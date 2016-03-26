
int red=4;
int green = 2;
int blue = 3;
int moisture = 0;
int detectPowerPin = 5;
int pumpPin = 6;
int analogPin = 0;
int low= 1;
int med= 2;
int high = 3;
int shortInterval = 500;
int longInterval = 5000;
int state = 0;
int c = 0;
int interval = 1000;
//states w3 w2 w1 w0 watering lowPower

void setup() {
  // put your setup code here, to run once:
  pinMode(detectPowerPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(pumpPin, OUTPUT);  
  Serial.begin(9600);
}

void statusLight(int r, int g, int b){
  digitalWrite(red,   1 - r);//green
  digitalWrite(green, 1 - g);//blue
  digitalWrite(blue,  1 - b);//red 
}

void blink(int times,int r,int g,int b) {
  for (int i = 0; i < times; i++) {
    statusLight(r,g,b); 
    delay(200);  
    statusLight(0,0,0);
    delay(200);  
  }  
}

void loop() {
  int wl = waterlevel();
  

  moisture = moistureLevel();
  
  if (moisture < 500) { 
     if (wl < 3) {
         //watering
         digitalWrite(pumpPin, 1);
         blink(1,0,1,0);
     } else {
         digitalWrite(pumpPin, 0);
         blink(6,1,0,1);
         blink(6,1,1,0);
        //alert cant water
     }
     interval = shortInterval;
  }  else {
     interval = longInterval;
     blink(wl,0,0,1);
     if (wl == 3) {
        blink(2,0,1,1);
     }
     digitalWrite(pumpPin, 0);
  }
  
  deepSleep(interval);
}

int waterlevel(){
  int thresh = 750;
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A3, 1);

  if (analogRead(low) < thresh ){
    return 0;   
  }else if (analogRead(med) < thresh ){
    return 1;  
  }else if (analogRead(high) < thresh ){
    return 2;  
  }else if (analogRead(high) > thresh ){
    return 3;  
  }
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  digitalWrite(A4, 0);  
}


  //423 = air
  //650 = finger grip
  //900 = 1 cm water
  //950 = full submersion 
int moistureLevel(){
  digitalWrite(detectPowerPin, 1);
  delay(100); 
  int invMoisture = analogRead(analogPin);
  digitalWrite(detectPowerPin, 0);
  return 1023 - invMoisture;
}

void deepSleep(int time) {
  delay(time);
}


