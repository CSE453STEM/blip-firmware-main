/*
 * BLIP-controller.c
 *
 * Created: 3/21/2016 1:23:40 PM
 * Author : Alex
 */ 

#include <avr/io.h>

#include "uart.h"

void init_gpio(void)
{
	//Init Port B
	DDRB = 0xEF;	//Pins 0-6 output
	PORTB = 0x00;	//All outputs off
	
	//Init port C
	DDRC = 0xEF;	//Pins 0-6 output
	PORTC = 0x00;	//All outputs off
	
	//Init port D
	DDRD = 0x00;
	PORTD = 0x00;
}

void init_timers(void)
{
	//Init timer 0
	
	//Init timer 1
	
	//Init timer 2
	
}

int main(void)
{
	init_gpio();
	uart_init();
	
	UDR0 = 'a';
    while (1) 
    {
    }
}

