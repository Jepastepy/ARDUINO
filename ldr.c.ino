#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);

int ledpin=6;
int threshold=500;



void setup() {
 pinMode(A0,INPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int ldrvalue =  analogRead(A0);
  Serial.println(ldrvalue);
  if(ldrvalue<threshold)
  {
    digitalWrite(ledpin,HIGH);

  }else
  {
    digitalWrite(ledpin,LOW);

  }
delay(200);

}


