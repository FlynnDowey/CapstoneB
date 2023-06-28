const int trigger_l = 4;
const int echo_l = 5;

const int trigger_r;
const int echo_r;

const int trigger_b;
const int echo_b;


long timeElapsed_l = 0;
long timeElapsed_r = 0;
long timeElapsed_b = 0;
float distance_l = 0;
float distance_r = 0;
float distance_b = 0;

void setup() {
    pinMode(trigger_l, OUTPUT);
    pinMode(echo_r, INPUT);
    Serial.begin(115200);
}

void loop() {
    // Clear trigger
    digitalWrite(trigger_l,LOW);
    delayMicroseconds(2);

    // send 10 microseond trigger
    digitalWrite(trigger_l, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_l, LOW);

    // time to get echo
    timeElapsed_l = pulseIn(echo_l, HIGH);
    timeElapsed_r = pulseIn(echo_r, HIGH);
    timeElapsed_b = pulseIn(echo_b, HIGH);

    // convert time to distance
    // Divide by 1000000 (convert microseconds to seconds)
    // Divide by 2 for distance there and back
    // Multiply by speed of sound 34300cm/s
    distance_l = (float)timeElapsed_l / 1000000 / 2 * 34300; // in cm
    distance_r = 0;
    distance_b = 0;

    Serial.print(distance_l);
    Serial.print(',');
    Serial.print(distance_r);
    Serial.print(',');
    Serial.print(distance_b);
    Serial.print('\n');

    delay(500);
}