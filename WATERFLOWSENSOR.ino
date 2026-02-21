 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Flow sensor
volatile int flow_frequency;
unsigned int l_hour;
float total_liters = 0.0;
const unsigned char flowsensor = 2;
unsigned long currentTime;
unsigned long cloopTime;
unsigned long lastFlowTime = 0;

// LED and buzzer
const int flowLED = 4;
const int buzzer = 5;

// Interrupt handler for flow sensor
void flow() {
  flow_frequency++;
}

void setup() {
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH);
  attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING);

  pinMode(flowLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // halt
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40, 20);
  display.println("FLOW");
  display.setCursor(20, 45);
  display.println("MONITOR");
  display.display();
  delay(2000);
  display.clearDisplay();

  currentTime = millis();
  cloopTime = currentTime;
  lastFlowTime = currentTime;
}

void loop() {
  currentTime = millis();

  if (currentTime >= (cloopTime + 1000)) {
    cloopTime = currentTime;

    // Calculate flow rate in L/h
    l_hour = (flow_frequency * 60) / 7.5;
    float l_per_sec = l_hour / 3600.0;
    total_liters += l_per_sec;

    // Check for flow activity
    if (flow_frequency > 0) {
      lastFlowTime = currentTime;
    }
    flow_frequency = 0;

    Serial.print("Flow: ");
    Serial.print(l_hour);
    Serial.print(" L/h | Total: ");
    Serial.print(total_liters, 2);
    Serial.println(" L");

    // Determine if flow has stopped
    bool noFlow = (currentTime - lastFlowTime) > 10000;

    display.clearDisplay();

    if (noFlow) {
      digitalWrite(buzzer, HIGH);
      
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(20, 20);
      display.println("NO FLOW");
      display.setCursor(25, 45);
      display.println("ALERT!");
    } else {
      digitalWrite(buzzer, LOW);

      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("F:");
      display.print(l_hour);
      display.println("L/h");

      display.setCursor(0, 38);
      display.print("TL:");
      display.print(total_liters, 2);
      display.println("L");
    }

    // LED ON if flow is happening, else OFF
    digitalWrite(flowLED, (l_hour > 0) ? HIGH : LOW);

    display.display();
  }
}