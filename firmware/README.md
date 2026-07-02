# Firmware — ESP8266 (NodeMCU)

This directory documents the embedded firmware that runs on the pot's
ESP8266 (NodeMCU) controller.

> **Why only a sample is published**
> The full sketch (calibration constants, autonomous watering
> thresholds, VPD/dew-point math, Firebase history-log writer, cooldown
> tuning) is kept private so the finished, deployable firmware can't be
> lifted directly from GitHub. `examples/akilli_ziraat.example.ino`
> shows the real file structure, pin map, libraries and program flow —
> the tuned logic bodies are stubbed out and documented instead of
> included verbatim. The complete `.ino` is available on request for
> academic review (advisor / jury).

## Hardware

| Component | Role |
|---|---|
| ESP8266 NodeMCU (CH340) | Main controller, Wi-Fi |
| DS18B20 | Waterproof digital temperature sensor (±0.5 °C) |
| Analog soil-moisture probe | Corrosion-resistant capacitive/resistive probe |
| L9110 | Dual-channel DC motor driver |
| Mini submersible pump | 120 L/H |
| RGB LED | Ambient light indicator, remotely controllable |

See [`/assets/hardware`](../assets/hardware) and
[`/assets/diagrams/system-architecture-sequence.jpg`](../assets/diagrams/system-architecture-sequence.jpg)
for the wiring and the Flutter → Firebase → ESP8266 sequence diagram.

## Data cycle (summary)

1. Every ~5 s the board reads soil moisture + temperature.
2. Values are pushed to Firebase Realtime Database under the device's
   node (`/{DEVICE_ID}/...`).
3. The Flutter app listens to that node via a `StreamBuilder` and
   updates the UI in ~250–400 ms (measured, see thesis §7.1.1).
4. When the user taps **Sula** (Water), the app flips a `motor_durum`
   flag; the firmware's Firebase listener catches the change and pulses
   the relay for a configurable duration, then resets the flag.
5. An autonomous loop compares the live moisture reading against the
   user-configured target (`ideal/nem`) with a hysteresis margin and a
   `millis()`-based cooldown, to avoid pump oscillation and
   over-watering.

## Firebase JSON shape (redacted example)

```json
{
  "000000": {
    "isim": "Kaktüs",
    "sicaklik": 21.25,
    "nem": 0,
    "motor_durum": 0,
    "isik_bilgisi": 0,
    "ai": 0,
    "dogrulama_kodu": 123,
    "ideal": { "nem": 50, "sicaklik": 22 },
    "sicaklik_gecmis": { "1": { "sicaklik": 21.4, "tarih": "…" } },
    "nem_gecmis": { "1": { "nem": 42, "tarih": "…" } }
  }
}
```

## Setup

1. Arduino IDE → **File > Preferences** → add to
   *Additional Boards Manager URLs*:
   `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
2. Install the **ESP8266** board package and the libraries listed in
   `examples/akilli_ziraat.example.ino`.
3. Copy `examples/config.example.h` → `config.h` and fill in your own
   Wi-Fi and Firebase credentials (this file is git-ignored).
4. Flash the board and monitor at 115200 baud.
