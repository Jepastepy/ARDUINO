

#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
float temp;
void setup() {
  
lcd.begin(16,2);
pinMode(A1,INPUT);
}

void loop() {
  int value=analogRead(A1);

 temp=  (value*500)/1023;
lcd.setCursor(0,0);
lcd.print("temperature=");
lcd.print(temp);
delay(1000);


}
