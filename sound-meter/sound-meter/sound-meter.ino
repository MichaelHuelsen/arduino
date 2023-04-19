// Pins definieren
const int redPin = 11;
const int yellowPin = 10;
const int bluePin = 9;
const int soundPin = 7;

// Aktueller Status, boolean kann nur false/0 oder true/1 sein
// d.h. "not 0" = 1 und "not 1" = 0
// statt "not" kann man auch "!" schreiben
boolean redLedStatus = true;
boolean yellowLedStatus = false;
boolean blueLedStatus = false;

// Wie lange warten nach Ton?
const int pauseDelay = 200;

void setup()
{
    // Pins konfigurieren und LEDs auf Start setzen
    Serial.begin(9600);

    pinMode(soundPin, INPUT);
    pinMode(bluePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);

    digitalWrite(bluePin, blueLedStatus);
    digitalWrite(yellowPin, yellowLedStatus);
    digitalWrite(redPin, redLedStatus);
}

void switchLed()
{

    if (redLedStatus)
    {
        redLedStatus = false;
        yellowLedStatus = true;
        writeLedStatus();
        return;
    }

    if (yellowLedStatus)
    {
        yellowLedStatus = false;
        blueLedStatus = true;
        writeLedStatus();
        return;
    }
    if (blueLedStatus)
    {
        blueLedStatus = false;
        redLedStatus = true;
        writeLedStatus();
        return;
    }
}

void writeLedStatus()
{

    digitalWrite(bluePin, blueLedStatus);
    digitalWrite(yellowPin, yellowLedStatus);
    digitalWrite(redPin, redLedStatus);
}

void loop()
{
    // Digitalpin 7 auslesen und bei LOW umschalten
    int din = digitalRead(soundPin);
    if (!din)
    {
        switchLed();

        /*
        redLedStatus = !redLedStatus;
        digitalWrite(redPin, !redLedStatus);
        digitalWrite(yellowPin, redLedStatus);
        */
        delay(pauseDelay);
    }
}