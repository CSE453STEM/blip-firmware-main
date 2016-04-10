/*
 * uart.h
 *
 * Created: 3/25/2016 1:47:06 PM
 *  Author: Alex
 */ 


#ifndef UART_H_
#define UART_H_

// Configure PD0 and PD1 as Uart RX/TX
void uart_init(void);

// Transmit a single byte
// Returns number of bytes placed into transmit queue
unsigned char uart_tx_byte(unsigned char data);

// Receive a single byte from rx buffer, place into data pointer
// Returns number of bytes retreived
unsigned char uart_rx_byte(unsigned char* data);

// Check number of bytes in receive queue
// Returns number of bytes currently in queue
unsigned char uart_rx_check(void);



#endif /* UART_H_ */