#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---- LCD Setup ----
// Create LCD object for 16x2 I2C LCD (Frank de Brabander library)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Replace 0x27 if your LCD has a different I2C address

// ---- Pulse Sensor Setup ----
const int pulsePin = A0;
const int blinkPin = 13;

volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false;
volatile boolean QS = false;

volatile int rate[10];
volatile unsigned long sampleCounter = 0;
volatile unsigned long lastBeatTime = 0;
volatile int P = 512;
volatile int T = 512;
volatile int thresh = 525;
volatile int amp = 100;
volatile boolean firstBeat = true;
volatile boolean secondBeat = false;

// ---- Setup ----
void setup() {
  Serial.begin(115200);
  pinMode(blinkPin, OUTPUT);

  // LCD setup
  lcd.init();          // Initialize LCD
  lcd.backlight();     // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Setup Timer2 interrupt for Pulse Sensor
  interruptSetup();
}

// ---- Main Loop ----
void loop() {
  if (QS) { // Heartbeat detected
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heart Beat Found");
    lcd.setCursor(0, 1);
    lcd.print("BPM: ");
    lcd.print(BPM);

    Serial.print("BPM: ");
    Serial.println(BPM);

    QS = false; // Reset flag
  }
  delay(20);
}

// ---- Timer2 Interrupt Setup ----
void interruptSetup() {
  TCCR2A = 0x02;  // CTC mode
  TCCR2B = 0x06;  // 256 prescaler
  OCR2A = 0x7C;   // 124 -> 2ms
  TIMSK2 = 0x02;  // Enable compare interrupt
  sei();          // Enable global interrupts
}

// ---- Timer2 ISR ----
ISR(TIMER2_COMPA_vect) {
  cli();
  Signal = analogRead(pulsePin);
  sampleCounter += 2;
  int N = sampleCounter - lastBeatTime;

  // Trough
  if (Signal < thresh && N > (IBI / 5) * 3) {
    if (Signal < T) T = Signal;
  }

  // Peak
  if (Signal > thresh && Signal > P) P = Signal;

  // Heartbeat detected
  if (N > 250) {
    if ((Signal > thresh) && (Pulse == false) && (N > (IBI / 5) * 3)) {
      Pulse = true;
      digitalWrite(blinkPin, HIGH);
      IBI = sampleCounter - lastBeatTime;
      lastBeatTime = sampleCounter;

      if (secondBeat) {
        secondBeat = false;
        for (int i = 0; i <= 9; i++) rate[i] = IBI;
      }

      if (firstBeat) {
        firstBeat = false;
        secondBeat = true;
        sei();
        return;
      }

      long runningTotal = 0;
      for (int i = 0; i <= 8; i++) {
        rate[i] = rate[i + 1];
        runningTotal += rate[i];
      }
      rate[9] = IBI;
      runningTotal += rate[9];
      runningTotal /= 10;
      BPM = 60000 / runningTotal;
      QS = true;
    }
  }

  // End of pulse wave
  if (Signal < thresh && Pulse == true) {
    digitalWrite(blinkPin, LOW);
    Pulse = false;
    amp = P - T;
    thresh = amp / 2 + T;
    P = thresh;
    T = thresh;
  }

  // Reset if no beat detected for 2.5s
  if (N > 2500) {
    thresh = 512;
    P = 512;
    T = 512;
    lastBeatTime = sampleCounter;
    firstBeat = true;
    secondBeat = false;
  }

  sei();
}
