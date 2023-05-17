library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

ENTITY Panel IS

  PORT(
    clk         : IN   STD_LOGIC;                     --system clock
    reset       : IN   STD_LOGIC;                     --active low reinitializes lcd, button
    RX_serialIN : IN   STD_LOGIC;                    --data to UART from Arduino, GPIO
    shift       : IN   STD_LOGIC;                     --shifts display, button
    home        : in std_logic;                        --resets cursor to home, button
    rooms       : in std_logic_vector(3 downto 0);     --room number, switches
	 
	 
	  roomsInUse   : out std_LOGIC_VECTOR(7 downto 0);    -- LED for rooms
    TX_serialout : out std_LOGIC;							--Transmitter output
    RX_busy    : OUT  STD_LOGIC;                     --active high, uart busy, goes to LED
    rw, rs, e, lcdon  : OUT  STD_LOGIC;                     --read/write, setup/data, enable and on for lcd
    lcd_data   : OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)

	 ); --data signals for lcd
END Panel;

architecture Panel_impl of Panel is
	type state is (USER_state, receive_state, send_state); --Send_state
	signal present_state, next_state : state;

	 -- lcd signals
    signal   lcd_enable : STD_LOGIC;                     --latches data into lcd controller
    SIGNAL   lcd_bus    : STD_LOGIC_VECTOR(9 DOWNTO 0);
    SIGNAL   lcd_busy   : STD_LOGIC;
	 
	 --rx signals
    signal   RX_ComeGetMe     : STD_LOGIC;               --Active high, come and get the byte plz
    signal   RX_data    : STD_logic_vector(7 DOWNTO 0);  --data from uart RX
	 
	 --tx signals
	 signal   TX_data    : STD_logic_vector(7 DOWNTO 0);  --data to uart TX
	 signal 	 TX_send    : STD_LOGIC;							--send the byte
	 signal   TX_active  : std_LOGIC;							--sending 
	 signal   TX_done    : std_LOGIC;							--done sending
	 
	 --shifting logic
	 signal previous_vector : std_logic_vector(3 downto 0);
	 signal change_detected : std_LOGIC;
	 signal doShift         : std_LOGIC;
	 
	 signal mapleds : std_LOGIC;
	 
	 
  constant startbyte : STD_LOGIC_VECTOR := "01111110"; --start byte for uart ascii ~
  constant stopbyte : STD_LOGIC_VECTOR := "00100001"; --stop byte for uart ascii !
  constant ledstart : std_LOGIC_VECTOR := "00101111"; --LEDbyte start ascii /
  constant ledstop : std_LOGIC_VECTOR := "01011100"; --LEDbyte start ascii \
begin

  uartRX : entity UART_RX port map(i_clk => clk, i_RX_Serial => RX_serialIN, o_RX_DV => RX_ComeGetMe, o_RX_Byte => RX_data);

  uartTX : entity UART_TX port map(i_clk => clk, i_TX_DV => TX_send, i_TX_Byte => TX_data, o_TX_Active => TX_active, o_TX_Serial => TX_serialout, o_TX_Done => TX_done);
  
  lcd : entity lcd_controller PORT MAP(clk => clk, reset_n => reset, lcd_enable => lcd_enable, lcd_bus => lcd_bus, busy => lcd_busy, rw => rw, rs => rs, e => e, lcd_data => lcd_data, lcdon => lcdon);


	state_reg : PROCESS (clk, reset)
	BEGIN
		IF reset = '0' THEN
			present_state <= USER_state;
		ELSIF rising_edge(clk) THEN
			present_state <= next_state;
		END IF;
	END PROCESS;
  
  
  outputs: process (clk, present_state, RX_ComeGetMe, TX_active, reset)
  begin
	if reset = '0' then
		roomsInUse <= "00000000";
   elsif rising_edge(clk) then
    case present_state is
    -- one case branch required for each state
    when receive_state =>
	 
	 -- ~~ /(ledbyte)\(data)!
	 
      RX_busy <= '1';
			if RX_ComeGetMe = '1' then
			   if RX_data = ledstart and mapleds = '0' then
					mapleds <= '1';
				elsIF RX_data = ledstop and mapleds = '1' then
					mapleds <= '0';
				elsif mapleds = '1' then
					roomsInUse <= RX_data;
				elsIF(lcd_busy = '0' AND lcd_enable = '0') THEN
				  lcd_enable <= '1';
				  	if RX_data = startbyte then
						lcd_bus <= "0000000001"; -- Clear display
					else 
						lcd_bus <= "10" & RX_data; -- Else print the byte
					end if;
				ELSE
				  lcd_enable <= '0';
				END IF;
			elsE
				lcd_enable <= '0';
			end if;
  
    when USER_state =>
	   TX_data <= "0000" & rooms;
      RX_busy <= '0';
      lcd_enable <= '0';
		if doShift = '1' and shift = '0' then -- shift screen to the left
			lcd_enable <= '1';
			lcd_bus <= "0000011000";
		elsif home = '0' then					  -- return home
			lcd_enable <= '1';
			lcd_bus <= "0000000010";
		end if;
			

	
	 when send_state =>
		TX_data <= "0000" & rooms;
			if TX_active = '0' then
				TX_send <= '1';
			else
				TX_send <= '0';
			end if;
	
    -- default branch
    when others =>
		RX_busy <= '0';
		lcd_enable <= '0';
  
    end case;
	end if;
  end process;
  
  nxt_state: process (present_state, RX_ComeGetMe)
  begin
    next_state <= present_state;
    case present_state is
  
      -- one case branch required for each state
      --when <state_value_i> =>
        --if <input_condition_1> then
        -- assignment to next_state
        --elsif <input_condition_2> then
        -- assignment to next_state
        --else
        -- assignment to next_state
        --end if;
  
      --...
     when receive_state =>
      if RX_ComeGetMe = '1' then
        IF RX_data = stopbyte THEN
          next_state <= USER_state;
        END IF;
		else
			next_state <= receive_state;
      END IF;


     when USER_state =>
      if RX_ComeGetMe = '1' then
        IF RX_data = startbyte THEN
          next_state <= receive_state;
        END IF;
		
		elsif change_detected = '1' then
			next_state <= send_state;
			
		else
			next_state <= USER_state;
      end if;

		
		when send_state =>
      if RX_ComeGetMe = '1' then
        IF RX_data = startbyte THEN
          next_state <= receive_state;
        END IF;
		
		elsif TX_done = '1' then
			next_state <= USER_state;
		
		else
        next_state <= send_state;
       end if;
		  
		  
      -- default branch
      when others =>
        null;
  
    end case;
  end process;
  

   room_change : process(clk) -- ChatGPT
    begin
        if rising_edge(clk) then
            if rooms /= previous_vector then
                change_detected <= '1';
            else
                change_detected <= '0';
            end if;
            previous_vector <= rooms;
        end if;
    end process;
	 
	 
	 
	 
	shiftProcess : process(clk)
		variable counter : integer range 0 to 25000001 := 0;
	begin
	if rising_edge(clk) then
		if shift = '1' then
			doShift <= '0';
		elsif shift = '0' then
			counter := counter + 1;
			if counter = 12500000 then
				doShift <= '1';
				counter := 0;
			else
				doShift <= '0';
			end if;
		end if;
	 end if;
	end process;
	

end Panel_impl;