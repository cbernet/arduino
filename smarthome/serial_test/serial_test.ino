#include <IRremote.h>

IRsend irsend;

#define PIN_MODE 100
#define DIGITAL_WRITE 101
#define DIGITAL_READ 102
#define ANALOG_WRITE 103
#define ANALOG_READ 104
#define AC_POWER 105

int khz = 38;

unsigned int signal_ac_on[] = {
  4588, 4332, 676, 1516, 716, 404, 716, 1480, 676, 1496, 732, 380, 684, 444, 736, 1452, 716, 404, 720, 400, 720, 1476, 712, 408, 716, 404, 716, 1460, 696, 1496, 708, 408, 740, 1452, 712, 412, 680, 444, 736, 376, 688, 1508, 716, 1476, 716, 1476, 604, 1568, 708, 1480, 716, 1472, 716, 1480, 676, 1492, 684, 440, 712, 408, 628, 516, 680, 440, 608, 516, 604, 1592, 676, 444, 604, 1568, 732, 384, 628, 1568, 708, 412, 712, 408, 684, 444, 708, 408, 712, 1476, 716, 404, 720, 1472, 720, 404, 716, 1480, 676, 1492, 680, 1508, 716, 4636, 4616, 4312, 712, 1504, 680, 444, 708, 1480, 712, 1480, 716, 404, 716, 404, 720, 1476, 716, 404, 716, 404, 716, 1476, 608, 516, 680, 440, 608, 1564, 680, 1508, 716, 404, 716, 1480, 712, 412, 652, 520, 676, 444, 604, 1568, 708, 1476, 716, 1476, 740, 1456, 676, 1496, 676, 1508, 716, 1480, 712, 1480, 600, 520, 680, 440, 608, 516, 604, 516, 680, 444, 676, 1512, 716, 404, 720, 1476, 680, 440, 608, 1568, 708, 408, 684, 444, 676, 444, 708, 408, 684, 1508, 716, 404, 716, 1476, 716, 408, 716, 1476, 604, 1564, 712, 1476, 744,
};

unsigned int signal_ac_off[] = {
  4512, 4332, 656, 1512, 712, 408, 652, 1480, 748, 1396, 732, 472, 652, 468, 608, 1560, 712, 408, 660, 444, 708, 1476, 716, 408, 660, 464, 712, 1476, 712, 1460, 712, 404, 716, 1476, 608, 516, 712, 1460, 708, 1480, 712, 1456, 712, 1476, 652, 472, 604, 1560, 716, 1476, 608, 1560, 716, 404, 716, 408, 712, 388, 680, 440, 712, 1476, 716, 408, 604, 500, 708, 1480, 712, 1460, 728, 1456, 712, 408, 716, 404, 716, 408, 660, 444, 704, 408, 716, 404, 656, 468, 604, 496, 712, 1476, 604, 1568, 712, 1476, 660, 1504, 716, 1480, 660, 4668, 4616, 4332, 688, 1484, 708, 404, 716, 1456, 712, 1476, 652, 472, 604, 492, 716, 1476, 660, 440, 680, 440, 712, 1480, 648, 472, 604, 496, 712, 1476, 652, 1520, 680, 440, 712, 1476, 716, 404, 720, 1476, 652, 1520, 708, 1480, 712, 1508, 712, 404, 716, 1476, 652, 1520, 712, 1476, 712, 408, 660, 444, 680, 440, 712, 404, 716, 1476, 660, 444, 708, 404, 716, 1480, 652, 1516, 712, 1476, 716, 408, 712, 408, 660, 440, 712, 408, 716, 404, 656, 496, 712, 404, 716, 408, 652, 1520, 708, 1480, 712, 1456, 712, 1480, 656, 1508, 716
};

void setup() {
  char c;
  Serial.begin(115200);
  Serial.setTimeout(100);
  Serial.flush();
  c = 0;
  Serial.write(c);
  c = 255;
  Serial.write(c);
  c = 0;
  Serial.write(c);
  pinMode(13, OUTPUT);
}
              
void loop() {
  char commande;  
  if (Serial.available()>0) {
     commande = Serial.read();
     if (commande==PIN_MODE) commande_pin_mode();
     else if (commande==DIGITAL_WRITE) commande_digital_write();
     else if (commande==DIGITAL_READ) commande_digital_read();
     else if (commande==ANALOG_WRITE) commande_analog_write();
     else if (commande==ANALOG_READ) commande_analog_read();
     else if (commande==AC_POWER) commande_ac_power();     
  }
  // autres actions à placer ici
}
              
void commande_pin_mode() {
    char pin,mode;
    while (Serial.available()<2);
    pin = Serial.read(); // pin number
    mode = Serial.read(); // 0 = INPUT, 1 = OUTPUT
    pinMode(pin,mode);
}
              
void commande_digital_write() {
   char pin,output;
   while (Serial.available()<2);
   pin = Serial.read(); // pin number
   output = Serial.read(); // 0 = LOW, 1 = HIGH
   digitalWrite(pin,output);
}
              
void commande_digital_read() {
   char pin,input;
   while (Serial.available()<1);
   pin = Serial.read(); // pin number
   input = digitalRead(pin);
   Serial.write(input);
}
              
void commande_analog_write() {
   char pin,output;
   while (Serial.available()<2);
   pin = Serial.read(); // pin number
   output = Serial.read(); // PWM value between 0 and 255
   analogWrite(pin,output);
}
              
void commande_analog_read() {
   char pin;
   int value;
   while (Serial.available()<1);
   pin = Serial.read(); // pin number
   value = analogRead(pin);
   Serial.write((value>>8)&0xFF); // 8 bits de poids fort
   Serial.write(value & 0xFF); // 8 bits de poids faible
}

void commande_ac_power() {
   char output;
   while (Serial.available()<1);
   output = Serial.read(); // 0 = LOW, 1 = HIGH
   if(output==1) {
     irsend.sendRaw(signal_ac_on, sizeof(signal_ac_on) / sizeof(signal_ac_on[0]), khz);
   }
   else if(output==0) {
     irsend.sendRaw(signal_ac_off, sizeof(signal_ac_off) / sizeof(signal_ac_off[0]), khz); 
   }
   delay(5000);
}

void blink(int n) {
  for(unsigned i=0; i<n; i++) {
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    }
  }
