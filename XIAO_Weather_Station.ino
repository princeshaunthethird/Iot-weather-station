/***************************************************
   Seeed XIAO ESP32-C6 Weather Station
   Features:
   - DHT11 Sensor (Temperature + Humidity)
   - SSD1306 OLED Display
   - Battery Voltage
   - Blynk Cloud Dashboard
***************************************************/

// ---- BLYNK TEMPLATE INFO ----  add all the details of the blynk app here.
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""  

// ---- Include Libraries ----
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ---- WiFi Credentials ----
char ssid[] = "";   // add your wifi name 
char pass[] = "";   // add your wifi password

// ---- DHT11 Sensor ----
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ---- OLED Display ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---- Battery Voltage Input ----
#define BATTERY_PIN A0  // ADC pin connected to voltage divider (2x 100kΩ resistors)

// ---- Timing ----
unsigned long lastUpdate = 0;
const long updateInterval = 2000; // 2 seconds

// ---- Read Battery Voltage ----
float readBatteryVoltage() {
  int raw = analogRead(BATTERY_PIN);
  float voltage = (raw / 4095.0) * 3.3 * 2.0; // Scale for voltage divider
  return voltage;
}

// ---- Setup ----
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Correct I2C pins for Seeed XIAO ESP32-C6
  Wire.begin(22, 23);  // SDA=D4 (GPIO22), SCL=D5 (GPIO23)
  dht.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("⚠️ OLED not found. Check wiring or address (try 0x3D).");
    while (true);
  }

  display.dim(false);  // Full brightness
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("OLED Test OK!");
  display.setCursor(10, 30);
  display.println("Booting...");
  display.display();
  delay(2000);

  // WiFi Connection Display
  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("Connecting WiFi...");
  display.display();

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  display.clearDisplay();
  display.setCursor(0, 20);
  display.println("WiFi Connected!");
  display.display();
  delay(1000);
}

// ---- Main Loop ----
void loop() {
  Blynk.run();

  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    readAndDisplay();
  }
}

// ---- Read Sensor Data and Update Display ----
void readAndDisplay() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  float vbat = readBatteryVoltage();

  // Fallback values if DHT fails
  if (isnan(temp)) temp = 25.0;
  if (isnan(hum)) hum = 50.0;

  // ---- Send Data to Blynk ----
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
  Blynk.virtualWrite(V2, vbat);

  // ---- Serial Output ----
  Serial.printf("Temp: %.1f C | Hum: %.1f %% | Batt: %.2f V\n",
                temp, hum, vbat);

  // ---- OLED Output ----
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("XIAO Weather Station");

  display.setCursor(0, 15);
  display.printf("Temp: %.1f C", temp);

  display.setCursor(0, 30);
  display.printf("Hum : %.1f %%", hum);

  display.setCursor(0, 45);
  display.printf("Batt: %.2f V", vbat);

  display.display();
}
