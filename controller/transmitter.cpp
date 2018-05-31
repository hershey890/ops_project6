/* Natasha Sarkar
 * transmitter.cpp
 * OPS 2018
 * Project: Wireless Space Team
 */

#include "transmitter.h"
#include "printf.h"

RF24 radio(7, 8);

void transmitter_setup() {
  printf_begin();
  radio.begin();
  radio.setRetries(15,15);
  radio.setPayloadSize(8);
  radio.openWritingPipe(pipes_trans[0]);
  radio.openReadingPipe(1,pipes_trans[1]);
  
  radio.startListening();
  radio.printDetails();
}

void sending(int tex)
{
    // First, stop listening so we can talk.
    radio.stopListening();

    // Take the time, and send it.  This will block until complete
    
    printf("Now sending...");
    bool ok = radio.write( &tex, sizeof(int) );
    
    if (ok)
      printf("ok...\n");
    else
      printf("failed.\n\r");

    radio.startListening();
}
