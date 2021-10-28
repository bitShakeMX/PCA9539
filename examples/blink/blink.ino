/* Example usage for PCA9539 library by Alfonso Martinez Alcantara.
   Demonstrates the use of output of the PCA9539.

*/

#include <Arduino.h>
#include <PCA9539.h>

#define PIN_LED	9  		// LED connected to GPIO-0 as output
#define PIN_BTN 8

PCA9539 EXPANSOR;

void setup()
{
  Serial.begin(115200);

  EXPANSOR.begin();
  EXPANSOR.pinMode(PIN_LED, OUTPUT);
  EXPANSOR.pinMode(PIN_BTN, INPUT);
}

void loop()
{
  Serial.println("HIGH");
  EXPANSOR.digitalWrite(PIN_LED, HIGH);
  delay(2000);
  Serial.println("LOW");
  EXPANSOR.digitalWrite(PIN_LED, LOW);
  delay(2000);

  Serial.printf("BTN %d\n", EXPANSOR.digitalRead(PIN_BTN));
  delay(1000);
}
