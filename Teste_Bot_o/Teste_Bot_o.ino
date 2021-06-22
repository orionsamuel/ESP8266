void setup() {
  pinMode(14, INPUT);
  Serial.begin(115200);

}

void loop() {
  Serial.println(digitalRead(14));
  delay(500);

}
