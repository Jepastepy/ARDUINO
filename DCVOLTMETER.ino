#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int analogInput=A0;
float Vin =0.0;
int value=0;
void setup() {
  pinMode(A0,INPUT);
 lcd.begin(16,2);
 lcd.print("DC VOLTMETER");
Serial.begin(9600);}
void loop() {
  value=analogRead(A0);
  Vin=(value*5.0)/1023.0;
  lcd.setCursor(0,1);
  lcd.print(Vin);
  Serial.println("Vin");
  Serial.println("DC VOLTMETER");
  delay(1000);


}
