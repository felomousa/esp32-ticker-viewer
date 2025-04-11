#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET   -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid     = "felo";
const char* password = "something_secure_idk";
const char* endpoint = "https://api.felomousa.com/finance";


void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void connectWiFi() {
  Serial.print("connecting to wifi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nwifi connected!");
}


void updateDisplay(float price, float change) {
  display.clearDisplay();
  char line1[16], line2[16];
  snprintf(line1, sizeof(line1), "$%.2f", price);
  if (change >= 0) // if price change >0, show with "+", otherwise use "-"
    snprintf(line2, sizeof(line2), "+$%.2f", change);
  else
    snprintf(line2, sizeof(line2), "-$%.2f", -change);
  
  display.setTextSize(2);
  display.setCursor(22, 3);
  display.print(line1);

  display.setTextSize(1);
  display.setCursor(46, 21);
  display.print(line2);
  //Serial.print("displayed");

  display.display();
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
      //Serial.print(change);
      //Serial.print(price);
      updateDisplay(price, change);
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
  Wire.begin();
  initDisplay();
  connectWiFi();
}

void loop() {
  getData();
  delay(5000);
}

