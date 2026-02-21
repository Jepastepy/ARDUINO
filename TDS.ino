#include <LiquidCrystal.h>

// LCD Pin Mapping based on your diagram:
// RS=D7, E=D8, D4=D9, D5=D10, D6=D11, D7=D12
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int TdsSensorPin = A0;  // TDS sensor output connected to A0
const float VREF = 5.0;       // Operating voltage of the Arduino
const int ADC_RES = 1024;     // ADC Resolution (10-bit)

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("TDS Meter Init");
  delay(2000);
  lcd.clear();
}

void loop() {
  // 1. Read the raw analog value
  int rawValue = analogRead(TdsSensorPin);

  // 2. Convert raw value to voltage
  float voltage = rawValue * VREF / ADC_RES;

  // 3. Simple TDS Calculation 
  // Note: For high accuracy, a temperature compensation factor is usually applied.
  // This is a standard linear approximation for many hobbyist TDS sensors:
  float tdsValue = (133.42 * pow(voltage, 3) - 255.86 * pow(voltage, 2) + 857.39 * voltage) * 0.5;

  // 4. Display the results on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print("V");

  lcd.setCursor(0, 1);
  lcd.print("TDS: ");
  lcd.print((int)tdsValue);
  lcd.print(" ppm    "); // Extra spaces to clear previous digits

  delay(1000); // Update every second
}