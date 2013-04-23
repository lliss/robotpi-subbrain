// direction = 1, 2
// pulseflag = 4
// break     = 7
// Forward   = 00
// Reverse   = 01
// Left      = 10
// Right     = 11

// Incoming pins
int dirpin1  = 1;
int dirpin2  = 2;
int breakpin = 7;
int pulsepin = 4;
int lightpin = 8;

// Outgoing pins
// Motor 1
int out1 = 3;
int out2 = 5;
int out3 = 6;

// Motor 2
int out4 = 9;
int out5 = 10;
int out6 = 11;

int lights = 14;

// Free pins
// 12, 13

boolean pulse = false;
boolean oldPinSetting = false;

int pin = 12;
int testpin = 13;

void setup() {
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(dirpin1,  INPUT);
  pinMode(dirpin2,  INPUT);
  pinMode(breakpin, INPUT);
  pinMode(pulsepin, INPUT);
  pinMode(lightpin, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);  
  pinMode(out3, OUTPUT);
  pinMode(pin, OUTPUT); 
  pinMode(testpin, OUTPUT); 

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600); 
}
 
void loop() {
  boolean readPulse = digitalRead(pulsepin) == HIGH ? true : false;
  //Serial.println(readPulse);
  pulse = false;
  if (oldPinSetting != readPulse) {
    oldPinSetting = readPulse;
    pulse = true;
  }
  if (pulse) {
    for (int i = 0; i < 3; i++) {
      /*digitalWrite(pin, HIGH);
      delay(150);
      digitalWrite(pin, LOW);
      delay(150);*/
    }
  }
  
  if (digitalRead(dirpin1) == HIGH) {
    /*digitalWrite(out1, HIGH);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    
    digitalWrite(out4, HIGH);
    digitalWrite(out5, LOW);
    digitalWrite(out6, HIGH);*/
    Serial.println("high");
  }
  else {
    /*digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    digitalWrite(out3, HIGH);
    
    digitalWrite(out4, LOW);
    digitalWrite(out5, LOW);
    digitalWrite(out6, HIGH);*/
    Serial.println("low");
  }
  //setForward();
  //setReverse();
  //setLeft();
  //setRight();
  delay(2000);
  setBreak();
  delay(2000);
  //setReverse();
  delay(2000);
  //setLeft();
  delay(2000);
  //setRight();
  delay(2000);
}

void setForward() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, HIGH);
    
  digitalWrite(out4, LOW);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, HIGH);
}

void setReverse() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
    
  digitalWrite(out4, HIGH);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);
}

void setBreak() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
    
  digitalWrite(out4, LOW);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);
}

void setRight() {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
    
  digitalWrite(out4, LOW);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, HIGH);
}

void setLeft() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, HIGH);
    
  digitalWrite(out4, HIGH);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);
}

void parseAction(int p1, int p2, boolean pulse) {
   
}
