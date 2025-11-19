#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// === LCD I2C ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Servo ===
Servo pompa;
const int servoPin = 9;

// === Tombol ===
const int btnOn  = 2;
const int btnOff = 3;
const int btnAuto = 4;

// === LED ===
const int ledManual = 8;
const int ledAuto   = 10;

// === Potensiometer ===
const int potPin = A0;     // PIN POTENSIO
int potValue = 0;          // nilai mentah
int autoDelay = 1000;      // delay auto mode

// === Status ===
bool autoMode = false;

bool lastOn  = HIGH;
bool lastOff = HIGH;
bool lastAuto = HIGH;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pompa.attach(servoPin);
  pompa.write(0); 

  pinMode(btnOn, INPUT_PULLUP);
  pinMode(btnOff, INPUT_PULLUP);
  pinMode(btnAuto, INPUT_PULLUP);

  pinMode(ledManual, OUTPUT);
  pinMode(ledAuto, OUTPUT);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" MINI POMPA AIR ");
  lcd.setCursor(0,1);
  lcd.print(" SYSTEM SIAP ");

  Serial.println("=== SISTEM SIAP ===");
  Serial.println("Tombol1 = ON");
  Serial.println("Tombol2 = OFF");
  Serial.println("Tombol3 = AUTO");
  Serial.println("Pot = Atur kecepatan AUTO");
  Serial.println("===================");

  delay(1500);
  lcd.clear();
}

void loop() {

  // ==== Baca Potensiometer ====
  potValue = analogRead(potPin);  
  autoDelay = map(potValue, 0, 1023, 300, 1500); 
  // Delay auto antara 300ms hingga 1500ms

  // ==== Tombol ====
  bool onPress = digitalRead(btnOn);
  bool offPress = digitalRead(btnOff);
  bool autoPress = digitalRead(btnAuto);

  // === TOMBOL 1: ON ===
  if (lastOn == HIGH && onPress == LOW) {
    autoMode = false;
    digitalWrite(ledAuto, LOW);

    pompa.write(90);
    digitalWrite(ledManual, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("POMPA: ON");

    Serial.println("POMPA ON (Manual)");

    delay(250);
  }
  lastOn = onPress;

  // === TOMBOL 2: OFF ===
  if (lastOff == HIGH && offPress == LOW) {
    autoMode = false;
    digitalWrite(ledAuto, LOW);

    pompa.write(0);
    digitalWrite(ledManual, LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("POMPA: OFF");

    Serial.println("POMPA OFF (Manual)");

    delay(250);
  }
  lastOff = offPress;

  // === TOMBOL 3: AUTO ===
  if (lastAuto == HIGH && autoPress == LOW) {
    autoMode = !autoMode;

    digitalWrite(ledManual, LOW);
    digitalWrite(ledAuto, autoMode);

    lcd.clear();
    lcd.print("MODE: AUTO");

    Serial.println("MODE AUTO AKTIF");

    delay(250);
  }
  lastAuto = autoPress;

  // === MODE AUTO ===
  if (autoMode) {

    // ==== Tampilkan nilai potensiometer ====
    lcd.setCursor(0,1);
    lcd.print("Delay:");
    lcd.print(autoDelay);
    lcd.print("ms  ");

    Serial.print("AUTO DELAY: ");
    Serial.println(autoDelay);

    // AUTO ON
    pompa.write(90);
    Serial.println("AUTO: POMPA ON");
    delay(autoDelay);

    // AUTO OFF
    pompa.write(0);
    Serial.println("AUTO: POMPA OFF");
    delay(autoDelay);
  }
}

