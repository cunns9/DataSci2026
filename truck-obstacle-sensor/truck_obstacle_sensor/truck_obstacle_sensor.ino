// RC Truck Obstacle Detector - ESP32-S3 + HC-SR04
// Trig -> GPIO 4, Echo -> GPIO 5 (through voltage divider), VCC -> 5Vin, GND -> GND
// Built-in RGB LED: GREEN = clear, YELLOW = object 1-5 ft, RED = closer than 1 ft

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;

#ifndef RGB_BUILTIN
#define RGB_BUILTIN 48   // change to 38 if your LED doesn't light
#endif

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  neopixelWrite(RGB_BUILTIN, r, g, b);
}

// Returns distance in feet, or -1 if nothing echoed back
float readDistanceFeet() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);      // "shout" for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // wait up to 30 ms for the echo
  if (duration == 0) return -1;

  float cm = duration * 0.0343 / 2.0;  // speed of sound, there and back
  return cm / 30.48;                   // cm -> feet
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  setColor(0, 0, 20);  // dim blue = starting up
  delay(500);
}

void loop() {
  float ft = readDistanceFeet();

  if (ft < 0 || ft > 5.0) {
    Serial.println("Clear (nothing within 5 ft)");
    setColor(0, 40, 0);              // green
  } else if (ft >= 1.0) {
    Serial.printf("Object detected: %.1f ft\n", ft);
    setColor(40, 30, 0);             // yellow
  } else {
    Serial.printf("TOO CLOSE: %.1f ft\n", ft);
    setColor(60, 0, 0);              // red
  }

  delay(100);  // sensor needs ~60 ms between pings
}
