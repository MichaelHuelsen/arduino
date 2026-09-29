#include <Arduino.h>
#include <HardwareSerial.h>
#include <config.h>
#include <seven_segment.h>

// Pin configuration
const int SOUND_METER_RED_PIN = 11;
const int SOUND_METER_YELLOW_PIN = 10;
const int SOUND_METER_BLUE_PIN = 9;
const int SOUND_METER_SOUND_PIN = 2;
const int SOUND_METER_ANALOG_PIN = A0;

// 7-segment display pins
const int SOUND_METER_LED_SEG_A_PIN = 13;
const int SOUND_METER_LED_SEG_B_PIN = 12;
const int SOUND_METER_LED_SEG_C_PIN = 4;
const int SOUND_METER_LED_SEG_D_PIN = 5;
const int SOUND_METER_LED_SEG_E_PIN = 6;
const int SOUND_METER_LED_SEG_F_PIN = 8;
const int SOUND_METER_LED_SEG_G_PIN = 7;
const int SOUND_METER_LED_SEG_DOT_PIN = 3;

// State variables
static boolean soundMeterRedStatus = true;
static boolean soundMeterYellowStatus = false;
static boolean soundMeterBlueStatus = false;
static int soundMeterCounter = 0;
static const int SOUND_METER_PAUSE_DELAY = 200;

// Forward declarations
static void switchSoundMeterLed();
static void writeSoundMeterLedStatus();

void setup_sound_meter_init() {
  Serial.println("Sound meter setup initialized");

  // Configure sound/LED pins
  pinMode(SOUND_METER_SOUND_PIN, INPUT);
  pinMode(SOUND_METER_BLUE_PIN, OUTPUT);
  pinMode(SOUND_METER_YELLOW_PIN, OUTPUT);
  pinMode(SOUND_METER_RED_PIN, OUTPUT);

  // Initialize 7-segment display using library
  initSevenSegment(SOUND_METER_LED_SEG_A_PIN, SOUND_METER_LED_SEG_B_PIN,
                   SOUND_METER_LED_SEG_C_PIN, SOUND_METER_LED_SEG_D_PIN,
                   SOUND_METER_LED_SEG_E_PIN, SOUND_METER_LED_SEG_F_PIN,
                   SOUND_METER_LED_SEG_G_PIN, SOUND_METER_LED_SEG_DOT_PIN);

  // Set initial LED states
  digitalWrite(SOUND_METER_BLUE_PIN, soundMeterBlueStatus);
  digitalWrite(SOUND_METER_YELLOW_PIN, soundMeterYellowStatus);
  digitalWrite(SOUND_METER_RED_PIN, soundMeterRedStatus);

  displayDigit(soundMeterCounter);
  Serial.println("Sound meter ready");
}

void setup_sound_meter_loop() {
  int din = digitalRead(SOUND_METER_SOUND_PIN);
  int sensorValue = analogRead(SOUND_METER_ANALOG_PIN);

  if (!din) {
    Serial.print("Sound detected! | Level: ");
    Serial.print(sensorValue);
    Serial.print(" | Counter: ");
    Serial.println(soundMeterCounter + 1);
    
    switchSoundMeterLed();
    delay(SOUND_METER_PAUSE_DELAY);
  }
}

// Helper functions (static to keep them local to this file)
static void switchSoundMeterLed() {
  if (soundMeterRedStatus) {
    soundMeterRedStatus = false;
    soundMeterYellowStatus = true;
    writeSoundMeterLedStatus();
    return;
  }

  if (soundMeterYellowStatus) {
    soundMeterYellowStatus = false;
    soundMeterBlueStatus = true;
    writeSoundMeterLedStatus();
    return;
  }

  if (soundMeterBlueStatus) {
    soundMeterBlueStatus = false;
    soundMeterRedStatus = true;
    writeSoundMeterLedStatus();
    return;
  }
}

static void writeSoundMeterLedStatus() {
  digitalWrite(SOUND_METER_BLUE_PIN, soundMeterBlueStatus);
  digitalWrite(SOUND_METER_YELLOW_PIN, soundMeterYellowStatus);
  digitalWrite(SOUND_METER_RED_PIN, soundMeterRedStatus);

  soundMeterCounter++;
  if (soundMeterCounter > 9) {
    soundMeterCounter = 0;
  }

  char ledStatus[20];
  if (soundMeterRedStatus) {
    strcpy(ledStatus, "RED");
  } else if (soundMeterYellowStatus) {
    strcpy(ledStatus, "YELLOW");
  } else {
    strcpy(ledStatus, "BLUE");
  }

  Serial.print("[LED] ");
  Serial.print(ledStatus);
  Serial.print(" | Display: ");
  Serial.println(soundMeterCounter);

  displayDigit(soundMeterCounter);
}
