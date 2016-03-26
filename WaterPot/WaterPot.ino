
int red=4;
int green = 2
int blue = 3;
int moisture = 0;
int detectPowerPin = 5;
int pumpPin = 6;
int analogPin = 0;
int low= 1
int med= 2
int high = 3


int interval = 1000;


void setup() {
  // put your setup code here, to run once:
  pinMode(detectPowerPin, OUTPUT);
  pinMode(red,     OUTPUT);
  pinMode(green,   OUTPUT);
  pinMode(blue,    OUTPUT);
  pinMode(pumpPin, OUTPUT);  
 
  Serial.begin(9600);
}rPot.ino

void blink(int ont) {
 
  digitalWrite(2, 1);//green
  digitalWrite(3, 1);//blue
  digitalWrite(4, 0);//red
  
  delay(ont);  
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(detectPowerPin, 1);
  delay(100); 
  int invMoisture = analogRead(analogPin);
  int seclev = analogRead(1);
  Serial.println(seclev); 
  
  digitalWrite(detectPowerPin, 0);
  moisture = 1023 - invMoisture;
  
  //423 = air
  //650 = finger grip
  //900 = 1 cm water
  //950 = full submersion 
  if (moisture < 600) { 
    blink(50);
    delay(100);
    blink(50);
  }
  
  if (moisture < 500) { 
    digitalWrite(pumpPin, 1);
   // analogWrite(pumpPin, 1);
   // interval = 1000;
  }
  else {
    digitalWrite(pumpPin, 0);
   // interval = 5000;
  }
  
  delay(interval);
}

int waterlevel(){
  int thesh = 750;
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A32, 1);

  if (analogRead(low) < thresh ){
    return 0;   
  }else if (analogRead(med) < thresh ){
    return 1;  
  }else if (analogRead(high) < thresh ){
    return 2;  
  }else if (analogRead(high) > thresh ){
    return 3;  
  }

  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);  
}

