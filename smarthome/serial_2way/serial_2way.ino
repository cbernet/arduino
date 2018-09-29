void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
}

void loop() {
  while(Serial.available() ) {
    char msg = Serial.read();  
    Serial.write(msg);
  }
}
