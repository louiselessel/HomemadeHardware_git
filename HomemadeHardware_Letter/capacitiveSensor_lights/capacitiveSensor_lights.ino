#include <CapacitiveSensor.h>

/*
   Based on CapitiveSense Library Demo Sketch from Paul Badger 2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/

/*
  Code by Louise Lessél
  Blink based on capacitive sensor onboard the PCB board. Using a 1 Mega Ohm resistor.
*/
#define pin 0 // Lights on (MOSI) bottom right opposite of dot
CapacitiveSensor   cs = CapacitiveSensor(3, 4); // 1 megohm resistor between pins 3 and 4, pin 4 is sensor pin where capacitor links to

int currentLevel = 0;
int change = 1;

void setup()
{
  // lights
  pinMode(pin, OUTPUT);

  // Capacitive sensor
  cs.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);

}

void loop()
{
  long start = millis();
  long reading =  cs.capacitiveSensor(30);
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug window spacing


  Serial.println(reading);

  if (reading > 500) {
    digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
    delay(50);                       // wait for a second
  } else {
    // add change to brightness:
    currentLevel = currentLevel + change;
    // and constrain:
    currentLevel = constrain(currentLevel, 2, 254);
    // if brightness is at either extreme, change the
    // direction of fading:
    if (currentLevel == 2 || currentLevel == 254) {
      change = -change;
    }
    // change the light:
    analogWrite(pin, currentLevel);
    delay(5);
  }
}
