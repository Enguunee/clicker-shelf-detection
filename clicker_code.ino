#include <LiquidCrystal.h>

// LCD wiring: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Photoresistor pins
const int slot1Pin = A5;  // Slot 1
const int slot2Pin = A0;  // Slot 2

// Light threshold
int threshold = 650;

// Average readings for stability
int readAvg(int pin, int samples = 20) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delay(3);
  }
  return sum / samples;
}

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clicker Check");
  delay(1000);
  lcd.clear();
}

void loop() {
  int v1 = readAvg(slot1Pin);
  int v2 = readAvg(slot2Pin);

  bool missing1 = (v1 > threshold);
  bool missing2 = (v2 > threshold);

  lcd.clear();

  if (!missing1 && !missing2) {
    lcd.setCursor(0, 0);
    lcd.print("All present");
    lcd.setCursor(0, 1);
    lcd.print("Slots 1-2 OK");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Missing spot:");
    lcd.setCursor(0, 1);

    bool first = true;
    if (missing1) { lcd.print("1"); first = false; }
    if (missing2) { if (!first) lcd.print(","); lcd.print("2"); }
  }

  delay(400);
}
