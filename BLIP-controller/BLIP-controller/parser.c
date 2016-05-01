#include parser.h

void parser_build_message(char c) {

  if( c == 0xFF  && cannon == 0 ) {
    blip++;
  }

  if( blip == 0 && cannon <= 3 ) {
    message[cannon] = c;
    cannon++;
  }
  else if( cannon == 4 ) {
    message[cannon] = c;
    cannon = 0;
    controller_transmit(max, message, 4);
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
  else if( blip > ( pay_size + 2 ) ) {
    controller_transmit(speed, message, pay_size);
    blip = 0;
    pay_size = 0;
  }
}
    
    


