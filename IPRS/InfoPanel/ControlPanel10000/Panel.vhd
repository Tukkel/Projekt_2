LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.ALL;

ENTITY Panel IS
	GENERIC (
		shiftCounter : INTEGER := 12500000 -- 4 times a second
	);

  PORT(
    clk         : IN   STD_LOGIC;                     --system clock
    reset       : IN   STD_LOGIC;                     --active low reinitializes lcd, button
    RX_serialIN : IN   STD_LOGIC;                    --data to UART from Arduino, GPIO
    shift       : IN   STD_LOGIC;                     --shifts display, button
    home        : in std_logic;                        --resets cursor to home, button
    rooms       : in std_logic_vector(4 downto 1);     --room number, switches
	 
	 
	 roomsInUse   : out std_LOGIC_VECTOR(7 downto 0);    -- LED for rooms
    TX_serialout : out std_LOGIC;							--Transmitter output
    RX_busy    : OUT  STD_LOGIC;                     --active high, uart busy, goes to LED
    rw, rs, e, lcdon  : OUT  STD_LOGIC;                     --read/write, setup/data, enable and on for lcd
    lcd_data   : OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)

		-- OUTPUTS
		roomsInUse : OUT STD_LOGIC_VECTOR(7 DOWNTO 0); -- LED for rooms
		TX_serialout : OUT STD_LOGIC; --Transmitter output
		RX_busy : OUT STD_LOGIC; --active high, uart busy, goes to LED
		rw, rs, e, lcdon : OUT STD_LOGIC; --read/write, setup/data, enable and on for lcd
		lcd_data : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)

	);
END Panel;

ARCHITECTURE Panel_impl OF Panel IS
	TYPE state IS (USER_state, receive_state, send_state);
	SIGNAL present_state, next_state : state;

	-- lcd signals
	SIGNAL lcd_enable : STD_LOGIC; --latches data into lcd controller
	SIGNAL lcd_bus    : STD_LOGIC_VECTOR(9 DOWNTO 0);
	SIGNAL lcd_busy   : STD_LOGIC;

	--rx signals
	SIGNAL RX_ByteReady : STD_LOGIC; --Active high, come and get the byte plz
	SIGNAL RX_data      : STD_LOGIC_VECTOR(7 DOWNTO 0); --data from uart RX

	--tx signals
	SIGNAL TX_data   : STD_LOGIC_VECTOR(7 DOWNTO 0); --data to uart TX
	SIGNAL TX_send   : STD_LOGIC; --send the byte
	SIGNAL TX_active : STD_LOGIC; --sending 
	SIGNAL TX_done   : STD_LOGIC; --done sending

	--shifting logic
	SIGNAL previous_vector : STD_LOGIC_VECTOR(3 DOWNTO 0);
	SIGNAL change_detected : STD_LOGIC;
	SIGNAL doShift         : STD_LOGIC;

	SIGNAL mapleds : STD_LOGIC;

	--Constants
	CONSTANT startbyte : STD_LOGIC_VECTOR := "01111110"; --start byte for uart ascii ~
	CONSTANT stopbyte  : STD_LOGIC_VECTOR := "00100001"; --stop byte for uart ascii !
	CONSTANT ledstart  : STD_LOGIC_VECTOR := "00101111"; --LEDbyte start ascii /
	CONSTANT ledstop   : STD_LOGIC_VECTOR := "01011100"; --LEDbyte start ascii \

BEGIN
	-- Instantiate components
	uartRX : ENTITY UART_RX PORT MAP(i_clk => clk, i_RX_Serial => RX_serialIN, o_RX_DV => RX_ByteReady, o_RX_Byte => RX_data);
	uartTX : ENTITY UART_TX PORT MAP(i_clk => clk, i_TX_DV => TX_send, i_TX_Byte => TX_data, o_TX_Active => TX_active, o_TX_Serial => TX_serialout, o_TX_Done => TX_done);
	lcd    : ENTITY lcd_controller PORT MAP(clk => clk, reset_n => reset, lcd_enable => lcd_enable, lcd_bus => lcd_bus, busy => lcd_busy, rw => rw, rs => rs, e => e, lcd_data => lcd_data, lcdon => lcdon);

state_reg : PROCESS (clk, reset)
	BEGIN
		IF reset = '0' THEN
			present_state <= USER_state;
		ELSIF rising_edge(clk) THEN
			present_state <= next_state;
		END IF;
	END PROCESS;

