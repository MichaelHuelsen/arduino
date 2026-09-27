// Pins definieren
const int redPin = 11;
const int yellowPin = 10;
const int bluePin = 9;
const int soundPin = 7;

// Aktueller Status, boolean kann nur false/0 oder true/1 sein
// d.h. "not 0" = 1 und "not 1" = 0
// statt "not" kann man auch "!" schreiben
boolean yellowLedStatus = false;

// Wie lange warten nach Ton?
const int pauseDelay = 200;

void setup()
{
    // Pins konfigurieren und LEDs auf Start setzen
    Serial.begin(9600);
    pinMode(soundPin, INPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    digitalWrite(yellowPin, yellowLedStatus);
    digitalWrite(redPin, !yellowLedStatus);
}

void loop()
{
    // Digitalpin 7 auslesen und bei LOW umschalten
    int din = digitalRead(soundPin);
    if (!din)
    {
        yellowLedStatus = !yellowLedStatus;
        digitalWrite(yellowPin, yellowLedStatus);
        digitalWrite(redPin, !yellowLedStatus);
        // Das HIGH ist nicht ganz logisch, da am Pin ja eigentlich ein LOW anliegt :)
        Serial.println("HIGH!");
        delay(pauseDelay);
    }
}