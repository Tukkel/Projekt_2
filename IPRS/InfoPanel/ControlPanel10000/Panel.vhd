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

    
    rw, rs, e, lcdon  : OUT  STD_LOGIC;                     --read/write, setup/data, enable and on for lcd
    lcd_data   : OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)

	 ); --data signals for lcd
END Panel;

architecture Panel_impl of Panel is
    signal   lcd_enable : STD_LOGIC;                     --latches data into lcd controller
    SIGNAL   lcd_bus    : STD_LOGIC_VECTOR(9 DOWNTO 0);
    SIGNAL   lcd_busy   : STD_LOGIC;
    signal   RX_ComeGetMe     : STD_LOGIC;                     --Active high, come and get the byte plz
    signal   RX_data    : STD_logic_vector(7 DOWNTO 0);  --data from uart
begin

  uart_rx : entity UART_RX port map(i_clk => clk, i_RX_Serial => RX_serialIN, o_RX_DV => RX_ComeGetMe, o_RX_Byte => RX_data);

  lcd : entity lcd_controller PORT MAP(clk => clk, reset_n => reset, lcd_enable => lcd_enable, lcd_bus => lcd_bus, busy => lcd_busy, rw => rw, rs => rs, e => e, lcd_data => lcd_data, lcdon => lcdon);




end Panel_impl;