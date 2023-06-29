const int trigger_l = 4;
const int echo_l = 5;

const int trigger_r = 6;
const int echo_r = 7;

const int trigger_b = 8;
const int echo_b = 9;


long timeElapsed_l = 0;
long timeElapsed_r = 0;
long timeElapsed_b = 0;
float distance_l = 0;
float distance_r = 0;
float distance_b = 0;

void setup() {
    pinMode(trigger_l, OUTPUT);
    pinMode(echo_l, INPUT);
    pinMode(trigger_r, OUTPUT);
    pinMode(echo_r, INPUT);
    pinMode(trigger_b, OUTPUT);
    pinMode(echo_b, INPUT);
    Serial.begin(115200);
}

void loop() {
    // Clear trigger
    digitalWrite(trigger_l,LOW);
    digitalWrite(trigger_r,LOW);
    digitalWrite(trigger_b,LOW);
    delayMicroseconds(2);
    

    // send 10 microseond trigger
    digitalWrite(trigger_l, HIGH);
    digitalWrite(trigger_r, HIGH);
    digitalWrite(trigger_b, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger_l, LOW);
    digitalWrite(trigger_r, LOW);
    digitalWrite(trigger_b, LOW);

    // time to get echo
    timeElapsed_l = pulseIn(echo_l, HIGH);
    timeElapsed_r = pulseIn(echo_r, HIGH);
    timeElapsed_b = pulseIn(echo_b, HIGH);

    // convert time to distance
    // Divide by 1000000 (convert microseconds to seconds)
    // Divide by 2 for distance there and back
    // Multiply by speed of sound 343m/s
    distance_l = (float)timeElapsed_l / 1000000 / 2 * 343; // in m
    distance_r = (float)timeElapsed_r / 1000000 / 2 * 343; // in m
    distance_b = (float)timeElapsed_b / 1000000 / 2 * 343; // in m

    Serial.print(distance_l);
    Serial.print(',');
    Serial.print(distance_r);
    Serial.print(',');
    Serial.print(distance_b);
    Serial.print('\n');

    delay(500);
}