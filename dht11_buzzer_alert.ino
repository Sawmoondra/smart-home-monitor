#include <DHT.h>

#define DHTPIN    2
#define DHTTYPE   DHT11
#define BUZZERPIN 8
#define TEMP_THRESHOLD 28.0  // buzzer triggers above this temperature

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(BUZZERPIN, OUTPUT);
    digitalWrite(BUZZERPIN, LOW);
    Serial.println("DHT11 Smart Home Monitor Starting...");
}

void loop() {
    delay(2000);

    float humidity = dht.readHumidity();
    float tempC    = dht.readTemperature();
    float tempF    = dht.readTemperature(true);

    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
        Serial.println("Failed to read from DHT11 sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C  |  ");
    Serial.print(tempF);
    Serial.println("°F");

    Serial.print("Humidity:    ");
    Serial.print(humidity);
    Serial.println("%");

    // Buzzer alert
    if (tempC > TEMP_THRESHOLD) {
        Serial.println("⚠ ALERT: Temperature too high!");
        digitalWrite(BUZZERPIN, HIGH);
        delay(500);
        digitalWrite(BUZZERPIN, LOW);
    } else {
        Serial.println("Status: Normal");
    }

    Serial.println("------------------------");
}