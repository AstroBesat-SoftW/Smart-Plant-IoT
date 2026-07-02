# Mobile & Web App — Flutter

Cross-platform client (Android / iOS / Web) built with Flutter + Dart,
backed by Firebase Realtime Database.

> **Why only a structure sample is published**
> The full Flutter project (screens, animations, Gemini AI prompt
> engineering, cloud messaging setup) is kept private. This folder
> shows the module layout and a couple of representative, redacted
> snippets so reviewers can see the architecture without being able to
> rebuild the shippable app from the repo. Full source is available on
> request for academic review.

## Project layout

```
lib/
├── main.dart              # App entry point, theme + routing
├── beyaz/                 # Light theme
├── genel_bakis.dart        # Dashboard (overview) screen
├── nem_sayfasi.dart         # Soil-moisture detail screen
├── sicaklik_sayfasi.dart    # Temperature detail screen
├── analiz.dart              # Biophysical lab / VPD / AI analysis screen
└── profilim.dart            # Profile & device-pairing screen
```

## Key packages (`pubspec.yaml`)

| Package | Purpose |
|---|---|
| `firebase_core`, `firebase_database` | Realtime Database sync |
| `google_generative_ai` | Gemini-powered plant-health interpretation |
| `mobile_scanner` | QR-code device pairing |
| `fl_chart` | Temperature / moisture history charts |
| `provider` | State management |

## Feature highlights

- **Two-step device pairing** — a numeric Device ID plus a verification
  code printed on the pot's label (2FA-style), so a stranger can't add
  themselves to your Firebase node just by guessing an ID.
- **Real-time dashboard** — carousel cards for moisture / temperature,
  a health-percentage bar, quick actions (Water / Light).
- **Biophysical Lab** — VPD and dew-point calculations rendered as
  charts, with a rule-based AI interpreter surfacing plain-language
  warnings ("your plant is losing water quickly").
- **Light / Dark themes**, single codebase compiled to Android APK and
  a static Web build (`flutter build web`).

## Redacted sample

See [`lib_structure/plant_model.example.dart`](lib_structure/plant_model.example.dart)
for the shape of the domain model that mirrors the Firebase JSON tree
documented in [`/firmware/README.md`](../firmware/README.md).
