#pragma once

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
#include "Particle.h"

#define PCA9539_I2C_ADDRESS        0x74

#define PCA9539_IP0_REGISTER       0x00
#define PCA9539_IP1_REGISTER       0x01

#define PCA9539_OP0_REGISTER       0x02
#define PCA9539_OP1_REGISTER       0x03

#define PCA9539_INV0_REGISTER      0x04
#define PCA9539_INV1_REGISTER      0x05

#define PCA9539_CONF0_REGISTER     0x06
#define PCA9539_CONF1_REGISTER     0x07


class PCA9539 {
public:
  /**
   * Constructor
   * Creates a new PCA9539 class to manage a PCA9539 chip.
   */
  PCA9539();

  /**
   * Initializes the device and performs initial I2C setup.
   * This method should be called before any others are used.
   *
   * @param {uint8_t} i2caddr - Sets the slave address of the PCA9539,
   * defaults to 0x20.
   */
  void begin(uint8_t i2caddr = PCA9539_I2C_ADDRESS);

  /**
   * Configures the specified pin to behave either as an input, inverted input,
   * or output.
   *
   * @param {uint8_t} pin - Pin number whose mode you wish to set.
   * @param {uint8_t} mode - Pin mode one of: INPUT, INPUT_INVERTED, or OUTPUT.
   */
  void pinMode(uint8_t pin, uint8_t mode);

  /**
   * Writes a HIGH or a LOW value to a digital pin.
   *
   * @param {uint8_t} pin - Pin number whose value you wish to set.
   * @param {uint8_t} value - Pin value one of: HIGH, or LOW.
   */
  void digitalWrite(uint8_t pin, uint8_t value);

  /**
   * Reads the value from a specified digital pin, either HIGH or LOW.
   * **Note: When using INPUT_INVERTED on pinMode(), you will get the inverted
   * status.**
   *
   * @param {uint8_t} pin - Pin number whose value you wish to get.
   * @returns {uint8_t} The status of the pin either HIGH or LOW.
   */
  uint8_t digitalRead(uint8_t pin);

private:
  uint8_t _i2caddr; // I2C address of the device
  uint8_t _port; // Port configuration status on Configuration register
  uint8_t _invport; // Port inverted status on Polarity Inversion register
};
