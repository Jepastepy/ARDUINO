




int r=3;
int g=5;
int y=6;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);


  // put your setup code here, to run once:

}

void loop() {
  
  analogWrite(3,255);
    analogWrite(5,0);    //red
  analogWrite(6,0);
  delay(500);
analogWrite(3,0);
    analogWrite(5,255);    //green
  analogWrite(6,0);
  delay(500);

analogWrite(3,0);
    analogWrite(5,0);    //blue
  analogWrite(6,255);
  delay(500);
analogWrite(3,148);   //violet
    analogWrite(5,0);
  analogWrite(6,211);
  delay(500);

analogWrite(3,75);
    analogWrite(5,0);   //purple
  analogWrite(6,130);
  delay(500);
analogWrite(3,255);
    analogWrite(5,255);   //yellow
  analogWrite(6,0);
  delay(500);
  analogWrite(3,255);
    analogWrite(5,127);   //orange
  analogWrite(6,0); 
  delay(500);

  
  
  // put your main code here, to run repeatedly:

}
