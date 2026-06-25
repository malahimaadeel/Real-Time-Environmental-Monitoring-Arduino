#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tmpPin = A0;
int humPin = A1;
int phPin = A2;
int buzzer = 9;
int redLED = 6;
int grnLED = 7;
int fanPin = 10;

float tempC, humidity, phValue;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(grnLED, OUTPUT);
  pinMode(fanPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  int tmpRaw = analogRead(tmpPin);
  tempC = (tmpRaw * 5.0 / 1023.0 - 0.5) * 100.0;

  int humRaw = analogRead(humPin);
  humidity = humRaw * (100.0 / 1023.0);

  int phRaw = analogRead(phPin);
  phValue = phRaw * (14.0 / 1023.0);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(tempC, 1);
  lcd.print("C H:");
  lcd.print(humidity, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("pH:");
  lcd.print(phValue, 1);

  bool alert = false;

  if (tempC > 40) {
    digitalWrite(fanPin, HIGH);
    alert = true;
  } else {
    digitalWrite(fanPin, LOW);
  }

  if (humidity > 80) alert = true;
  if (phValue < 4.0 || phValue > 9.0) alert = true;

  if (alert) {
    digitalWrite(redLED, HIGH);
    digitalWrite(grnLED, LOW);
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(grnLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}
