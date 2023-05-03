LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
USE work.all;

ENTITY UARTtest IS -- UART_RX
    PORT (
        CLOCK_50 : IN STD_LOGIC;
        GPIO_1 : IN STD_LOGIC_VECTOR(2 DOWNTO 1);

        LEDR : OUT STD_LOGIC_VECTOR(8 DOWNTO 0)
    );
END UARTtest; -- UART_RX

ARCHITECTURE rtl OF UARTtest IS -- UART_RX
BEGIN

    uart : entity UART_RX port map(i_clk => CLOCK_50, i_RX_Serial => GPIO_1(1), o_RX_DV => LEDR(8), o_RX_Byte => LEDR(7 downto 0));

END rtl;