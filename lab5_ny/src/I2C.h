#include <stdint.h>
#ifndef I2C_H
#define I2C_H

void initI2C(int sdapin, int sclpin);
void writeI2C(uint8_t address, uint8_t reg, uint8_t data);
void readI2C(uint8_t address, uint8_t reg, uint8_t *buffer, int len);
#endif