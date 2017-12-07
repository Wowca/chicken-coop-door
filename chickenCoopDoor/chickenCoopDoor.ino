#include <Bounce2.h>

const int goUpButtonInput = 2;
const int goDownButtonInput = 3;
const int goLeftOutput = 7;
const int goRightOutput = 8;
const int enableMotorA = 9;

bool isDoorFullyClosedState = false;
bool isDoorFullyOpenState = false;

Bounce debouncerButtonUp = Bounce();
Bounce debouncerButtonDown = Bounce();

void setup() {
  pinMode(goUpButtonInput, INPUT);
  pinMode(goDownButtonInput, INPUT);
  pinMode(goLeftOutput, OUTPUT);
  pinMode(goRightOutput, OUTPUT);

  digitalWrite(goUpButtonInput, HIGH);
  digitalWrite(goDownButtonInput, HIGH);

  digitalWrite(goLeftOutput, LOW);
  digitalWrite(goRightOutput, LOW);

  debouncerButtonUp.attach(goUpButtonInput);
  debouncerButtonDown.attach(goDownButtonInput);
  debouncerButtonUp.interval(5);
  debouncerButtonDown.interval(5);
}

void loop() {
  digitalWrite(enableMotorA, HIGH);
  
  debouncerButtonUp.update();
  debouncerButtonDown.update();
  
  if (isDark())
  {
    isDoorFullyClosed();
    if (!isDoorFullyClosedState)
    {
      moveDoorDown();
    } else {
      motorStop();
    }
  } else {
    isDoorFullyOpen();
    if (!isDoorFullyOpenState)
    {
      moveDoorUp();
    } else {
      motorStop();
    }
  }
  
  delay(10);
}

bool isDark()
{
  int sensorValue = analogRead(A0);  
  if (sensorValue > 100)
  {
    return true;
  }

  return false;
}

void isDoorFullyClosed()
{
  int value = debouncerButtonDown.read();
  
  if (value == 0) {
    if (isDoorFullyClosedState == false) {
      isDoorFullyClosedState = true;
      isDoorFullyOpenState = false;
    }
  }
}

void isDoorFullyOpen()
{
  int value = debouncerButtonUp.read();
  
  if (value == 0) {
    if (isDoorFullyOpenState == false) {
      isDoorFullyOpenState = true;
      isDoorFullyClosedState = false;
    }
  }
}

void motorStop()
{
  digitalWrite(enableMotorA, LOW);
  digitalWrite(goLeftOutput, LOW);
  digitalWrite(goRightOutput, LOW);
}

void moveDoorUp()
{
  digitalWrite(goLeftOutput, HIGH);
  digitalWrite(goRightOutput, LOW);
}

void moveDoorDown()
{
  digitalWrite(goLeftOutput, LOW);
  digitalWrite(goRightOutput, HIGH);
}
