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
	
	data = PINC & 0x3F;
	data |= (PIND & 0x04) << 4; 
	return (~data) & 0x7F;
}


/*this turns the leds on */
void led_write(unsigned char data){
	PORTB = data & 0x7F;
}



/*this clears the led lights*/
void led_clear(void){
	PORTB &= 0x80;
}