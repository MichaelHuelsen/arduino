
#define LED_PIN 12
#define RED_LED_PIN 11
#define YELLOW_LED_PIN 10
#define BLUE_LED_PIN 9

int delayMs = 250;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
}

void waitASec()
{
    delay(delayMs);
}

void blink()
{
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, HIGH);
    waitASec();
    digitalWrite(YELLOW_LED_PIN, HIGH);
    waitASec();
    digitalWrite(BLUE_LED_PIN, HIGH);
    waitASec();
    digitalWrite(LED_PIN, LOW);
    waitASec();
    digitalWrite(RED_LED_PIN, LOW);
    waitASec();
    digitalWrite(YELLOW_LED_PIN, LOW);
    waitASec();
    digitalWrite(BLUE_LED_PIN, LOW);
    waitASec();
}

void loop()
{

    blink();
    waitASec();
}