outputs : PROCESS (clk, present_state, RX_ByteReady, TX_active, reset)
	BEGIN
		IF reset = '0' THEN
			roomsInUse <= "00000000";
		ELSIF rising_edge(clk) THEN
			
		CASE present_state IS
			WHEN receive_state =>
				RX_busy <= '1';
				IF RX_ByteReady = '1' THEN -- if we have a byte to read
					IF RX_data = ledstart AND mapleds = '0' THEN -- if the byte is / and we are not already mapping leds
						mapleds <= '1';
					ELSIF mapleds = '1' THEN -- if we are mapping leds. This could be done with a counter instead so more bytes could be read
						roomsInUse <= RX_data;
						mapleds <= '0';
					ELSIF (lcd_busy = '0' AND lcd_enable = '0') THEN -- if we are not mapping leds and the lcd is not busy
						lcd_enable <= '1';
						IF RX_data = startbyte THEN -- if it is second ~ then clear display
							lcd_bus <= "0000000001";
						ELSIF RX_data = stopbyte THEN
							lcd_enable <= '0';		 -- Stop printing
						ELSE
							lcd_bus <= "10" & RX_data; -- Else print the byte
						END IF;
					ELSE
						lcd_enable <= '0';
					END IF;
				ELSE
					lcd_enable <= '0';
				END IF;

			WHEN USER_state =>
				--TX_data <= "0000" & rooms;
				RX_busy <= '0';
				lcd_enable <= '0';
				IF doShift = '1' AND shift = '0' THEN -- shift screen to the left
					lcd_enable <= '1';
					lcd_bus <= "0000011000";
				ELSIF home = '0' THEN -- return home
					lcd_enable <= '1';
					lcd_bus <= "0000000010";
				END IF;

			WHEN send_state =>
				TX_data <= "0000" & rooms; -- sends the switches to the arduino
				IF TX_active = '0' THEN
					TX_send <= '1';
				ELSE
					TX_send <= '0';
				END IF;

				-- default branch
			WHEN OTHERS =>
				RX_busy <= '0';
				lcd_enable <= '0';

		END CASE;
	END IF;
END PROCESS;

nxt_state : PROCESS (present_state, RX_ByteReady)
	BEGIN
		next_state <= present_state;
		CASE present_state IS

			WHEN receive_state =>
				IF RX_ByteReady = '1' THEN
					IF RX_data = stopbyte THEN -- only way to get out of this state
						next_state <= USER_state;
					END IF;
				ELSE
					next_state <= receive_state;
				END IF;

			WHEN USER_state =>
				IF RX_ByteReady = '1' THEN
					IF RX_data = startbyte THEN -- if the byte is ~
						next_state <= receive_state;
					END IF;

				ELSIF change_detected = '1' THEN -- if the switches have changed
					next_state <= send_state;

				ELSE
					next_state <= USER_state;
				END IF;

			WHEN send_state =>
				IF RX_ByteReady = '1' THEN
					IF RX_data = startbyte THEN -- if the byte is ~
						next_state <= receive_state;
					END IF;

				ELSIF TX_done = '1' THEN -- if the byte has been sent
					next_state <= USER_state;

				ELSE
					next_state <= send_state;
				END IF;

				-- default branch
			WHEN OTHERS =>
				NULL;

		END CASE;
	END PROCESS;

room_change : PROCESS (clk) -- ChatGPT code
	-- This process detects if the switches have changed
	BEGIN
		IF rising_edge(clk) THEN
			IF rooms /= previous_vector THEN
				change_detected <= '1';
			ELSE
				change_detected <= '0';
			END IF;
			previous_vector <= rooms;
		END IF;
	END PROCESS;

shiftProcess : PROCESS (clk)
	-- This process shifts the screen to the left every 4 seconds based on the shiftCounter generic
		VARIABLE counter : INTEGER RANGE 0 TO 50000001 := 0;
	BEGIN
		IF rising_edge(clk) THEN
			IF shift = '1' THEN
				doShift <= '0';
			ELSIF shift = '0' THEN -- if the button is pressed
				counter := counter + 1;
				IF counter = shiftCounter THEN
					doShift <= '1';
					counter := 0;
				ELSE
					doShift <= '0';
				END IF;
			END IF;
		END IF;
	END PROCESS;
END Panel_impl;