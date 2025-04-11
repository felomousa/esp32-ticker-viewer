# ESP32 Finance OLED Display

Connects to WiFi, fetches JSON from an HTTPS API every 5 seconds, and displays current price and daily change on a 128x32 SSD1306 OLED.

## Details
- HTTPS requests using `HTTPClient` (`WiFiClientSecure` backend)  
- Parses JSON with ArduinoJson  
- Updates OLED with Adafruit SSD1306/GFX  
- Clears display before redraw to prevent artifacts  
- PlatformIO project using ESP32 (Arduino framework)

## Debugging
- Serial output for WiFi and HTTP status  
- JSON parsing check with `deserializeJson()`  
- Only updates display if data is valid

## Skills Used
- C++  
- JSON handling  
- I²C peripheral control  
- Basic network requests and error handling

## API Response Format
```json
{
  "current_price": 131.96,
  "daily_change": 1.09,
  "ticker": "VFV.TO"
}
```

## PlatformIO Setup
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_port = COM4  ; adjust as needed

lib_deps =
  bblanchon/ArduinoJson@^6.18.0
  adafruit/Adafruit BusIO@^1.17.0
  adafruit/Adafruit GFX Library@^1.11.11
  adafruit/Adafruit SSD1306@^2.5.13
```

## Hardware Used
- ESP32 WROOM dev board (esp32dev)  
- SSD1306 OLED display, 128x32, I²C (address: 0x3C)  

## Minimum Requirements
- ArduinoJson >= 6.18.0
- Adafruit BusIO >= 1.17.0
- Adafruit GFX Library >= 1.11.11
- Adafruit SSD1306 >= 2.5.13

## Troubleshooting
- **Nothing on screen:**  
  - Check I²C wiring and display address (0x3C)  
  - Ensure `display.begin()` and `display.setTextColor()` are called  
- **No data shown:**  
  - Confirm WiFi credentials and API availability  
  - Verify JSON keys match expected format  
- **COM port issues:**  
  - Set `upload_port` to correct port in `platformio.ini`  
