#include "PCA9539.h"

/**
 * @brief Constructor Creates a new PCA9539 class to manage a PCA9539 chip.
*/
PCA9539::PCA9539()
{
  _i2caddr = NULL;
  _port = NULL;
  _invport = NULL;
}

/**
 * @brief Initializes the device and performs initial I2C setup.
 *        This method should be called before any others are used.
 * @param {uint8_t} i2caddr - Sets the slave address of the PCA9539, defaults to 0x20.
*/
void PCA9539::begin(uint8_t i2caddr)
{
  _i2caddr = i2caddr;
  Wire.begin();
}

/**
 * @brief Configures the specified pin to behave either as an input, inverted input, or output.
 * @param {uint8_t} pin - Pin number whose mode you wish to set.
 * @param {uint8_t} mode - Pin mode one of: INPUT, INPUT_INVERTED, or OUTPUT.
*/
void PCA9539::pinMode(uint8_t pin, uint8_t mode)
{
  uint8_t confRegister = NULL;
  uint8_t invRegister = NULL;
  uint8_t bitPin = NULL;

  if ((pin >= 0) && (pin < 8))
  {
    confRegister = PCA9539_CONF0_REGISTER;
    invRegister = PCA9539_INV0_REGISTER;
    bitPin = pin;
  }

  if ((pin >= 8) && (pin < 16))
  {
    confRegister = PCA9539_CONF1_REGISTER;
    invRegister = PCA9539_INV1_REGISTER;
    bitPin = pin - 8;
  }

  switch (mode)
  {
  case OUTPUT:
  {
    // Clear the pin on the configuration register for output
    _port &= ~(1 << bitPin);
    break;
  }
  // case INPUT_INVERTED:
  case SPECIAL:
  {
    // Set the pin on the configuration register for input
    _port |= (1 << bitPin);
    // Set the pin on the polarity inversion register for inverted input
    _invport |= (1 << bitPin);
    break;
  }
  case INPUT:
  {
    // Set the pin on the configuration register for input
    _port |= (1 << bitPin);
    // Clear the pin on the polarity inversion register for normal input
    _invport &= ~(1 << bitPin);
    break;
  }
  default:
  {
    // Set the pin on the configuration register for input
    _port |= (1 << bitPin);
    // Clear the pin on the polarity inversion register for normal input
    _invport &= ~(1 << bitPin);
    break;
  }
  }

  // Write the configuration of the individual pins as inputs or outputs
  Wire.beginTransmission(_i2caddr);
  Wire.write(confRegister);
  Wire.write(_port);
  Wire.endTransmission();

  if ((mode == SPECIAL) || (mode == INPUT))
  {
    // Write the input polarity configuration of the individual pins
    Wire.beginTransmission(_i2caddr);
    Wire.write(invRegister);
    Wire.write(_invport);
    Wire.endTransmission();
  }
}

/**
 * @brief Writes a HIGH or a LOW value to a digital pin.
 * @param {uint8_t} pin - Pin number whose value you wish to set.
 * @param {uint8_t} value - Pin value one of: HIGH, or LOW.
*/
void PCA9539::digitalWrite(uint8_t pin, uint8_t value)
{
  uint8_t opRegister = NULL;
  uint8_t statusPin = NULL;
  uint8_t bitPin = NULL;

  if ((pin >= 0) && (pin < 8))
  {
    opRegister = PCA9539_OP0_REGISTER;
    bitPin = pin;
  }
  else if ((pin >= 8) && (pin < 16))
  {
    opRegister = PCA9539_OP1_REGISTER;
    bitPin = pin - 8;
  }
  else
  {
    return;
  }

  statusPin = readI2c(opRegister);

  switch (value)
  {
  case HIGH:
  { // Set the pin HIGH on the output register
    statusPin |= (1 << bitPin);
    break;
  }
  case LOW:
  {
    // Set the pin LOW on the output register
    statusPin &= ~(1 << bitPin);
    break;
  }
  default:
  {
    // Set the pin LOW on the output register
    statusPin &= ~(1 << bitPin);
    break;
  }
  }
  writeI2c(opRegister, statusPin);
}

/**
 * @brief Reads the value from a specified digital pin, either HIGH or LOW.
 * @note When using ESPECIAL on pinMode(), you will get the inverted status.
 * @param {uint8_t} pin - Pin number whose value you wish to get.
 * @returns {uint8_t} The status of the pin either HIGH or LOW.
*/
bool PCA9539::digitalRead(uint8_t pin)
{
  uint8_t ipRegister = NULL;
  uint8_t bitPin = NULL;
  int buff = false;

  if ((pin > 0) && (pin < 8))
  {
    ipRegister = PCA9539_IP0_REGISTER;
    bitPin = pin;
  }
  else if ((pin >= 8) && (pin < 16))
  {
    ipRegister = PCA9539_IP1_REGISTER;
    bitPin = pin - 8;
  }
  else
  {
    return false;
  }

  // We only need to read 1 byte of data to get the pins
  buff = readI2c(ipRegister);
  return (buff & (1 << bitPin)) ? HIGH : LOW;
}

/**
 * @brief REALIZA A LEITURA DO ENDERECO @param address
 * @param address ENDERECO DO REGISTRADOR A SER LIDO
 * @return RETORNA O VALOR RECEBIDO 
*/
int32_t PCA9539::readI2c(uint8_t address)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  _lastError = Wire.endTransmission();
  Wire.requestFrom(_i2caddr, (uint8_t)READ_ONE_BYTE);

  while (!Wire.available())
  {
    NOP();
  }
  return Wire.read();
}

/**
 * @brief REALIZA A GRAVACAO NO VALOR @param data NO @param address ENVIADO
 *        E ARMAZENA O RESULTADO DA TRANSMISSAO EM _lastError
 * @param address ENDERECO DO REGISTRADOR A SER GRAVADO
 * @param data VALOR A SER GRAVADO
*/
void PCA9539::writeI2c(uint8_t address, uint8_t data)
{
  Wire.beginTransmission(_i2caddr);
  Wire.write(address);
  Wire.write(data);
  _lastError = Wire.endTransmission();
}
