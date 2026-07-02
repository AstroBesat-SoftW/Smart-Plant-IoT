/*
 * ============================================================================
 *  AKILLI ZİRAAT — ESP8266 Firmware (Public Example / Sample)
 * ============================================================================
 *  Author : Besat Arif ÇINGAR
 *  Thesis : Akıllı Ziraat: IoT Tabanlı Akıllı Bitki Yönetim ve Analiz Sistemi
 *  Advisor: Dr. Öğr. Üyesi Halil Nusret BULUŞ
 *  Dept.  : Tekirdağ Namık Kemal Üniversitesi — Bilgisayar Mühendisliği
 *
 *  NOTE — THIS IS A REDACTED SAMPLE, NOT THE FULL SOURCE.
 *  ----------------------------------------------------------------------
 *  This file exists to document the firmware architecture for the
 *  repository visitor / grader. The complete implementation (autonomous
 *  watering thresholds, VPD/dew-point math, cooldown tuning, calibration
 *  constants and the full Firebase read/write cycle) has been trimmed or
 *  replaced with stubs so the working sketch cannot be copy-pasted and
 *  redeployed as-is. Full source is available on request for academic
 *  review (advisor / jury) — see README for contact details.
 * ============================================================================
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>          // Wi-Fi connectivity
#include <FirebaseESP8266.h>      // Firebase Realtime Database client
#include <OneWire.h>              // 1-Wire bus (DS18B20)
#include <DallasTemperature.h>    // Digital temperature sensor
#include <NTPClient.h>            // Network time (for history timestamps)
#include <WiFiUdp.h>

#include "config.example.h"       // <-- copy to config.h and fill in secrets

// --- PIN MAP ---------------------------------------------------------------
#define RELAY_PIN       D0        // Water pump relay
#define ONE_WIRE_BUS    D2        // DS18B20 data line
#define MOISTURE_PIN    A0        // Analog soil-moisture probe

int PIN_LED_RED   = D5;
int PIN_LED_GREEN = D4;
int PIN_LED_BLUE  = D6;

// --- GLOBALS -----------------------------------------------------------
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

FirebaseData   fbdo;
FirebaseAuth   auth;
FirebaseConfig config;

WiFiUDP  ntpUDP;
NTPClient timeClient(ntpUDP);

unsigned long wateringCooldown = 0;   // millis()-based safety timer

// ============================================================================
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);      // relay is active-LOW → start OFF

  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  sensors.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println(" connected.");

  timeClient.begin();

  config.api_key      = API_KEY;
  config.database_url = DATABASE_URL;
  auth.user.email      = USER_EMAIL;
  auth.user.password   = USER_PASSWORD;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

// ============================================================================
void loop() {
  readAndPublishSensorData();   // -> see firmware/README.md for cycle details
  handleManualCommands();       // "Sula" button / light color from the app
  runAutonomousWateringLogic(); // proprietary — omitted in this sample
  delay(5000);                  // ~5s telemetry cycle
}

// ----------------------------------------------------------------------------
// Reads soil moisture + temperature and pushes them to Firebase, throttled
// to avoid flooding the Realtime Database write quota.
// Full implementation, including the history-log node writer with NTP
// timestamps (see thesis §6.5), is omitted from this public sample.
// ----------------------------------------------------------------------------
void readAndPublishSensorData() {
  // float temperature = sensors.getTempCByIndex(0);
  // int   moisturePct = readCalibratedMoisture();
  // Firebase.setFloat(fbdo, String(DEVICE_ID) + "/sicaklik", temperature);
  // Firebase.setInt(fbdo, String(DEVICE_ID) + "/nem", moisturePct);
  // ... history logging omitted ...
}

// ----------------------------------------------------------------------------
// Listens for "motor_durum" / "isik_bilgisi" flags written by the Flutter
// app and drives the relay / RGB LED accordingly. See thesis §6.6 for the
// full listener implementation.
// ----------------------------------------------------------------------------
void handleManualCommands() {
  // if (Firebase.getInt(fbdo, String(DEVICE_ID) + "/motor_durum")) { ... }
}

// ----------------------------------------------------------------------------
// Autonomous irrigation decision engine.
// Combines the user-configured target moisture ("ideal/nem") with a
// hysteresis margin and a millis()-based cooldown timer to prevent pump
// oscillation and root-rot from overwatering (thesis §7.1.2, §6.7).
// The tuned constants and full decision logic are intentionally withheld.
// ----------------------------------------------------------------------------
void runAutonomousWateringLogic() {
  // if (moisture <= (targetMoisture - SAFETY_MARGIN) && wateringCooldown == 0) {
  //     triggerPump(configuredDurationMs);
  //     wateringCooldown = WATERING_COOLDOWN_LIMIT;
  // }
}
