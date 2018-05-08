/* Natasha Sarkar 
 * receiver.cpp
 * OPS 2018
 * Project: Wireless Space Team
 */

#include "receiver.h"
#include "printf.h"

RF24 radio2(7,8);

void receiver_setup() {
  printf_begin();
  radio2.begin();

  radio2.setRetries(15,15);
  radio2.setPayloadSize(8);

  radio2.openWritingPipe(pipes_rec[1]);
  radio2.openReadingPipe(1,pipes_rec[0]);

  radio2.startListening();
  radio2.printDetails();
}

bool receiving(float &val) {
    // if there is data ready
    bool result;
    if ( radio2.available() ) {
      result = radio2.read(&val, sizeof(float));
      //printf(" %d \n", val);
      return result;
    }
  
    return false;
}
