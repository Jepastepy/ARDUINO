#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <DHT.h>

// OLED Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 Setup
#define DHTPIN A2     // Data pin connected to A2 as per your diagram
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// RTC Setup
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);

  // Initialize DHT
  dht.begin();

  // Initialize OLED (Address 0x3C is common for SSD1306)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    for(;;);
  }

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("RTC failed");
    for(;;);
  }

  // Use this line once to set the time, then comment it out and re-upload
  // rtc.adjust(DateTime(F(_DATE), F(TIME_)));

  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  DateTime now = rtc.now();
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  display.clearDisplay();

  // --- Display Time ---
  display.setCursor(0, 0);
  display.setTextSize(2);
  if(now.hour() < 10) display.print('0');
  display.print(now.hour());
  display.print(':');
  if(now.minute() < 10) display.print('0');
  display.print(now.minute());

  // --- Display Temp & Humidity ---
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Temp: ");
  display.print(t, 1);
  display.print(" C");

  display.setCursor(0, 45);
  display.print("Humidity: ");
  display.print(h, 0);
  display.print("%");

  display.display();
  delay(2000); // DHT11 needs at least 2 seconds between readings
}