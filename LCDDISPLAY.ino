
#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
   lcd.setCursor(4,0);
  lcd.print("Jepa");

  // put your setup code here, to run once:


}

void loop() {
  lcd.setCursor(4,0);
  lcd.print("Jepa");
  
  lcd.setCursor(2,1);
  lcd.scrollDisplayLeft();
  
  lcd.print(" Welcome");
  delay(500);
 
  // put your main code here, to run repeatedly:
}
