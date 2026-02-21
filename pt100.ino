#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int ptPin = A0;
const float Vref = 5.0;
const float R_fixed = 100.0;
const float alpha = 0.385;   // ohm per degree

void setup() {
  lcd.begin(16,2);
  lcd.print("PT100 Temp");
  delay(2000);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(ptPin);

  // Step 1: Convert ADC to voltage
  float voltage = (adcValue * Vref) / 1023.0;

  // Step 2: Calculate PT100 resistance
  float R_pt100 = (voltage * R_fixed) / (Vref - voltage);

  // Step 3: Convert resistance to temperature
  float temperature = (R_pt100 - 100.0) / alpha;

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  delay(1000);
}