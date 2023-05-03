#define soundSensor A1
#define ldrPin A2

#define irSensor 5
#define trigPin 6
#define echoPin 7

#define red1 8
#define yellow1 9
#define green1 10
#define red2 11
#define yellow2 12
#define green2 13

void emergency_vehicle()
{
  int soundSensorState = analogRead(soundSensor);
  if (soundSensorState > 300)
  {
    delay(2000);
    digitalWrite(green2, LOW);
    digitalWrite(yellow2, HIGH);
    delay(1000);
    digitalWrite(yellow2, LOW);
    digitalWrite(red2, HIGH);
    for (int irSensorState = digitalRead(irSensor);; irSensorState = digitalRead(irSensor))
    {
      if (irSensorState == HIGH)
      {
        digitalWrite(red1, LOW);
        digitalWrite(green1, HIGH);
        break;
      }
    }
  }
  while (soundSensorState > 300)
    soundSensorState = analogRead(soundSensor);
}

void side_road()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;
  Serial.println(distance);
  if (distance < 10)
  {
    delay(2000);
    digitalWrite(green1, LOW);
    digitalWrite(yellow1, HIGH);
    delay(1000);
    digitalWrite(yellow1, LOW);
    digitalWrite(red1, HIGH);
    for (int irSensorState = digitalRead(irSensor);; irSensorState = digitalRead(irSensor))
    {
      if (irSensorState == HIGH)
      {
        digitalWrite(red2, LOW);
        digitalWrite(green2, HIGH);
        break;
      }
    }
  }

  emergency_vehicle();

  if (digitalRead(red2) == HIGH)
    side_road();

  while (distance < 10)
  {
    emergency_vehicle();
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.0343 / 2;
  }
}

void change_brightness()
{
  int ldrValue = analogRead(ldrPin);
  int ledBrightness = map(ldrValue, 0, 1023, 0, 255);

  if (digitalRead(red1) == HIGH)
    analogWrite(red1, ledBrightness);
  else if (digitalRead(green1) == HIGH)
    analogWrite(green1, ledBrightness);
  else
    analogWrite(yellow1, ledBrightness);

  if (digitalRead(red2) == HIGH)
    analogWrite(red2, ledBrightness);
  else if (digitalRead(green2) == HIGH)
    analogWrite(green2, ledBrightness);
  else
    analogWrite(yellow2, ledBrightness);

  side_road();
}

void setup()
{
  Serial.begin(9600);
  pinMode(soundSensor, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(irSensor, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
}

void loop()
{
  delay(2000);
  digitalWrite(green2, LOW);
  digitalWrite(yellow2, HIGH);
  delay(2000);
  digitalWrite(yellow2, LOW);
  digitalWrite(red2, HIGH);
  for (int irSensorState = digitalRead(irSensor);; irSensorState = digitalRead(irSensor))
  {
    if (irSensorState == HIGH)
    {
      digitalWrite(red1, LOW);
      digitalWrite(green1, HIGH);
      break;
    }
  }

  change_brightness();
}
