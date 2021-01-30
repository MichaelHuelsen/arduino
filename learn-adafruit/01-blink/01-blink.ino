/*
  Blink the on board LED
 */

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop()
{
  int d = 1000;
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(d);             // wait for a second
  digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
  delay(d);             // wait for a second
}
