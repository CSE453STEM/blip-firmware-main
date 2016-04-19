#include extract.h

void buildmessage(char c) {

  if( c == 0xFF ) {
    count++;
  }

  if( count == 1 ) {
    speed = c;
    count++;
  }
  else if( count == 2 ) {
    pay_size = c;
    count++;
  }
  else if( count >= 3 && count <= ( pay_size + 2 ) ) {
    message[count-3] = c;
    count++;
  }
  else if( count > ( pay_size + 2 ) ) {
    controller_transmit(speed, message, pay_size);
    count = 0;
    pay_size = 0;
  }
}
    
    


