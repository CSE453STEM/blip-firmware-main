/*
 * uart.c
 *
 * Created: 3/25/2016 1:46:51 PM
 *  Author: Alex
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define BUFFER_SIZE 256

struct ringbuf {
	volatile unsigned char* array;
	volatile unsigned char head;
	volatile unsigned char tail;
};

static struct ringbuf rx_buf;
static struct ringbuf tx_buf;
static volatile unsigned char rx_buf_array[BUFFER_SIZE];
static volatile unsigned char tx_buf_array[BUFFER_SIZE];

void uart_init(void)
{
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);	//Enable transmitter and receiver, receive interrupt enable
	UBRR0 = 25;	//19200 baud
	
	//Set up ring buffers for RX and TX
	rx_buf.array = rx_buf_array;
	rx_buf.head = 0;
	rx_buf.tail = 0;
	
	tx_buf.array = tx_buf_array;
	tx_buf.head = 0;
	tx_buf.tail = 0;
}

unsigned char uart_tx_byte(unsigned char data)
{
	if(tx_buf.tail != (tx_buf.head + 1))
	{
		//TX buffer isn't full, add to queue and enable transmissions
		tx_buf.array[tx_buf.head] = data; 
		tx_buf.head++;
		UCSR0B |= (1<<UDRIE0);	//Start interrupts on transmit register empty
		return 1;	//Indicate one byte added to queue
	}
	
	//Buffer was full, return 0 bytes added to queue
	return 0;
}

unsigned char uart_rx_byte(unsigned char* data)
{
	if(rx_buf.head != rx_buf.tail)
	{
		//RX buffer isn't empty, return 1 byte of data read
		*data = rx_buf.array[rx_buf.tail];
		rx_buf.tail++;
		return 1;
	}
	
	//Buffer was empty, return 0 bytes read
	return 0;
}

unsigned char uart_rx_check(void)
{
	return rx_buf.head - rx_buf.tail;
}


ISR(USART_RX_vect)
{
	unsigned char data = UDR0;
	if(rx_buf.tail != (rx_buf.head + 1))
	{
		rx_buf.array[rx_buf.head] = data;
		rx_buf.head++;
	}
}

ISR(USART_UDRE_vect)
{
	if(tx_buf.head != tx_buf.tail)
	{
		//Buffer is not empty, transmit a byte
		UDR0 = tx_buf.array[tx_buf.tail];
		tx_buf.tail++;
	}
	else
	{
		//Data is not valid, stop interrupts
		UCSR0B &= ~(1<<UDRIE0);
	}
}