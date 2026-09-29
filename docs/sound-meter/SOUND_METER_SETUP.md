# Sound Meter Setup

A multi-component sound detection circuit with 7-segment display output and LED indicator rings.

## Components Required

### Sound Detection
- **Sound Sensor Module** (KY-037 or similar): Detects sound and outputs digital signal
  - Sensitivity adjustment: Built-in potentiometer for calibration
  - Analog output: Optional for sound level reading

### LEDs & Resistors
- **3× RGB/Status LEDs** (Red, Yellow, Blue):
  - 1× 330Ω resistor (for each LED)
  - Used for sound detection indication in rotating pattern

### 7-Segment Display
- **Common Cathode 7-Segment Display** (e.g., LTS-4301):
  - Displays sound detection counter (0-9)
  - Decimal point for additional status indication

### Additional
- Arduino board (Uno, Nano, Mega)
- Jumper wires
- Breadboard
- 5V power supply

## Wiring Diagram

```
Sound Sensor (KY-037)
├─ VCC → 5V
├─ GND → GND
├─ DO (Digital Output) → Pin 7 (SOUND_METER_SOUND_PIN)
└─ AO (Analog Output) → A0 (SOUND_METER_ANALOG_PIN)

LED Indicators
├─ Red LED (+ resistor) → Pin 11 (SOUND_METER_RED_PIN) → GND
├─ Yellow LED (+ resistor) → Pin 10 (SOUND_METER_YELLOW_PIN) → GND
└─ Blue LED (+ resistor) → Pin 9 (SOUND_METER_BLUE_PIN) → GND

7-Segment Display (Common Cathode)
├─ Segment A → Pin 13 (SOUND_METER_LED_SEG_A_PIN)
├─ Segment B → Pin 12 (SOUND_METER_LED_SEG_B_PIN)
├─ Segment C → Pin 4 (SOUND_METER_LED_SEG_C_PIN)
├─ Segment D → Pin 5 (SOUND_METER_LED_SEG_D_PIN)
├─ Segment E → Pin 6 (SOUND_METER_LED_SEG_E_PIN)
├─ Segment F → Pin 8 (SOUND_METER_LED_SEG_F_PIN)
├─ Segment G → Pin 7 (SOUND_METER_LED_SEG_G_PIN)
├─ Decimal Point → Pin 3 (SOUND_METER_LED_SEG_DOT_PIN)
└─ Common Cathode → GND
```

## How It Works

1. **Sound Detection**: The KY-037 sensor detects sound and outputs a LOW digital signal when sound is detected
2. **LED Rotation**: Each sound detection triggers the next LED in sequence (Red → Yellow → Blue → Red)
3. **Counter Display**: Each detection increments a counter (0-9) displayed on the 7-segment display
4. **Debouncing**: 200ms delay prevents false triggers from sensor noise

## Pinout Summary

| Component | Pin | Type | Purpose |
|-----------|-----|------|---------|
| Sound Sensor | 7 | Digital Input | Sound detection trigger |
| Sound Sensor | A0 | Analog Input | Sound level reading (optional) |
| Red LED | 11 | Digital Output | Status indicator |
| Yellow LED | 10 | Digital Output | Status indicator |
| Blue LED | 9 | Digital Output | Status indicator |
| 7-Seg A | 13 | Digital Output | Segment control |
| 7-Seg B | 12 | Digital Output | Segment control |
| 7-Seg C | 4 | Digital Output | Segment control |
| 7-Seg D | 5 | Digital Output | Segment control |
| 7-Seg E | 6 | Digital Output | Segment control |
| 7-Seg F | 8 | Digital Output | Segment control |
| 7-Seg G | 7 | Digital Output | Segment control |
| 7-Seg DOT | 3 | Digital Output | Decimal point |

## Calibration

1. Power up the system
2. Adjust the **sensitivity potentiometer** on the KY-037 module
3. Test detection by making sounds near the sensor
4. Fine-tune until reliable detection without false positives

## Code Files

- `setup_sound_meter.h` - Header file with function declarations
- `setup_sound_meter.cpp` - Complete implementation with helper functions

## Usage

In `main.cpp`, activate the sound meter setup:

```cpp
#define ACTIVE_SETUP_SOUND_METER  // Uncomment this line
// #define ACTIVE_SETUP_LED       // Comment out other setups
```

Then upload to your Arduino board.

## Future Enhancements

- Add analog sound level display
- Implement different sensitivity modes
- Add EEPROM to save calibration values
- Create a frequency analyzer (with FFT)
- Add wireless communication for remote monitoring
