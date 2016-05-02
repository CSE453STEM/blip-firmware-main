/*
 * controller.c
 *
 * Created: 4/11/2016 2:01:13 PM
 *  Author: Alex
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "controller.h"
#include "led.h"
#include "uart.h"

static enum controller_state
{
	STATE_IDLE,
	STATE_SEND_ACK,
	STATE_RECEIVING,
	STATE_START_TRANSMISSION,
	STATE_TRANSMITTING,
	STATE_REQUEST_LOCK,
	STATE_WAIT
} state;

static unsigned int transmissionSpeeds[7] = {31250, 15625, 6250, 3125, 1562, 1024, 1024};
static unsigned char transmissionData[128];
static unsigned char transmissionSize;
static unsigned char transmissionCount;
static unsigned char lightsOn;

static unsigned char receiveData;
static unsigned char receiveFlag;

//Local functions
static void pci_enable()
{
	PCMSK2 = (1<<PCINT18);
	PCMSK1 = (1<<PCINT8)+(1<<PCINT9)+(1<<PCINT10)+(1<<PCINT11)+(1<<PCINT12)+(1<<PCINT13);
}

static void pci_disable()
{
	PCMSK2 = 0;
	PCMSK1 = 0;
}

//Global functions
void controller_init(void)
{
	state = STATE_IDLE;
	lightsOn = 0;
	receiveFlag = 0;
	// Initialize the timer module
	TCCR1B |= (1<<WGM12);
	TIMSK1 |= (1<<OCIE1A);	//Enable compare interrupt A 
	
	PCICR |= (1<<PCIE2)+(1<<PCIE1);	//Enable pin change interrupts on input pins
	pci_enable();
}

/* Table of blip rates:
 # | Char per sec | Divisor
 --------------------------
 0 | 1			  | 31250
 1 | 2			  | 15625
 2 | 5			  | 6250
 3 | 10			  | 3125
 4 | 20			  | 1562
 5 | 30			  | 1024
 6 | MAX		  | TBD
*/
void controller_transmit(unsigned char speed, unsigned char* data, unsigned char size)
{
	if(state != STATE_IDLE)
	{
		return;	//We weren't idle, don't start a new transmission
	}
	pci_disable();
	state = STATE_START_TRANSMISSION;
	transmissionSize = size;
	unsigned char i;
	for(i = 0; i < size; i++)
	{
		transmissionData[i] = data[i];
	}
	if(speed > 6) speed = 6;
	OCR1A = transmissionSpeeds[speed];
}

void controller_process(void)
{
	switch(state) {
		case STATE_IDLE:
			//Wait for Lock Request or a call to controller_transmit()
			if(receiveFlag)
			{
				receiveFlag = 0;
				uart_tx_byte(receiveData);
			}
			break;
			
		case STATE_START_TRANSMISSION:
			//Set up lights with the proper first byte
			//Reset counter to 0
			transmissionCount = 0;
			led_write(transmissionData[0]);
			lightsOn = 1;
			state = STATE_TRANSMITTING;
			
			//Enable timer
			TCCR1B |= (1<<CS12);
			
			break;
			
		case STATE_TRANSMITTING:
			//Check if transmission done
			if(transmissionCount == transmissionSize)
			{
				//Transmission is done
				//Exit transmit mode
				state = STATE_IDLE;
				pci_enable();
			}
			break;
			
		default:
			state = STATE_IDLE;
			break;
	}
}

ISR(TIMER1_COMPA_vect) 
{
	//Compare A interrupt vector
	//Used to time transmission of message
	
	//When compare is triggered, data has been on the line for the proper amount of time.  
	//Change it to the next byte (Or clear the line if we have reached the end of message)
	if(lightsOn)
	{
		//Lights were on for one cycle, turn them off and do nothing else
		led_clear();
		lightsOn = 0;
	}
	else
	{
		
		transmissionCount++;
	
		if(transmissionCount == transmissionSize)
		{
			//Xmit done, turn off timer and clear line
			led_clear();
			TCCR1B &= ~(1<<CS12);
		}
		else
		{
			//Xmit not done, put next byte on line
			led_write(transmissionData[transmissionCount]);
			lightsOn = 1;
			//Reset timer and wait again
		}
	}
}

ISR(PCINT1_vect)
{
	//Input pins have changed, read data if appropriate
	if(state == STATE_IDLE)
	{
		//We are idle, receive data
		_delay_ms(1);
		receiveData = led_read();
		if(receiveData != 0x00) {
			receiveFlag = 1;
		}
	}
}

ISR(PCINT2_vect)
{
	//Input pins have changed, read data if appropriate
	if(state == STATE_IDLE)
	{
		//We are idle, receive data
		_delay_ms(1);
		receiveData = led_read();
		if(receiveData != 0x00) {
			receiveFlag = 1;
		}
	}
}