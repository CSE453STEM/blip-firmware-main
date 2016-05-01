#ifndef PARSER_H_
#define PARSER_H_

unsigned char message[128];                                                                  
unsigned char blip = 0;                                                                    
unsigned char cannon = 0;                                                                  
unsigned char speed = 0;

unsigned char pay_size = 0;

void parser_build_message(unsigned char c);

#endif
