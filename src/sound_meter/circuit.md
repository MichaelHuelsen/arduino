# Sound Meter Circuit

## Components Required

### Sound Detection
- **Sound Sensor Module** (KY-037 or similar)
  - Detects sound and outputs digital signal
  - Built-in sensitivity adjustment potentiometer
  - Optional analog output for sound level

### LEDs & Resistors
- **Red LED** + 330Ω resistor
- **Yellow LED** + 330Ω resistor
- **Blue LED** + 330Ω resistor

### 7-Segment Display
- **Common Cathode 7-Segment Display** (e.g., LTS-4301)
- Displays sound detection counter (0-9)

### General
- Arduino board (Uno, Nano, Mega, etc.)
- Breadboard
- Jumper wires
- 5V power supply

## Wiring Diagram

```
                          ┌─────────────────┐
                          │  Sound Sensor   │
                          │   (KY-037)      │
                          └─────────────────┘
                          VCC  GND  DO  AO
                           │    │    │    │
                           ├────┼────┼────┘
                          5V   GND  P7  A0
                          
┌─────────────────────────────────────────────────────────────┐
│                     Arduino Board                           │
│                                                             │
│  Digital Pins:                                              │
│  ┌─────────────────────────────────────────────────────┐   │
│  │ P3:  7-Seg Dot        │ P11: Red LED                │   │
│  │ P4:  7-Seg D          │ P12: 7-Seg B               │   │
│  │ P5:  7-Seg E          │ P13: 7-Seg A               │   │
│  │ P6:  7-Seg F          │                             │   │
│  │ P7:  7-Seg G & Sound  │ Analog:                     │   │
│  │ P8:  7-Seg F          │ A0: Sound Level (optional)  │   │
│  │ P9:  Blue LED         │                             │   │
│  │ P10: Yellow LED       │                             │   │
│  └─────────────────────────────────────────────────────┘   │
│                                                             │
│  Connections:                                               │
│  5V ──────────────── LEDs (via 330Ω resistors)              │
│  GND ───────────────── All grounds                          │
└─────────────────────────────────────────────────────────────┘

┌──────────────────────┐      ┌──────────────┐
│   7-Segment Display  │      │  LED Ring    │
│  (Common Cathode)    │      │              │
│                      │      │  ╔═════════╗ │
│    ┌───────┐         │      │  ║  🔴 RED  ║ │
│    │ a b c │         │      │  ║ 🟡 YELLOW║ │
│  f │       │ b       │      │  ║  🔵 BLUE ║ │
│    │ g d e │         │      │  ╚═════════╝ │
│    └───────┘         │      │              │
│      .dot            │      │ (rotates on  │
│                      │      │  detection)  │
│    Connected to      │      │              │
│    P13-P3, P4-P8     │      └──────────────┘
└──────────────────────┘
```

## Pin Configuration

| Component | Pin | Direction | Function |
|-----------|-----|-----------|----------|
| Sound Sensor DO | 7 | Input | Sound detection trigger |
| Sound Sensor AO | A0 | Input (Analog) | Optional: sound level |
| Red LED | 11 | Output | Status indicator |
| Yellow LED | 10 | Output | Status indicator |
| Blue LED | 9 | Output | Status indicator |
| 7-Seg A | 13 | Output | Segment A control |
| 7-Seg B | 12 | Output | Segment B control |
| 7-Seg C | 4 | Output | Segment C control |
| 7-Seg D | 5 | Output | Segment D control |
| 7-Seg E | 6 | Output | Segment E control |
| 7-Seg F | 8 | Output | Segment F control |
| 7-Seg G | 7 | Output | Segment G control |
| 7-Seg DOT | 3 | Output | Decimal point |

## How It Works

1. **Sound Detection**: KY-037 sensor outputs LOW when sound is detected
2. **LED Rotation**: Each detection cycles through Red → Yellow → Blue → Red
3. **Counter**: Increments 0-9 on each detection, wraps around
4. **Display**: 7-segment display shows current counter value
5. **Debounce**: 200ms delay prevents false triggers

## Calibration

1. Power up the circuit
2. Locate the **sensitivity potentiometer** on the KY-037 module
3. Rotate the potentiometer to adjust sensitivity:
   - Clockwise: Less sensitive (requires louder sound)
   - Counter-clockwise: More sensitive (detects quiet sounds)
4. Test with sounds to find optimal setting

## Assembly Tips

- Keep sound sensor away from direct vibration sources
- Shield sensor from high ambient noise if needed
- Use common cathode 7-segment display
- Ensure proper resistor values to prevent LED burnout
- Check polarity of LEDs (long leg = positive)

## Code Interface

The setup uses two public functions:
- `setup_sound_meter_init()` - Initialize pins and state
- `setup_sound_meter_loop()` - Main loop logic

Internal state is managed statically within the .cpp file.
