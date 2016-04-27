/*
 * led.c
 *
 * Created: 3/25/2016 1:47:39 PM
 *  Author: Alex
 */ 

#include <avr/io.h>

#include "led.h"

/*this reads the leds*/
unsigned char led_read(void){
	unsigned char data;
	
	data = PINB & 0x7F; 
	return data;
}


/*this turns the leds on */
void led_write(unsigned char data){
	
	data = data & 0x7F;
	PORTB = data;

	
}



/*this clears the led lights*/
void led_clear(void){
	PORTB &= 0x80;
}