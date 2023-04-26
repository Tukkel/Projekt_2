/********************************************
* MSYS, LAB 13. Part 3                      *
* ADC using multiplexing and regulating.    *
*                                           *
* Henning Hargaard 11/4 2019                *
*********************************************/
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "uart.h"

void Init_ADC()
{
	// PF pins are inputs (ADC)
	DDRF = 0;
	// Internal 5 volt reference, ADLAR = 0, Input = ADC0 single ended
	ADMUX = 0b01000000;
	// ADC enable
	// ADC interrupt disabled
	// ADC prescaler = 128 (=> ADC clock = 16 MHz / 128 = 125 kHZ)
	ADCSRA = 0b10000111;
}

void Init_Timer3()
{
	// OC3A = PE, pin 3 : Set as output pin
	DDRE |= (1<<3);
	// Mode = 3 (PWM, Phase Correct, 10 bit)
	// Set OC3A on match down counting / Clear OC3A on match up counting
	// Clock prescaler = 1
	TCCR3A = 0b10000011;
	TCCR3B = 0b00000001;
	// Duty cycle = 50%
	OCR3A = 1024/2;
}

int main()
{
	unsigned int ADC_Potentiometer, ADC_PWM;
	int dif;
	
	Init_ADC();
	Init_Timer3();
	InitUART(9600, 8);
	SendChar('\r');
	while(1)
	{
		ADMUX &= ~(1);
		ADCSRA |= 0b01000000;
		while (ADCSRA & 0b01000000)
		{}
		ADC_Potentiometer = ADCW;
		SendString("ADC0 = ");
		SendInteger(ADC_Potentiometer);
		ADMUX |= 1;
		ADCSRA |= 0b01000000;
		while (ADCSRA & 0b01000000)
		{}
		ADC_PWM = ADCW;
		SendString(" | ADC1 = ");
		SendInteger(ADC_PWM);
		SendChar('\n');
		dif = ADC_Potentiometer-ADC_PWM;
		if (dif > 0)
		{
			OCR3A += (1+dif/3);
		}
		else if (dif < 0)
		{
			OCR3A += (dif/3-1);
		}
		_delay_ms(1000);
	}
}