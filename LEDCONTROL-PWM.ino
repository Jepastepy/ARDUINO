
int i=0;
void setup() {
  
  // put your setup code here, to run once:
pinMode(0,INPUT);
pinMode(1,INPUT);
pinMode(3,OUTPUT);
}

void loop() {
  analogWrite(3,i);
  if(digitalRead(0)==LOW)
  {
   if( i<255)
   {
    i+=26;
    
   }
delay(500);
  }
  if(digitalRead(1)==LOW)
  {
    if(i>0)
    {
      i-=26;
    }
    delay(500);
  }
}
  // put your main code here, to run repeatedly:
