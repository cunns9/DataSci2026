// Echo debug - shows what the HC-SR04 is doing behind the scenes
// Same wiring as truck_obstacle_sensor: Trig -> GPIO 4, Echo -> GPIO 5

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  delay(1000);
  Serial.println("--- echo debug start ---");
}

void loop() {
  int echoBefore = digitalRead(ECHO_PIN);  // should be 0 while idle

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 60000);  // longer wait than the main sketch

  Serial.printf("echo idle=%d  pulse=%ld us", echoBefore, duration);
  if (duration == 0)      Serial.println("  -> NO ECHO");
  else                    Serial.printf("  -> %.1f cm\n", duration * 0.0343 / 2.0);

  delay(500);
}
