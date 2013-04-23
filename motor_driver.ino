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
  pulse = false;
  if (oldPinSetting != readPulse) {
    oldPinSetting = readPulse;
    pulse = true;
  }

  int p1 = (int) digitalRead(dirpin1);
  int p2 = (int) digitalRead(dirpin2);
  boolean cease = (boolean) digitalRead(breakpin);
  parseAndActivate(p1, p2, false, false);
}

/**
 * @todo
 */
void setForward(boolean pulse) {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, HIGH);

  digitalWrite(out4, LOW);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, HIGH);

  if (pulse) {
    delay(1000);
    setBreak();
  }
}

/**
 * @todo
 */
void setReverse(boolean pulse) {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);

  digitalWrite(out4, HIGH);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);

  if (pulse) {
    delay(1000);
    setBreak();
  }
}

/**
 * @todo
 */
void setBreak() {
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);

  digitalWrite(out4, LOW);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);
}

/**
 * @todo
 */
void setRight(boolean pulse) {
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);

  digitalWrite(out4, LOW);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, HIGH);

  if (pulse) {
    delay(1000);
    setBreak();
  }
}

/**
 * @todo
 */
void setLeft(boolean pulse) {
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH);
  digitalWrite(out3, HIGH);

  digitalWrite(out4, HIGH);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);

  if (pulse) {
    delay(1000);
    setBreak();
  }
}

/**
 * @todo
 *
 * 00 Forward
 * 01 Right
 * 10 Left
 * 11 Reverse
 */
void parseAndActivate(int p1, int p2, boolean cease, boolean pulse) {
  if (cease) {
    setBreak();
    return;
  }
  pulse = false;
  int sum = p1 + p2;
  if (sum == 0) {
    setForward(pulse);
  }
  else if(sum == 2) {
    setReverse(pulse);
  }
  else if (p1 == 1) {
    setLeft(pulse);
  }
  else {
    setRight(pulse);
  }
}
