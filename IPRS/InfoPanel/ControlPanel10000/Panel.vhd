library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

ENTITY Panel IS

  PORT(
    clk        : IN   STD_LOGIC;                     --system clock
    reset      : IN   STD_LOGIC;                     --active low reinitializes lcd, button
    RX_serialIN : IN   STD_LOGIC;                     --data to UART from Arduino

    
    rw, rs, e, lcdon  : OUT  STD_LOGIC;                     --read/write, setup/data, enable and on for lcd
    lcd_data   : OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)

	 ); --data signals for lcd
END Panel;

architecture Panel_impl of Panel is
    signal   lcd_enable : STD_LOGIC;                     --latches data into lcd controller
    SIGNAL   lcd_bus    : STD_LOGIC_VECTOR(9 DOWNTO 0);
    SIGNAL   lcd_busy   : STD_LOGIC;
    signal   RX_get     : STD_LOGIC;                     --Active high, come and get the byte plz
    signal   RX_data    : STD_logic_vector(7 DOWNTO 0);  --data from uart
begin

end Panel_impl;