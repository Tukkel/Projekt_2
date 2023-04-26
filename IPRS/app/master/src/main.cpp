/*
 * LAB6-2.c
 *
 * Created: 05/10/2022 10.22.22
 * Author : terkel
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
  DDRA = 0x00;			//Port A input
	DDRB = 0xFF;			//Port B output
    while (1) 
    {
		if ((~PINA & (1<<0)))
		{
			_delay_us(478);
			PORTB = ~PORTB;
		}
		else if ((~PINA & (1<<1)))
		{
			_delay_us(506);
			PORTB = ~PORTB;
		}
		else if ((~PINA & (1<<2)))
		{
			_delay_us(568);
			PORTB = ~PORTB;
		}
		else if ((~PINA & (1<<3)))
		{
			_delay_us(638);
			PORTB = ~PORTB;
		}
		else if ((~PINA & (1<<4)))
		{
			_delay_us(716);
			PORTB = ~PORTB;
		}
		else if ((~PINA & (1<<5)))
		{
			_delay_us(758);
			PORTB = ~PORTB;
		}
		else if (~PINA & (1<<6))
		{
			_delay_us(851);
			PORTB = ~PORTB;
		}
		else if (~PINA & (1<<7))
		{
			_delay_us(956);
			PORTB = ~PORTB;
		}
    }
}

