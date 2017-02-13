const int goUpButtonInput = 2;
const int goDownButtonInput = 3;
const int goLeftOutput = 7;
const int goRightOutput = 8;
const int enableMotorA = 9;
int buttonUpState = 0;
int buttonDownState = 0;

void setup() {
  pinMode(goUpButtonInput, INPUT);
  pinMode(goDownButtonInput, INPUT);
  pinMode(goLeftOutput, OUTPUT);
  pinMode(goRightOutput, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(goUpButtonInput, HIGH);
  digitalWrite(goDownButtonInput, HIGH);
}

void loop() {
  digitalWrite(enableMotorA, HIGH);
  buttonUpState = digitalRead(goUpButtonInput);

  if (isDark())
  {
    if (!isDoorFullyClosed())
    {
      moveDoorDown();
    } else {
      motorStop();
    }
  } else {
    if (!isDoorFullyOpen())
    {
      moveDoorUp();
    } else {
      motorStop();
    }
  }
}

bool isDark()
{
  int sensorValue = analogRead(A0);  
  if (sensorValue == 1023)
  {
    return true;
  }

  return false;
}

bool isDoorFullyClosed()
{
  buttonDownState = digitalRead(goDownButtonInput);
  if (buttonDownState == LOW) {
    return true;
  }
  return false;
}

bool isDoorFullyOpen()
{
  buttonUpState = digitalRead(goUpButtonInput);
  if (buttonUpState == LOW) {
    return true;
  }
  return false;
}

void motorStop()
{
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void moveDoorUp()
{
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void moveDoorDown()
{
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
