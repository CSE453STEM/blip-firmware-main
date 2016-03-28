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
void uart_tx_byte(unsigned char data);

// Receive a single byte from rx buffer
unsigned char uart_rx_byte(void);



#endif /* UART_H_ */