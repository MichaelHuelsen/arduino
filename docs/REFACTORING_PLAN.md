# Sound Meter Refactoring Guide

## Current State
The sound meter setup duplicates logic that already exists in the `lib/` folder.

## Refactoring Opportunities

### ✅ Already Identified Reusable Components

| Component | Location | Can Use | Notes |
|-----------|----------|---------|-------|
| 7-Segment Display | `lib/display/seven-segment.h` | ✓ YES | Duplicated logic in sound_meter.cpp |
| LED Control | `lib/led/led.h` | ✓ PARTIAL | Has single LED class, need multi-LED manager |

### Components to Extract

#### 1. **7-Segment Display** (HIGH PRIORITY)
Currently, sound meter duplicates the entire 7-segment display logic.

**Current duplication:**
```cpp
// In setup_sound_meter.cpp (lines 120-160)
static void displayDigit(byte digit) { ... }
static void turnOffDisplay() { ... }
static void toggleDot() { ... }
```

**Better approach:**
Use `lib/display/seven-segment.h` - it already has all these functions!

```cpp
#include <seven-segment.h>

void setup_sound_meter_init() {
  // Initialize the 7-segment display
  initSevenSegment(
    SOUND_METER_LED_SEG_A_PIN,
    SOUND_METER_LED_SEG_B_PIN,
    SOUND_METER_LED_SEG_C_PIN,
    SOUND_METER_LED_SEG_D_PIN,
    SOUND_METER_LED_SEG_E_PIN,
    SOUND_METER_LED_SEG_F_PIN,
    SOUND_METER_LED_SEG_G_PIN,
    SOUND_METER_LED_SEG_DOT_PIN
  );
  // ... rest of init
}

void loop() {
  // ... detection logic
  displayDigit(soundMeterCounter);  // Use lib function
}
```

**Benefit:** Eliminates ~40 lines of duplicated code

---

#### 2. **LED Ring Manager** (NEW LIBRARY)
The sound meter uses a rotating LED pattern (Red → Yellow → Blue). This pattern is generic and could be reused.

**Suggested new library:** `lib/led/led-ring.h`

```cpp
// lib/led/led_ring.h
#ifndef LED_RING_H
#define LED_RING_H

class LedRing {
public:
  LedRing(int redPin, int yellowPin, int bluePin);
  void begin();
  void next();  // Rotate to next LED
  
private:
  int _redPin, _yellowPin, _bluePin;
  int _currentIndex;
};

#endif
```

**Current sound meter code:**
```cpp
// Manual LED rotation (lines 82-105)
static void switchSoundMeterLed() {
  if (soundMeterRedStatus) {
    soundMeterRedStatus = false;
    soundMeterYellowStatus = true;
    writeSoundMeterLedStatus();
    return;
  }
  // ... more manual switching
}
```

**With LedRing library:**
```cpp
LedRing ledRing(11, 10, 9);
ledRing.begin();
ledRing.next();  // Simple one-liner to rotate
```

**Benefit:** Reusable for any multi-LED indicator system

---

#### 3. **Sound Sensor** (NEW LIBRARY)
A simple sound sensor wrapper for consistent usage.

**Suggested new library:** `lib/sensors/sound-sensor.h`

```cpp
#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

class SoundSensor {
public:
  SoundSensor(int digitalPin, int analogPin = -1);
  void begin();
  boolean isTriggered();      // Returns true if sound detected
  int getLevel();             // Returns analog sound level
  
private:
  int _digitalPin;
  int _analogPin;
  const int DEBOUNCE_DELAY = 200;
};

#endif
```

**Current code:**
```cpp
int din = digitalRead(SOUND_METER_SOUND_PIN);
int sensorValue = analogRead(SOUND_METER_ANALOG_PIN);
if (!din) { ... }
```

**With SoundSensor library:**
```cpp
SoundSensor sensor(7, A0);
if (sensor.isTriggered()) {
  Serial.println("Sound: " + String(sensor.getLevel()));
}
```

**Benefit:** Encapsulates sensor logic, handles debouncing automatically

---

## Refactoring Implementation Steps

### Phase 1: Use Existing 7-Segment Library (Quick Win)
1. Remove duplicate display functions from `setup_sound_meter.cpp`
2. Add `#include <seven-segment.h>` 
3. Call `initSevenSegment(...)` in setup
4. Call `displayDigit(...)` from the library
5. **Result:** ~40 lines removed, same functionality

### Phase 2: Create LED Ring Library (Reusable)
1. Create `lib/led/led_ring.h` and `lib/led/led_ring.cpp`
2. Implement multi-LED rotation logic
3. Refactor sound meter to use `LedRing` class
4. **Result:** Sound meter becomes much simpler, LED ring available for other projects

### Phase 3: Create Sound Sensor Library (Optional)
1. Create `lib/sensors/sound_sensor.h`
2. Implement debouncing and level reading
3. Refactor sound meter setup
4. **Result:** Cleaner sensor interface, debouncing built-in

---

## Proposed Refactored Sound Meter Code

After all refactoring:

```cpp
#include <Arduino.h>
#include <config.h>
#include <seven-segment.h>
#include <led_ring.h>
#include <sound_sensor.h>

// Configuration
const int SOUND_SENSOR_DIG_PIN = 7;
const int SOUND_SENSOR_ANA_PIN = A0;
const int LED_RED = 11;
const int LED_YELLOW = 10;
const int LED_BLUE = 9;
const int SEG_A = 13, SEG_B = 12, SEG_C = 4, SEG_D = 5;
const int SEG_E = 6, SEG_F = 8, SEG_G = 7, SEG_DOT = 3;

// Instances
static SoundSensor soundSensor(SOUND_SENSOR_DIG_PIN, SOUND_SENSOR_ANA_PIN);
static LedRing ledRing(LED_RED, LED_YELLOW, LED_BLUE);
static int counter = 0;

void setup_sound_meter_init() {
  Serial.println("Sound meter setup initialized");
  
  soundSensor.begin();
  ledRing.begin();
  initSevenSegment(SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DOT);
  
  displayDigit(counter);
  Serial.println("Sound meter ready");
}

void setup_sound_meter_loop() {
  if (soundSensor.isTriggered()) {
    counter = (counter + 1) % 10;
    
    Serial.print("Sound detected! | Level: ");
    Serial.print(soundSensor.getLevel());
    Serial.print(" | Counter: ");
    Serial.println(counter);
    
    ledRing.next();
    displayDigit(counter);
  }
}
```

**Comparison:**
- **Before:** 200+ lines with duplicated logic
- **After:** ~50 lines, clean and maintainable

---

## Recommendation

**Start with Phase 1 (7-Segment)** — it's the quickest win:
- Use existing library code
- Remove 40 lines from sound meter
- No new files needed
- Same functionality

**Then Phase 2 (LED Ring)** — for reusability:
- Create small, focused library
- Makes sound meter simpler
- Available for other projects

**Phase 3 (Sound Sensor)** — nice to have:
- Completes the abstraction
- Adds built-in debouncing
- Makes code more readable
