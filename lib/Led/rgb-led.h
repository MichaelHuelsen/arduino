
int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int d = 500; // delay

void setup()
{
    // put your setup code here, to run once:
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
#endif
    analogWrite(redPin, red);
    analogWrite(bluePin, blue);
    analogWrite(greenPin, green);
}

void rgbStartSignal()
{
    int d2 = 100;
    int max = 5;
    for (int i = 0; i < max; i++)
    {
        setColor(255, 0, 0);
        delay(d2);
        setColor(0, 255, 0);
        delay(d2);
    }
}

void rgbStandard()
{
    setColor(255, 0, 0); // red
    delay(d);
    setColor(0, 255, 0); // green
    delay(d);
    setColor(0, 0, 255); // blue
    delay(d);
}

void rgbRandom(int n)
{
    for (int i = 0; i < n; i++)
    {
        int r = random(255);
        int g = random(255);
        int b = random(255);
        setColor(r, g, b);
        delay(d);
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
    rgbStartSignal();
    rgbStandard();
    rgbRandom(3);
}
