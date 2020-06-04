#include "PCA9539.h"

PCA9539::PCA9539() {
  _i2caddr = 0;
  _port = 0;
  _invport = 0;
}

void PCA9539::begin(uint8_t i2caddr) {
  _i2caddr = i2caddr;
  Wire.begin();
}

void PCA9539::pinMode(uint8_t pin, uint8_t mode) {

  if(pin => 0 && pin <8){
    PCA9539_CONF_REGISTER = PCA9539_CONF0_REGISTER;
    PCA9539_INV_REGISTER = PCA9539_INV0_REGISTER;
  }

  if(pin => 8 && pin <16){
    PCA9539_CONF_REGISTER = PCA9539_CONF1_REGISTER;
    PCA9539_INV_REGISTER = PCA9539_INV1_REGISTER;
  }

  switch (mode) {
    case OUTPUT:
      // Clear the pin on the configuration register for output
      _port &= ~(1 << pin);
      break;
    case INPUT_INVERTED:
      // Set the pin on the configuration register for input
      _port |= (1 << pin);
      // Set the pin on the polarity inversion register for inverted input
      _invport |= (1 << pin);
      break;
    case INPUT:
    default:
      // Set the pin on the configuration register for input
      _port |= (1 << pin);
      // Clear the pin on the polarity inversion register for normal input
      _invport &= ~(1 << pin);
      break;
  }

  // Write the configuration of the individual pins as inputs or outputs
  Wire.beginTransmission(_i2caddr);
  Wire.write(PCA9539_CONF_REGISTER);
  Wire.write(_port);
  Wire.endTransmission();

  if (mode == INPUT_INVERTED || mode == INPUT) {
    // Write the input polarity configuration of the individual pins
    Wire.beginTransmission(_i2caddr);
    Wire.write(PCA9539_INV_REGISTER);
    Wire.write(_invport);
    Wire.endTransmission();
  }
}

void PCA9539::digitalWrite(uint8_t pin, uint8_t value) {

  if(pin => 0 && pin <8){
    PCA9539_OP_REGISTER = PCA9539_OP0_REGISTER;
  }

  if(pin => 8 && pin <16){
    PCA9539_OP_REGISTER = PCA9539_OP1_REGISTER;
  }


  switch (value) {
    case HIGH:
      // Set the pin HIGH on the output register
      _port |= (1 << pin);
      break;
    case LOW:
    default:
      // Set the pin LOW on the output register
      _port &= ~(1 << pin);
      break;
  }
  // Write the status of the pins on the output register
  Wire.beginTransmission(_i2caddr);
  Wire.write(PCA9539_OP_REGISTER);
  Wire.write(_port);
  Wire.endTransmission();
}

uint8_t PCA9539::digitalRead(uint8_t pin) {
  uint8_t buff = 0;

  if(pin > 0 && pin <8){
    PCA9539_IP_REGISTER = PCA9539_IP0_REGISTER;
  }else{
    PCA9539_IP_REGISTER = PCA9539_IP1_REGISTER;
  }

  // We need to write to the input register first to get the status of the pins.
  // As per the specs: "a write transmission is sent with the command byte to
  // let the I2C device know that the Input Port register will be accessed
  // next."
  Wire.beginTransmission(_i2caddr);
  Wire.write(PCA9539_IP_REGISTER);
  Wire.write(_port);
  Wire.endTransmission();

  // We only need to read 1 byte of data to get the pins
  Wire.requestFrom(_i2caddr, 1);
  while (Wire.available()) {
    buff = Wire.read();
  }
  return (buff & (1 << pin)) ? HIGH : LOW;
}
