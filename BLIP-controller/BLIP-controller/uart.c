/*
 * uart.c
 *
 * Created: 3/25/2016 1:46:51 PM
 *  Author: Alex
 */ 
#include <avr/io.h>

#include "uart.h"

void uart_init(void)
{
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UBRR0 = 25;	//19200 baud
}
