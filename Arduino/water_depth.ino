#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C address 0x27, 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int waterLevelPin = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  // Show welcome message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello! Welcome");
  lcd.setCursor(0, 1);
  lcd.print("to SenimSu");
  delay(2000); // 2 seconds
}

void loop() {
  int raw = analogRead(waterLevelPin);

  // Map 50%-71% to 0-100
  int depth = map(raw, 42, 60, 0, 100);
  depth = constrain(depth, 0, 100); // Ensure 0-100%

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water Depth:");
  lcd.setCursor(0,1);
  lcd.print(depth);
  lcd.print("%");

  // Send to Serial for Python
  Serial.println(depth);

  delay(500); // Update twice per second
}
