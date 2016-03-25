/*
 * led.h
 *
 * Created: 3/25/2016 1:47:28 PM
 *  Author: Alex
 */ 


#ifndef LED_H_
#define LED_H_

// Read data from the light pipe
unsigned char led_read(void);

// Write data to the light pipe
void led_write(unsigned char data);

// Clear the lights
void led_clear(void);

#endif /* LED_H_ */