/**
 * @file
 * Handle translating incoming data signals from another device (Raspberry Pi)
 * to motor controls.
 */

/**
 * Pin Descriptions:
 *
 * direction = 2, 34
 * pulseflag = 4
 * break     = 7
 *
 */

/**
 * Direction Pins Translation:
 *
 * Forward   = 00
 * Reverse   = 11
 * Left      = 01
 * Right     = 10
 */

// Incoming pins
int dirpin1  = 2;
int dirpin2  = 34;
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

// Logic for implementing short bursts of activity on a motor.
// Not currently implemented.
boolean pulse = false;
boolean oldPinSetting = false;

void setup() {
  // Initialize input and output pins
  pinMode(dirpin1,  INPUT);
  pinMode(dirpin2,  INPUT);
  pinMode(breakpin, INPUT);
  pinMode(pulsepin, INPUT);
  pinMode(lightpin, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);
  pinMode(out6, OUTPUT);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // State setting flip for the motor pulse.
  // Not currently implemented.
  boolean readPulse = digitalRead(pulsepin) == HIGH ? true : false;
  pulse = false;
  if (oldPinSetting != readPulse) {
    oldPinSetting = readPulse;
    pulse = true;
  }

  // Read state of direction pins.
  int p1 = (int) digitalRead(dirpin1);
  int p2 = (int) digitalRead(dirpin2);
  Serial.println(p1);
  // Read the state of the break. Convert it into a boolean.
  boolean cease = (boolean) digitalRead(breakpin);
  cease = !cease;
  parseAndActivate(p1, p2, cease, false);
}

/**
 * Activate motors to move the robot forward.
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
 * Activate motors to move the robot backward.
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
 * @see CanaKit motor driver docs.
 * Stop the motors.
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
 * Activate motors on the left side to turn us right.
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
 * Activate motors on the right side to turn us left.
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
 * Use informationfrom both direction pins, the stop signal and the pulse
 * signal. Translate these into activations or deactivations on the motots.
 *
 * 00 Forward
 * 10 Right
 * 01 Left
 * 11 Reverse
 */
void parseAndActivate(int p1, int p2, boolean cease, boolean pulse) {
  if (cease) {
    setBreak();
    return;
  }
  // Since this isn't in use right now, just force the pulse to false.
  pulse = false;
  if (p1 == 0 && p2 == 0) {
    setForward(pulse);
  }
  else if(p1 == 1 && p2 == 1) {
    setReverse(pulse);
  }
  else if (p1 == 1 && p2 == 0) {
    setLeft(pulse);
  }
  else if (p1 == 0 && p2 == 1) {
    setRight(pulse);
  }
}
