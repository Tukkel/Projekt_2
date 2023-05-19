
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE work.all;

ENTITY panel_test IS
  PORT(
      CLOCK_50       : IN  STD_LOGIC;  --system clock
		KEY				: IN std_LOGIC_VECTOR(3 downto 0);
		GPIO_0         : IN std_LOGIC_VECTOR(1 downto 0);
		SW					: IN std_LOGIC_VECTOR(3 downto 0);
		
		LEDG				: out std_LOGIC_VECTOR(0 downto 0);
		LEDR				: out std_logic_vector(8 downto 1);
      lcd_rw, lcd_rs, lcd_en : OUT STD_LOGIC;  --read/write, setup/data, and enable for lcd
      lcd_data  : INOUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		
		GPIO_1			: out std_LOGIC_VECTOR(1 downto 0);
		--lcd_blon : out std_LOGIC;
		lcd_on : out std_LOGIC
		); --data signals for lcd
END panel_test;

ARCHITECTURE behavior OF panel_test IS

BEGIN    

  --instantiate the lcd controller
 pan : entity Panel PORT MAP(clk => CLOCK_50, reset => KEY(0), RX_serialIN => GPIO_0(0), rooms => SW, shift => KEY(1), home => KEY(2),
	RX_busy => LEDG(0), rw => lcd_rw, rs => lcd_rs, e => lcd_en, lcd_data => lcd_data, lcdon => lcd_on, TX_serialout => GPIO_1(0), roomsInUse => LEDR);


END behavior;
