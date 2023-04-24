int LED_SEG_A_PIN;
int LED_SEG_B_PIN;
int LED_SEG_C_PIN;
int LED_SEG_D_PIN;
int LED_SEG_E_PIN;
int LED_SEG_F_PIN;
int LED_SEG_G_PIN;
int LED_SEG_DOT_PIN;
boolean isDotActive = false;

void turnOffDisplay()
{
    digitalWrite(LED_SEG_A_PIN, LOW);
    digitalWrite(LED_SEG_B_PIN, LOW);
    digitalWrite(LED_SEG_C_PIN, LOW);
    digitalWrite(LED_SEG_D_PIN, LOW);
    digitalWrite(LED_SEG_E_PIN, LOW);
    digitalWrite(LED_SEG_F_PIN, LOW);
    digitalWrite(LED_SEG_G_PIN, LOW);
}

void toggleDot()
{
    if (isDotActive == true)
    {
        digitalWrite(LED_SEG_DOT_PIN, HIGH);
        isDotActive = false;
    }
    else
    {
        digitalWrite(LED_SEG_DOT_PIN, LOW);
        isDotActive = true;
    }
}

void displayDigit(byte digit)
{
    turnOffDisplay();
    if (digit > 9)
    {
        return;
    }

    // Conditions for displaying segment a
    if (digit != 1 && digit != 4)
    {
        digitalWrite(LED_SEG_A_PIN, HIGH);
    }

    // Conditions for displaying segment b
    if (digit != 5 && digit != 6)
    {
        digitalWrite(LED_SEG_B_PIN, HIGH);
    }

    // Conditions for displaying segment c
    if (digit != 2)
    {
        digitalWrite(LED_SEG_C_PIN, HIGH);
    }

    // Conditions for displaying segment d
    if (digit != 1 && digit != 4 && digit != 7)
    {
        digitalWrite(LED_SEG_D_PIN, HIGH);
    }

    // Conditions for displaying segment e
    if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    {
        digitalWrite(LED_SEG_E_PIN, HIGH);
    }

    // Conditions for displaying segment f
    if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    {
        digitalWrite(LED_SEG_F_PIN, HIGH);
    }

    if (digit != 0 && digit != 1 && digit != 7)
    {
        digitalWrite(LED_SEG_G_PIN, HIGH);
    }
}

void initSevenSegment(
    int a,
    int b,
    int c,
    int d,
    int e,
    int f,
    int g,
    int dot)
{
    LED_SEG_A_PIN = a;
    LED_SEG_B_PIN = b;
    LED_SEG_C_PIN = c;
    LED_SEG_D_PIN = d;
    LED_SEG_E_PIN = e;
    LED_SEG_F_PIN = f;
    LED_SEG_G_PIN = g;
    LED_SEG_DOT_PIN = dot;

    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(dot, OUTPUT);

    Serial.println("Seven Segment Display initialized");
}