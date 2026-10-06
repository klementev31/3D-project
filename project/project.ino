#include <Stepper.h>
Stepper stepper1(2038, 8, 7, 6, 5);
bool p0, p1;
void Enc(bool e0, bool e1){
  if(p0 ^ p1 ^ e0 ^ e1){
    Serial.println(p1 ^ e0);
  }
  p0 = e0;
  p1 = e1;
}

void setup() {
  Serial.begin(9600);
  p0 = digitalRead(9);
  p1 = digitalRead(10);
}

void loop() {
  Enc(digitalRead(9), digitalRead(10));
  delay(100);
}
