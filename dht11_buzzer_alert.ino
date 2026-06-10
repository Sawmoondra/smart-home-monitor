// ============================================================
// Smart Home Monitor - DHT11 Temperature & Humidity Sensor
// Board: Arduino Uno R3 (Elegoo)
// Author: Samundra Aryal
// Date: June 2026
// ============================================================
// Description:
// Reads temperature and humidity from DHT11 sensor every 2 seconds.
// Triggers a buzzer alert when temperature exceeds defined threshold.
// Logs all readings to Serial Monitor via UART communication.
// ============================================================

#include <DHT.h>

// Pin definitions
#define DHTPIN    2       // DHT11 data pin connected to digital pin 2
#define BUZZERPIN 8       // Active buzzer connected to digital pin 8

// Sensor type
#define DHTTYPE DHT11

// Alert threshold - buzzer triggers above this temperature (Celsius)
#define TEMP_THRESHOLD 28.0

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);           // Start serial communication at 9600 baud
    dht.begin();                  // Initialize DHT11 sensor
    pinMode(BUZZERPIN, OUTPUT);   // Set buzzer pin as output
    digitalWrite(BUZZERPIN, LOW); // Make sure buzzer is off at start
    Serial.println("Smart Home Monitor Starting...");
    Serial.println("-----------------------------");
}

void loop() {
    delay(2000); // DHT11 needs 2 seconds between readings

    // Read sensor data
    float humidity = dht.readHumidity();
    float tempC    = dht.readTemperature();      // Celsius
    float tempF    = dht.readTemperature(true);  // Fahrenheit

    // Check if readings are valid
    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
        Serial.println("ERROR: Failed to read from DHT11 sensor!");
        return;
    }

    // Print temperature readings
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("C  |  ");
    Serial.print(tempF);
    Serial.println("F");

    // Print humidity reading
    Serial.print("Humidity:    ");
    Serial.print(humidity);
    Serial.println("%");

    // Check temperature threshold and trigger buzzer if too high
    if (tempC > TEMP_THRESHOLD) {
        Serial.println("ALERT: Temperature too high!");
        digitalWrite(BUZZERPIN, HIGH);  // Turn buzzer on
        delay(500);                     // Beep for 500ms
        digitalWrite(BUZZERPIN, LOW);   // Turn buzzer off
    } else {
        Serial.println("Status: Normal");
    }

    Serial.println("-----------------------------");
}