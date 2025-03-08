#include "LiquidCrystal.h"
#include <ArduinoJson.h>

#define LCD_RS 12
#define LCD_E  11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 2

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();
  
  // Petit message de test
  lcd.setCursor(0, 0);
  lcd.print("Hello, UNO R3 1.0!");
  lcd.setCursor(0, 1);
  lcd.print("Mode 4 bits OK");

  while (!Serial) {}

  Serial.println("Arduino is ready to receive data...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ready to receive");
}

void loop() {
  if (Serial.available() > 0) {
    String incomingData = Serial.readStringUntil('\n');
    incomingData.trim();

    Serial.print("Received: ");
    Serial.println(incomingData);

    StaticJsonDocument<200> doc;

    DeserializationError error = deserializeJson(doc, incomingData);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }

    float temperature = doc["temp"]; 
    int humidity = doc["humidity"]; 
    const char* status = doc["status"];

    lcd.clear();  
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("°C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
  }
}