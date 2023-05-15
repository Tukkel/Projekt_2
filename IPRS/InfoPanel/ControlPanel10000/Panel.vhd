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

    
    RX_busy    : OUT  STD_LOGIC;                     --active high, uart busy, goes to LED
    rw, rs, e, lcdon  : OUT  STD_LOGIC;                     --read/write, setup/data, enable and on for lcd
    lcd_data   : OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)

	 ); --data signals for lcd
END Panel;

architecture Panel_impl of Panel is
	type state is (USER_state, receive_state); --Send_state
	signal present_state, next_state : state;

    signal   lcd_enable : STD_LOGIC;                     --latches data into lcd controller
    SIGNAL   lcd_bus    : STD_LOGIC_VECTOR(9 DOWNTO 0);
    SIGNAL   lcd_busy   : STD_LOGIC;
    signal   RX_ComeGetMe     : STD_LOGIC;                     --Active high, come and get the byte plz
    signal   RX_data    : STD_logic_vector(7 DOWNTO 0);  --data from uart

  constant startbyte : STD_LOGIC_VECTOR := "01111110"; --start byte for uart ascii ~
  constant stopbyte : STD_LOGIC_VECTOR := "00100001"; --stop byte for uart ascii !
begin

  uart : entity UART_RX port map(i_clk => clk, i_RX_Serial => RX_serialIN, o_RX_DV => RX_ComeGetMe, o_RX_Byte => RX_data);

  lcd : entity lcd_controller PORT MAP(clk => clk, reset_n => reset, lcd_enable => lcd_enable, lcd_bus => lcd_bus, busy => lcd_busy, rw => rw, rs => rs, e => e, lcd_data => lcd_data, lcdon => lcdon);


	state_reg : PROCESS (clk, reset)
	BEGIN
		IF reset = '0' THEN
			present_state <= USER_state;
		ELSIF rising_edge(clk) THEN
			present_state <= next_state;
		END IF;
	END PROCESS;
  
  outputs: process (clk, present_state, RX_ComeGetMe)
  begin
    case present_state is
    -- one case branch required for each state
    when receive_state =>
      RX_busy <= '1';
		 if rising_edge(clk) then
			if RX_ComeGetMe = '1' then
				IF(lcd_busy = '0' AND lcd_enable = '0') THEN
				  lcd_enable <= '1';
				  lcd_bus <= "10" & RX_data;
				ELSE
				  lcd_enable <= '0';
				END IF;
			elsE
				lcd_enable <= '0';
			end if;
		 end if;
  
    when USER_state =>
      RX_busy <= '0';
      lcd_enable <= '0';

    -- default branch
    when others =>
		RX_busy <= '0';
		lcd_enable <= '0';
  
    end case;
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
		else
			next_state <= USER_state;
      end if;

      -- default branch
      when others =>
        null;
  
    end case;
  end process;
  
end Panel_impl;