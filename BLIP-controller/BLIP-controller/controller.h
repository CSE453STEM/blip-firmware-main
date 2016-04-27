/*
 * controller.h
 *
 * Created: 4/11/2016 2:02:17 PM
 *  Author: Alex
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

void controller_init(void);

void controller_transmit(unsigned char speed, unsigned char* data, unsigned char size);

void controller_process(void);

#endif /* CONTROLLER_H_ */