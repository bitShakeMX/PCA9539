#ifndef _PCA9539_H
#define _PCA9539_H

/* PCA9539 library by Alfonso Martinez Alcantara
 *
 * This library allows for easy interfacing with PCA9539 GPIO expander chip
 * using I2C protocol. It has familiar functions when dealing with the pins
 * such as pinMode(), digitalWrite(), and digitalRead().
 *
 * It also allows using inverted input, as well as interrupt when input status
 * changes, to avoid continuous polling.
 */

// This will load the definition for common Particle variable types
// #include "Particle.h"

#include <Arduino.h>
#include <Wire.h>

#define PCA9539_I2C_ADDRESS 0x77

#define PCA9539_IP0_REGISTER 0x00
#define PCA9539_IP1_REGISTER 0x01

#define PCA9539_OP0_REGISTER 0x02
#define PCA9539_OP1_REGISTER 0x03

#define PCA9539_INV0_REGISTER 0x04
#define PCA9539_INV1_REGISTER 0x05

#define PCA9539_CONF0_REGISTER 0x06
#define PCA9539_CONF1_REGISTER 0x07

#define READ_ONE_BYTE 1

class PCA9539
{
public:
  PCA9539();

  void begin(uint8_t i2caddr = PCA9539_I2C_ADDRESS);
  void pinMode(uint8_t pin, uint8_t mode);
  void digitalWrite(uint8_t pin, uint8_t value);
  bool digitalRead(uint8_t pin);

  int32_t readI2c(uint8_t address);
  void writeI2c(uint8_t address, uint8_t data);

private:
  uint8_t _lastError; // Save the last error transmition
  uint8_t _i2caddr;   // I2C address of the device
  uint8_t _port;      // Port configuration status on Configuration register
  uint8_t _invport;   // Port inverted status on Polarity Inversion register
};

#endif