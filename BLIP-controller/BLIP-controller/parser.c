/*
 * parser.c
 *
 * Created: 5/1/2016 3:04:33 PM
 *  Author: Alex
 */ 

#include "parser.h"
#include "controller.h"

static unsigned char message[128];
static unsigned char blip;
static unsigned char cannon;
static unsigned char speed;

static unsigned char pay_size;

void parser_init(void)
{
	blip = 0;
	cannon = 0;
	speed = 0;
	pay_size = 0;
}

void parser_build_message(unsigned char c) {

	if( c == 0xFF  && cannon == 0 ) {
		blip++;
		return;
	}

	if( blip == 0 && cannon <= 3 ) {
		message[cannon] = c;
		cannon++;
		return;
	}
	else if( cannon == 4 ) {
		message[cannon] = c;
		cannon = 0;
		controller_transmit(0x05, message, 4);
		return;
	}
	
	if( blip == 1 ) {
		speed = c;
		blip++;
	}
	else if( blip == 2 ) {
		pay_size = c;
		blip++;
	}
	else if( blip >= 3 && blip <= ( pay_size + 2 ) ) {
		message[blip-3] = c;
		blip++;
	}
	
	if( blip > ( pay_size + 2 ) ) {
		controller_transmit(speed, message, pay_size);
		blip = 0;
		pay_size = 0;
	}
}



