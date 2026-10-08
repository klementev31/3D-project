#include <Stepper.h>

const int PinA = 10;
const int PinB = 9;

// Убедитесь, что физически подключили к плате ULN2003: IN1->8, IN2->6, IN3->7, IN4->5
// (Тут средние пины 6 и 7 уже переставлены местами для правильной фазировки)
Stepper stepper(2038, 8, 7, 6, 5);

int counter = 0; 

// Функция для чтения инкрементального энкодера
int Enc(int pinA, int pinB) {
  static int lastStateA = HIGH;
  int currentStateA = digitalRead(pinA);
  int result = 0;

  if (currentStateA != lastStateA) {
    if (digitalRead(pinB) == currentStateA) {
      result = 1;  // Поворот вправо
    } else {
      result = -1; // Поворот влево
    }
  }
  
  lastStateA = currentStateA;
  return result;
}

void setup() {
  Serial.begin(9600);
  
  // ОБЯЗАТЕЛЬНО настраиваем пины энкодера на вход с подтяжкой INPUT_PULLUP
  pinMode(PinA, INPUT_PULLUP);
  pinMode(PinB, INPUT_PULLUP);
  
  stepper.setSpeed(12); // Максимальная скорость для 28BYJ-48
}

void loop() {
  int change = Enc(PinA, PinB);
  
  if (change != 0) {
    counter += change;
    
    // Ограничиваем счетчик в пределах одного оборота (от 0 до 2037)
    if (counter >= 2038) counter = 0;
    if (counter < 0) counter = 2037;
    
    Serial.print("Положение: ");
    Serial.println(counter);
    
    // ВАЖНО: Делаем небольшое число шагов (например, 20), 
    // чтобы мотор успевал крутиться, но не блокировал энкодер слишком надолго
    stepper.step(change * 20); 
  }
}
