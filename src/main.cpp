#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define RESET_PIN    -1 // not in use

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RESET_PIN);

int counter = 1;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC);

  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 2); // vertically centered

  display.display();
  delay(1000);

  Serial.println("setup donzo");
}

void loop() {
  display.setTextColor(SSD1306_INVERSE);

  display.clearDisplay();
  display.setCursor(0, 2); // vertically centered

  display.print(counter);
  display.display();
  //Serial.println(counter);
  delay(100);
  counter++;
  if (counter > 100) counter = 1;
}
