#include<LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int num_measure=128;//set num of measurement
int pinSignal=A4;//pin connected to pin 4 module sound sensor
long Sound_signal;//store the value read sound signal
long sum=0;//store the total value
long level=0;
int value=0;



void setup() {
  pinMode(pinSignal,INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
  }



void loop() {
  sum=0;
  for(int i=0;i<num_measure;i++)
  {
    Sound_signal=analogRead(pinSignal);
    sum+=abs(Sound_signal-512);
    }
    level=sum/num_measure;
    value=level;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("sound level");
    lcd.setCursor(0,1);
    lcd.print("sound level :db");
    Serial.print(value);
    delay(500);


}
