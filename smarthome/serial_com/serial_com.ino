const int ledPin = 13;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop()
{
  while (Serial.available())  {
    const char* message = Serial.read()-'0';  // on soustrait le caractère 0, qui vaut 48 en ASCII
    light(message);
  }
  delay(500);
}

void light(int n){
  for (int i = 0; i < n; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}
