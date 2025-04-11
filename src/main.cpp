#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET   -1

const char* ssid     = "";
const char* password = "";
const char* endpoint = "https://api.felomousa.com/finance";

void connectWiFi() {
  Serial.print("connecting to wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nwifi connected!");
}

void getData() {
  if (WiFi.status() != WL_CONNECTED)
    return;
    
  HTTPClient http;
  http.begin(endpoint);
  int code = http.GET();
  if (code == HTTP_CODE_OK) {
    String payload = http.getString();
    StaticJsonDocument<256> doc;
    if (!deserializeJson(doc, payload)) {
      float price = doc["current_price"];
      float change = doc["daily_change"];
      char line1[16], line2[16];
      snprintf(line1, sizeof(line1), "$%.2f", price);
      
      if (change >= 0) // if price change >0, show with "+", otherwise use "-"
        snprintf(line2, sizeof(line2), "+$%.2f", change);
      else
        snprintf(line2, sizeof(line2), "-$%.2f", -change);
        
      Serial.println(line1);
      Serial.println(line2);
    } else {
      Serial.println("json parse error");
    }
  } else {
    Serial.print("http error: ");
    Serial.println(http.errorToString(code));
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  getData();
  delay(5000);
}
