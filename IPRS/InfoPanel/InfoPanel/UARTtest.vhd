LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.all;

ENTITY UARTtest IS -- UART_RX
    PORT (
        CLOCK_50 : IN STD_LOGIC;
        GPIO_1 : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
		  

		  GPIO_0 : out STD_LOGIC_VECTOR(2 DOWNTO 0);
        LEDR : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
    );
END UARTtest; -- UART_RX

ARCHITECTURE rtl OF UARTtest IS -- UART_RX
BEGIN

    uart : entity UART_RX port map(i_clk => CLOCK_50, i_RX_Serial => GPIO_1(0), o_RX_DV => GPIO_0(0), o_RX_Byte => LEDR(7 downto 0));

	 GPIO_0(1) <= GPIO_1(0);
	 
END rtl;