LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.ALL;

entity LCDtest is
	port(
    CLOCK_50 : IN STD_LOGIC;
    KEY : IN STD_LOGIC_VECTOR (1 DOWNTO 0); --reset, enable
    SW : IN STD_LOGIC_VECTOR (9 DOWNTO 0); -- bus
	 
	 LEDR : OUT STD_LOGIC_VECTOR (0 DOWNTO 0);
    LCD_RW : OUT STD_LOGIC;
    LCD_RS : OUT STD_LOGIC;
    LCD_EN : OUT STD_LOGIC;
    LCD_DATA : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)
);
end entity;

architecture LCDtest_struct of LCDtest is
begin
tester_LCD: entity lcd_controller port map
(
    clk => CLOCK_50,
    reset_n => KEY(0),
    lcd_enable => KEY(1),
    busy => LEDR(0),
    lcd_bus => SW(9 DOWNTO 0),
    rw => LCD_RW,
    rs => LCD_RS,
    e => LCD_EN,
    lcd_data => LCD_DATA(7 DOWNTO 0)

	
	 
);
end LCDtest_struct;

 
  