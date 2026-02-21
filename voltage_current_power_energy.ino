#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// Constants
const int voltagePin = A0;    // Pin to measure voltage across the load resistor
const int currentPin = A1;    // Pin to measure voltage across the current sensor (10Ω)
const float voltageRef = 5.0; // Reference voltage (5V)
const int loadResistor = 1000; // Load resistor (1000 ohms)
const int currentResistor = 10; // Current sensor resistor (10 ohms)
// Variables
float voltage = 0.0;
float current = 0.0;
float power = 0.0;
float energy = 0.0;
unsigned long previousMillis = 0;
unsigned long displayMillis = 0;
const long displayInterval = 3000;
bool displayToggle = false;
const long interval = 1000;  // Interval to update readings (1 second)

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Serial.print("Starting....");
  Serial.println("\n");
  delay(2000); // Wait for serial monitor to initialize
  lcd.begin(16, 2); 
  lcd.print("Starting....");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if one second has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time we updated
    previousMillis = currentMillis;

    // Read voltage across load resistor (Voltage Divider)
    int voltageReading = analogRead(voltagePin);
    voltage = (voltageReading / 1023.0) * voltageRef;

    // Read voltage across current sensor (10 ohm resistor)
    int currentReading = analogRead(currentPin);
    float voltageAcrossSensor = (currentReading / 1023.0) * voltageRef;
    current = voltageAcrossSensor / currentResistor;
    current = current*1000;

    // Calculate power: P = V_load * I
    power = voltage * current;

    // Calculate energy: Energy += Power * Time (1 second)
    energy += power * (interval / 3600000.0);  // Time is in seconds

  }

    // Print the readings to the Serial Monitor
    Serial.print("Voltage: ");
    Serial.print(voltage, 2);
    Serial.print(" V, ");
    Serial.print("Current: ");
    Serial.print(current, 3);
    Serial.print(" mA, ");
    Serial.print("Power: ");
    Serial.print(power, 3);
    Serial.print(" mW, ");
    Serial.print("Energy: ");
    Serial.print(energy, 4);
    Serial.println(" mWh");
    delay(1000);
  
   if (currentMillis - displayMillis >= displayInterval) {
    displayMillis = currentMillis;
    displayToggle = !displayToggle;

    lcd.clear();
    if (displayToggle) {
      lcd.setCursor(0, 0);
      lcd.print("Voltage:");
      lcd.print(voltage, 2);
      lcd.print("V");
      lcd.setCursor(0, 1);
      lcd.print("Current:");
      lcd.print(current, 3);
      lcd.print("mA");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Power:");
      lcd.print(power, 3);
      lcd.print("mW");
      lcd.setCursor(0, 1);
      lcd.print("Energy:");
      lcd.print(energy, 4);
      lcd.print("mWh");
    }
}
}