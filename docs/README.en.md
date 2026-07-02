<div align="center">

<img src="../assets/images/banner.jpg" alt="Akıllı Ziraat" width="100%" />

# 🌱 Akıllı Ziraat
### IoT-Based Smart Plant Management & Analysis System

[**🇹🇷 Bu sayfayı Türkçe oku**](README.tr.md) · [⬅ Back to root](../README.md)

</div>

---

## Table of Contents

- [About](#about)
- [Why](#why)
- [Key Features](#key-features)
- [System Architecture](#system-architecture)
- [Hardware](#hardware)
- [The Biophysical Lab (VPD)](#the-biophysical-lab-vpd)
- [App Screenshots](#app-screenshots)
- [Tech Stack](#tech-stack)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Results](#results)
- [Roadmap](#roadmap)
- [Author & Acknowledgments](#author--acknowledgments)
- [License](#license)

---

## About

**Akıllı Ziraat** ("Smart Agriculture") is an end-to-end IoT system that
takes care of a houseplant so its owner doesn't have to remember to.
An ESP8266-powered pot continuously measures soil moisture and
temperature, streams the data to Firebase in real time, and can
autonomously water the plant when it needs it — while a cross-platform
Flutter app (Android / iOS / Web) lets the owner watch, control, and
understand what's happening, including a **biophysical stress
analysis** based on Vapor Pressure Deficit (VPD).

This project was designed, built, and written up **solo**, end to end
— firmware, cloud schema, mobile/web UI, biophysical math, and the
accompanying thesis — as a Computer Engineering graduation project at
**Tekirdağ Namık Kemal University**, under the supervision of
**Dr. Öğr. Üyesi Halil Nusret BULUŞ**. Project management (backlog,
3 Agile sprints, RACI matrix, Gantt chart) was likewise run solo, using
standard Scrum artifacts to structure the 14-week build.

> 📄 The complete thesis (Turkish) is included in [`/docs/thesis`](thesis)
> for reference, alongside the defense presentation.

## Why

Modern life pulls people away from the day-to-day attention that
indoor plants need. The two most common failure modes are entirely
preventable:

1. **Neglect** — forgetting to water, leading to a dried-out plant.
2. **Overwatering** — watering "just in case," leading to root rot.

Akıllı Ziraat replaces guesswork with continuous sensing, a
configurable target range, and a science-based read on how much stress
the plant is actually under — not just how wet the soil happens to be
right now.

## Key Features

- 🔄 **Real-time monitoring** — soil moisture & temperature streamed to
  the app in ~250–400 ms via Firebase Realtime Database.
- 💧 **Autonomous watering** — a hysteresis + cooldown algorithm
  prevents both under- and over-watering and protects the relay from
  rapid on/off cycling.
- 🧪 **Biophysical Lab** — computes **Vapor Pressure Deficit (VPD)**
  and dew point from live temperature/humidity to quantify plant
  transpiration stress, not just raw sensor values.
- 🤖 **AI-assisted interpretation** — a plain-language assistant (rule
  engine + Gemini) turns sensor + VPD data into actionable advice
  ("your plant is losing water too fast, move it out of direct light").
- 📱 **Cross-platform app** — a single Flutter codebase ships to
  Android, iOS, and Web with light/dark themes.
- 🔐 **Secure device pairing** — a two-step Device-ID + verification
  code flow (2FA-style) before a pot can be linked to an account.
- 📈 **History & charts** — temperature/moisture history logged with
  timestamps and rendered with `fl_chart`.
- 🔔 **Push notifications** — Firebase Cloud Messaging alerts for
  critical thresholds (e.g. frost risk below 15 °C).

## System Architecture

<div align="center">
<img src="../assets/diagrams/system-overview.jpg" alt="System overview — outdoor field & indoor pot variants" width="90%" />
</div>

The platform was scoped for two deployment shapes — a field-scale
sensor network and the indoor smart-pot variant that was fully
implemented for this thesis — sharing the same cloud/app backbone.

<div align="center">
<img src="../assets/diagrams/data-flow.jpg" alt="Sensors → Firebase → Flutter data flow" width="80%" /><br/>
<sub>Sensors (ESP8266) → Firebase Realtime DB → Flutter app, synced via <code>StreamBuilder</code> in 250–400 ms.</sub>
</div>

<div align="center">
<img src="../assets/diagrams/system-architecture-sequence.jpg" alt="Command sequence: app to pump" width="90%" />
<br/><sub>End-to-end command path: tapping "Water" in the app flips a Firebase flag, the ESP8266 listener
catches the change (<code>onDataChange</code>), pulses the pump, then resets the flag.</sub>
</div>

## Hardware

<div align="center">
<img src="../assets/hardware/device-photo.jpg" alt="Working prototype in a succulent pot" width="45%" />
</div>

| Component | Role |
|---|---|
| **ESP8266 NodeMCU** | Main controller, Wi-Fi |
| **DS18B20** | Waterproof digital temperature sensor (±0.5 °C) |
| **Analog soil-moisture probe** | Corrosion-resistant, buried probe |
| **L9110** | Dual-channel DC motor driver |
| **Mini submersible pump** | 120 L/H |
| **RGB LED** | Ambient status light, remotely controllable |

Full bill of materials and cost breakdown is in the thesis appendix
(≈ 455 TL / prototype).

## The Biophysical Lab (VPD)

The most distinctive part of the system: instead of just showing "40%
humidity," it computes **Vapor Pressure Deficit**, the metric growers
actually use to judge transpiration stress:

```
SVP  = 0.6108 × exp( 17.27 × T / (T + 237.3) )
VPD  = SVP × (1 − RH / 100)
```

Where `T` is temperature (°C) and `RH` is relative humidity (%). A high
VPD means the air is "pulling" moisture out of the plant faster than
its roots can replace it — the app surfaces this as a plain-language
stress warning rather than a raw kPa figure.

<div align="center">
<img src="../assets/diagrams/biophysical-lab-module.jpg" alt="Biophysical lab module" width="85%" />
</div>

## App Screenshots

<div align="center">
<img src="../assets/screenshots/prototype-dashboard.jpg" alt="Dashboard prototype" width="30%" />
<img src="../assets/screenshots/dashboard-light-dark.jpg" alt="Light / dark dashboard" width="30%" />
<img src="../assets/screenshots/device-pairing.jpg" alt="Secure device pairing flow" width="30%" />
</div>
<div align="center">
<img src="../assets/screenshots/biophysical-analysis.jpg" alt="Biophysical analysis screen" width="30%" />
<img src="../assets/screenshots/ai-analysis.jpg" alt="AI-assisted analysis" width="30%" />
</div>

## Tech Stack

| Layer | Technology |
|---|---|
| Microcontroller | ESP8266 (NodeMCU), Arduino framework |
| Sensors | DS18B20, analog capacitive/resistive soil probe |
| Cloud | Google Firebase (Realtime Database, Cloud Messaging) |
| Mobile / Web | Flutter, Dart (single codebase → Android / iOS / Web) |
| Charts | `fl_chart` |
| AI | Rule-based interpreter + `google_generative_ai` (Gemini) |
| Device pairing | `mobile_scanner` (QR) + numeric verification code |
| Project management | Agile / Scrum — 3 sprints, RACI matrix, Gantt chart |

## Repository Structure

```
.
├── README.md                  # You are here (language picker)
├── docs/
│   ├── README.en.md           # This document
│   ├── README.tr.md           # Turkish documentation
│   └── thesis/                # Full thesis PDF + defense slides
├── firmware/
│   ├── README.md               # Firmware architecture notes
│   └── examples/                # Redacted sample sketch + config template
├── mobile/
│   ├── README.md               # App architecture notes
│   └── lib_structure/           # Redacted sample models
└── assets/
    ├── images/                  # Banner / cover art
    ├── diagrams/                 # Architecture & sequence diagrams
    ├── screenshots/               # App UI screenshots
    └── hardware/                   # Physical prototype photos
```

## Getting Started

> ⚠️ **This is a portfolio / documentation repository, not a
> ready-to-clone-and-run app.** The firmware and Flutter sources
> published here are intentionally **redacted samples** — they show
> real architecture and file structure, but tuned thresholds,
> calibration constants, the full AI prompt pipeline, and Firebase
> credentials have been stripped or stubbed out so the finished system
> can't be lifted directly from GitHub and redeployed. This protects
> original thesis work from being copied while still letting reviewers,
> recruiters, and my advisor/jury inspect how it's built.
>
> **Want the full source for academic review?** Reach out — see
> [Author & Acknowledgments](#author--acknowledgments).

If you just want to see the architecture:

1. Read [`firmware/README.md`](../firmware/README.md) for the
   ESP8266 side (pin map, data cycle, Firebase JSON shape).
2. Read [`mobile/README.md`](../mobile/README.md) for the Flutter app
   (module layout, key packages, feature list).
3. Browse [`docs/thesis`](thesis) for the full write-up, including all
   formulas, sprint reports, and experimental results.

## Results

Measured during real-world testing (see thesis §7.1 for full detail):

- **Command latency**: 250–400 ms from tapping "Water" in the app to
  the pump activating, via Firebase's WebSocket-based sync.
- **Auto-reconnect**: the ESP8266 detects Wi-Fi drops and reconnects
  automatically with no data-flow interruption beyond the outage itself.
- **Anti-oscillation**: an 8-point hysteresis margin plus a
  `millis()`-based cooldown eliminated pump on/off flapping observed
  in early testing.
- **Cross-platform parity**: the same Flutter codebase produced
  visually consistent Android APK and Web builds.

## Roadmap

- 📷 ESP32-CAM + on-device/edge deep learning for leaf-disease
  detection (rust, mildew, etc.).
- ☀️ Solar power for energy-independent field deployments.
- 📡 LoRaWAN support for outdoor/agricultural use beyond Wi-Fi range.

## Author & Acknowledgments

**Besat Arif ÇINGAR** — Computer Engineering, Tekirdağ Namık Kemal
University ().

This was a solo undergraduate thesis project — design, hardware,
firmware, cloud schema, mobile/web app, biophysical modeling, and
writing were all done individually. Sincere thanks to my advisor,
**Dr. Öğr. Üyesi Halil Nusret BULUŞ**, for the guidance throughout.

Interested in the full source, a demo, or have questions about the
implementation? Open an issue on this repository or reach out directly.

## License

The documentation, diagrams, and redacted samples in this repository
are released under the [MIT License](../LICENSE). The complete,
production firmware and mobile application source are **not** included
in this public repository (see [Getting Started](#getting-started)).
