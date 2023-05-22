library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

ENTITY Panel_tester IS

  PORT(
		CLOCK_50 : in std_logic; --clk
		KEY : in std_logic_vector(2 downto 0); --reset, shift, home
		GPIO_0 : in std_logic_vector(0 downto 0); --RX-serialIN
		SW : in std_logic_vector(3 downto 0); --rooms
		
		LEDG : out std_LOGIC_VECTOR(0 downto 0); -- RX_busy
		LCD_RW : OUT STD_LOGIC; 
		LCD_RS : OUT STD_LOGIC;
		LCD_EN : OUT STD_LOGIC;
		LCD_ON : out std_LOGIC;
		LCD_DATA : OUT STD_LOGIC_VECTOR (7 DOWNTO 0)

	 ); 
END entity;

ARCHITECTURE rtl OF Panel_tester IS 
BEGIN
	 
	 p1 : entity Panel port map(clk => CLOCK_50, reset => KEY(0), RX_serialIN => GPIO_0(0), shift => KEY(1), home => KEY(2), rooms => SW(3 downto 0), 
											RX_busy => LEDG(0), rw => LCD_RW, rs => LCD_RS, e => LCD_EN, lcdon => LCD_ON, lcd_data => LCD_DATA(7 downto 0));
	
	 
END rtl;