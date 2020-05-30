/* Example usage for PCA9539 library by Alfonso Martinez Alcantara.
 * Demonstrates the use of output of the PCA9539.
 *
 */

#include "PCA9539.h"

#define PIN_LED	0  		// LED connected to GPIO-0 as output

PCA9539 gpio;


void setup() {
  gpio.begin();
  gpio.pinMode(PIN_LED, OUTPUT);
}

void loop() {
  gpio.digitalWrite(PIN_LED, HIGH); 
  delay(500);
  gpio.digitalWrite(PIN_LED, LOW); 
  delay(500);
}
