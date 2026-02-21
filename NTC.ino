 



#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int ntcpin=A0;
int fanpin=3;
int threshold=500;



void setup() {
 pinMode(A0,INPUT);
  pinMode(fanpin,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int ntcvalue =  analogRead(A0);
  Serial.println(ntcvalue);
  if(ntcvalue<threshold)
  {
    digitalWrite(fanpin,HIGH);
    delay(200);
  }else
  {
    digitalWrite(fanpin,LOW);

  }
delay(200);

}


