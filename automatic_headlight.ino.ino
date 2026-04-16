int led1 = 8;        // HIGH beam
int led2 = 9;        // LOW beam (always ON in night)
int buzzer = 10;
int buttonPin = 2;
int modePin = 3;
int ldrPin = A0;

int threshold = 500;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(modePin, INPUT);

  Serial.begin(9600);
}

void loop() {

  int mode = digitalRead(modePin);
  int lightValue = analogRead(ldrPin);

  // ================= DAY MODE =================
  if (mode == HIGH) {

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

    if (digitalRead(buttonPin) == LOW) {
      digitalWrite(buzzer, HIGH);

      digitalWrite(led1, HIGH);
      delay(150);
      digitalWrite(led1, LOW);
      delay(150);
      digitalWrite(led1, HIGH);
      delay(150);

      digitalWrite(buzzer, LOW);
    }
  }

  // ================= NIGHT MODE =================
  else {

    digitalWrite(led2, HIGH); // 🔥 ALWAYS ON

    if (digitalRead(buttonPin) == LOW) {

      digitalWrite(buzzer, HIGH);

      digitalWrite(led1, HIGH);
      delay(150);
      digitalWrite(led1, LOW);
      delay(150);
      digitalWrite(led1, HIGH);
      delay(150);

      digitalWrite(buzzer, LOW);
    }

    else if (lightValue > threshold) {
      digitalWrite(led1, LOW); // dipper condition
    }

    else {
      digitalWrite(led1, HIGH); // normal high beam
    }
  }
}