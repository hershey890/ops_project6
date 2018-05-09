#ifndef TRANSMITTER_H
#define TRANSMITTER_H

/* Natasha Sarkar
 * transmitter.h
 * OPS 2018
 * Project: Wireless Space Team
 */

//TRANSMITTER

#include "RF24.h"

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes_trans[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

/* Sets up the radio as a transmitter */
void transmitter_setup();

/* Sends the value sent to this function (tex) over
 * radio. Prints "sending [val] ... ok..." upon success
 * and prints "sending [val] ... failed..." upon failure. 
 */
void sending(int tex);

#endif
