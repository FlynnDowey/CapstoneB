const int trigger_l = 4;
const int echo_l = 1;

const int trigger_r = 6;
const int echo_r = 2;

const int trigger_b = 8;
const int echo_b = 3;

volatile long timeStart_l = 0;
volatile long timeStart_r = 0;
volatile long timeStart_b = 0;
volatile long timeEnd_l = 0;
volatile long timeEnd_r = 0;
volatile long timeEnd_b = 0;
volatile bool triggered_l = false;
volatile bool triggered_r = false;
volatile bool triggered_b = false;

void setup() {
  pinMode(trigger_l, OUTPUT);
  pinMode(trigger_r, OUTPUT);
  pinMode(trigger_b, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(echo_r, INPUT);
  pinMode(echo_b, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(echo_l), handleEcho_l, CHANGE);
  attachInterrupt(digitalPinToInterrupt(echo_r), handleEcho_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(echo_b), handleEcho_b, CHANGE);

  Serial.begin(115200);
}

void loop() {
  // Trigger all sensors simultaneously
  digitalWrite(trigger_l, HIGH);
  digitalWrite(trigger_r, HIGH);
  digitalWrite(trigger_b, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_l, LOW);
  digitalWrite(trigger_r, LOW);
  digitalWrite(trigger_b, LOW);

  // Wait for all sensors to be triggered
  while (!triggered_l || !triggered_r || !triggered_b) {
    // Wait until all sensors have triggered their echo
  }

  // Calculate distance for each sensor
  long timeElapsed_l = timeEnd_l - timeStart_l;
  long timeElapsed_r = timeEnd_r - timeStart_r;
  long timeElapsed_b = timeEnd_b - timeStart_b;
  float distance_l = (float)timeElapsed_l / 1000000 / 2 * 343; // in m
  float distance_r = (float)timeElapsed_r / 1000000 / 2 * 343; // in m
  float distance_b = (float)timeElapsed_b / 1000000 / 2 * 343; // in m

  // Print distances
  Serial.print(distance_l);
  Serial.print(',');
  Serial.print(distance_r);
  Serial.print(',');
  Serial.print(distance_b);
  Serial.print('\n');

  // Reset trigger flags
  triggered_l = false;
  triggered_r = false;
  triggered_b = false;

  delay(500);
}

void handleEcho_l() {
  if (digitalRead(echo_l) == HIGH) {
    timeStart_l = micros();
  } else {
    timeEnd_l = micros();
    triggered_l = true;
  }
}

void handleEcho_r() {
  if (digitalRead(echo_r) == HIGH) {
    timeStart_r = micros();
  } else {
    timeEnd_r = micros();
    triggered_r = true;
  }
}

void handleEcho_b() {
  if (digitalRead(echo_b) == HIGH) {
    timeStart_b = micros();
  } else {
    timeEnd_b = micros();
    triggered_b = true;
  }
}
