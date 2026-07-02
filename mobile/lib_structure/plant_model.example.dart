/// plant_model.example.dart
/// ---------------------------------------------------------------------
/// Akıllı Ziraat — domain model sample (REDACTED).
///
/// This mirrors the Firebase Realtime Database JSON tree documented in
/// `/firmware/README.md`, showing how the app deserializes a device
/// node. Business logic (health-percentage scoring, VPD calculation,
/// AI prompt assembly) lives elsewhere in the private codebase and is
/// intentionally not included here.
/// ---------------------------------------------------------------------
library plant_model_example;

class Plant {
  final String deviceId;
  final String name;
  final double temperature;
  final int moisture;
  final bool pumpActive;
  final int lightMode;
  final IdealConditions ideal;

  Plant({
    required this.deviceId,
    required this.name,
    required this.temperature,
    required this.moisture,
    required this.pumpActive,
    required this.lightMode,
    required this.ideal,
  });

  factory Plant.fromSnapshot(String deviceId, Map<dynamic, dynamic> json) {
    return Plant(
      deviceId: deviceId,
      name: json['isim'] ?? 'Bitki',
      temperature: (json['sicaklik'] ?? 0).toDouble(),
      moisture: (json['nem'] ?? 0) as int,
      pumpActive: (json['motor_durum'] ?? 0) == 1,
      lightMode: (json['isik_bilgisi'] ?? 0) as int,
      ideal: IdealConditions.fromSnapshot(json['ideal'] ?? {}),
    );
  }

  // healthScore(), vpd(), and the Gemini-based recommendation builder
  // are part of the private implementation — see README for access.
}

class IdealConditions {
  final int minMoisture;
  final int maxMoisture;
  final double idealTemperature;

  IdealConditions({
    required this.minMoisture,
    required this.maxMoisture,
    required this.idealTemperature,
  });

  factory IdealConditions.fromSnapshot(Map<dynamic, dynamic> json) {
    return IdealConditions(
      minMoisture: (json['min_nem'] ?? 40) as int,
      maxMoisture: (json['max_nem'] ?? 60) as int,
      idealTemperature: (json['sicaklik'] ?? 22).toDouble(),
    );
  }
}
