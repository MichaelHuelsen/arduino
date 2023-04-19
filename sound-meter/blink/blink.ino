
int redLED = 13;
int delayMs = 1000;

void setup()
{
  pinMode(redLED, OUTPUT);
}

void waitASec()
{
  delay(delayMs);
}

void loop()
{
  digitalWrite(redLED, HIGH);
  waitASec();
  digitalWrite(13, LOW);
  waitASec();
}
