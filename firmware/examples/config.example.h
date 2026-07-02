/*
 * config.example.h
 * ------------------------------------------------------------------
 * Akıllı Ziraat — ESP8266 configuration template.
 *
 * This is an EXAMPLE file. Copy it to `config.h` and fill in your own
 * credentials before compiling. `config.h` is git-ignored so real
 * Wi-Fi / Firebase secrets never get committed to the repository.
 * ------------------------------------------------------------------
 */

#ifndef CONFIG_H
#define CONFIG_H

// --- WI-FI ---
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"

// --- FIREBASE ---
#define API_KEY         "YOUR_FIREBASE_API_KEY"
#define DATABASE_URL    "your-project-default-rtdb.firebaseio.com"
#define USER_EMAIL      "your-service-account@example.com"
#define USER_PASSWORD   "YOUR_FIREBASE_USER_PASSWORD"

// --- DEVICE ---
#define DEVICE_ID       "000000"   // Printed on the pot's pairing label

#endif
