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

const char* ssid     = "";
const char* password = "";
const char* endpoint = "https://api.felomousa.com/finance";


void initDisplay() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
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
  char line1[16], line2[16];
  snprintf(line1, sizeof(line1), "$%.2f", price);
  if (change >= 0) // if price change >0, show with "+", otherwise use "-"
    snprintf(line2, sizeof(line2), "+$%.2f", change);
  else
    snprintf(line2, sizeof(line2), "-$%.2f", -change);
  // Serial.println(line1); // print current price 
  // Serial.println(line2); // print price change
  display.setTextSize(2);
  display.setCursor(22, 3);
  display.print(line1);

  display.setTextSize(1);
  display.setCursor(46, 21);
  display.print(line2);

  display.display();
}

void getData() {
  if(WiFi.status() != WL_CONNECTED) return;

  HTTPClient http; http.begin(endpoint);
  int code = http.GET();

  if(code == HTTP_CODE_OK) {
    String payload = http.getString();
    StaticJsonDocument<256> doc;
    if(!deserializeJson(doc, payload))
      updateDisplay(doc["current_price"].as<float>(), doc["daily_change"].as<float>());
    else Serial.println("json parse error");
  } else {
    Serial.print("http error: "); Serial.println(http.errorToString(code));
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