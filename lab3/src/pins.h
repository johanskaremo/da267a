#ifndef PINS_H_
#define PINS_H_
#include <stdint.h>

// initialises the 4 pins 
void initPins();
// switches LED A on if level!=0 or off if level==0
void setLED(uint8_t level);


#endif