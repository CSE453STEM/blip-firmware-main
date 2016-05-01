/*
 * BLIP-controller.c
 *
 * Created: 3/21/2016 1:23:40 PM
 * Author : Alex
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"
#include "led.h"
#include "controller.h"


void init_gpio(void)
{
	//Init Port B
	DDRB = 0xEF;	//Pins 0-6 output
	PORTB = 0x00;	//All outputs off
	
	//Init port C
	DDRC = 0x00;	//Pins 0-6 input
	PORTC = 0x00;	//All pullups off
	
	//Init port D
	DDRD = 0x00;	//Pins 0-7 input
	PORTD = 0x00;	//All pullups off
}

int main(void)
{
	init_gpio();
	uart_init();
	controller_init();
	
	sei();
	unsigned char buffer[3] = {'A', 'B', 'C'};
	//controller_transmit(0x00, buffer, 3);

	unsigned char data;	
    while (1) 
    {
		controller_process();
		/*while(uart_rx_byte(&data))
		{
			uart_tx_byte(data);
			led_write(data);
		}*/
    }
}

