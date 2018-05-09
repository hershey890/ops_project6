#ifndef RECEIVER_H
#define RECEIVER_H

/* Natasha Sarkar
 * receiver.h
 * OPS 2018
 * Project: Wireless Space Team
 */

//RECEIVER

#include "RF24.h"

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes_rec[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

/* Sets up the radio as a receiver */
void receiver_setup();

/* Returns true if there is data to read and stores the data into val; 
 * otherwise returns false.
 */
bool receiving(int& val);

#endif
