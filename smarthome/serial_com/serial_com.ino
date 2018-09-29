const int ledPin = 13;

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(100);
  pinMode(ledPin, OUTPUT);
}
void loop()
{
  while (Serial.available())  {
    String message = Serial.readString();  // on soustrait le caractère 0, qui vaut 48 en ASCII
    message = message.substring(0, message.length()-1);
    // light(message);
    // Serial.println(message);
    if(message.compareTo(String("1"))==0) {
      digitalWrite(ledPin, HIGH);
    }
    else if (message.compareTo(String("0"))==0) {
      digitalWrite(ledPin, LOW);   
    }
    delay(1000);
  }
}

void light(int n){
  for (int i = 0; i < n; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}
