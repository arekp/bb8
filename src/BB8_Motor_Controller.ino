/*
 * BB8_Motor_Controller.ino
 * Kod dla płytki Arduino Nano ("Mięśnie")
 * ------------------------------------
 * Odpowiedzialność: Odbieranie prostych komend przez port szeregowy (Serial) i precyzyjne sterowanie silnikami.
 * Ten kod jest bardzo zbliżony do oryginalnej wersji, ale używa sprzętowego portu szeregowego do komunikacji.
 * 
 * Używane biblioteki: brak dodatkowych.
 */

// Definicja pinów dla Arduino Nano
// Motor A
int left_1 = 2;
int left_2 = 3;
// Motor B
int right_1 = 4;
int right_2 = 5;

// Piny PWM (enable)
int left_en = 9;
int right_en = 6;

// Parametry ruchu
int hiz = 250;
int yavas_hiz = 150;
int ramp_time = 1;
int anlik_hiz = 0;
int anlik_yavas_hiz = 0;

// Diody LED
int yesil_led = A0;
int kirmizi_led = A1;
int mavi_led = A2;

void setup() {
  // Definicja pinów jako wyjścia
  pinMode(left_1, OUTPUT);
  pinMode(left_2, OUTPUT);
  pinMode(right_1, OUTPUT);
  pinMode(right_2, OUTPUT);
  pinMode(left_en, OUTPUT);
  pinMode(right_en, OUTPUT);
  pinMode(yesil_led, OUTPUT);
  pinMode(kirmizi_led, OUTPUT);
  pinMode(mavi_led, OUTPUT);

  // Uruchomienie portu szeregowego do nasłuchiwania na komendy od ESP32
  Serial.begin(9600);

  // Sekwencja testowa LED
  digitalWrite(yesil_led, HIGH); delay(250);
  digitalWrite(kirmizi_led, HIGH); delay(250);
  digitalWrite(mavi_led, HIGH); delay(250);
  digitalWrite(yesil_led, LOW); delay(250);
  digitalWrite(kirmizi_led, LOW); delay(250);
  digitalWrite(mavi_led, LOW);

  // Zatrzymaj silniki przy starcie
  dur();
}

void loop() {
  // Sprawdź, czy nadeszła nowa komenda od ESP32
  if (Serial.available()) {
    char command = Serial.read();

    // Uruchom odpowiednią funkcję ruchu na podstawie otrzymanego znaku
    if (command == 'F') {
      ileri();
    } else if (command == 'B') {
      geri();
    } else if (command == 'L') {
      sol();
    } else if (command == 'R') {
      sag();
    } else if (command == 'I') {
      sag_ileri_capraz();
    } else if (command == 'G') {
      sol_ileri_capraz();
    } else if (command == 'J') {
      sol_geri_capraz();
    } else if (command == 'H') {
      sag_geri_capraz();
    } else if (command == 'S') {
      dur();
    }
  }
}

// --- Funkcje sterujące silnikami (bez zmian w stosunku do oryginału) ---

void ileri() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    digitalWrite(left_1, HIGH);
    digitalWrite(left_2, LOW);
    digitalWrite(right_1, LOW);
    digitalWrite(right_2, HIGH);
    analogWrite(left_en, anlik_hiz);
    analogWrite(right_en, anlik_hiz);
  }
}

void geri() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    digitalWrite(left_1, LOW);
    digitalWrite(left_2, HIGH);
    digitalWrite(right_1, HIGH);
    digitalWrite(right_2, LOW);
    analogWrite(left_en, anlik_hiz);
    analogWrite(right_en, anlik_hiz);
  }
}

void sol() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    digitalWrite(left_1, LOW);
    digitalWrite(left_2, HIGH);
    digitalWrite(right_1, LOW);
    digitalWrite(right_2, HIGH);
    analogWrite(left_en, anlik_hiz);
    analogWrite(right_en, anlik_hiz);
  }
}

void sag() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    digitalWrite(left_1, HIGH);
    digitalWrite(left_2, LOW);
    digitalWrite(right_1, HIGH);
    digitalWrite(right_2, LOW);
    analogWrite(left_en, anlik_hiz);
    analogWrite(right_en, anlik_hiz);
  }
}

void dur() {
  digitalWrite(left_1, LOW);
  digitalWrite(left_2, LOW);
  digitalWrite(right_1, LOW);
  digitalWrite(right_2, LOW);
  analogWrite(left_en, 0);
  analogWrite(right_en, 0);
}

void sag_ileri_capraz() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    for (anlik_yavas_hiz = 0; anlik_yavas_hiz <= yavas_hiz; anlik_yavas_hiz = anlik_yavas_hiz + ramp_time) {
      digitalWrite(left_1, HIGH);
      digitalWrite(left_2, LOW);
      digitalWrite(right_1, LOW);
      digitalWrite(right_2, HIGH);
      analogWrite(left_en, anlik_yavas_hiz);
      analogWrite(right_en, anlik_hiz);
    }
  }
}

void sol_ileri_capraz() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    for (anlik_yavas_hiz = 0; anlik_yavas_hiz <= yavas_hiz; anlik_yavas_hiz = anlik_yavas_hiz + ramp_time) {
      digitalWrite(left_1, HIGH);
      digitalWrite(left_2, LOW);
      digitalWrite(right_1, LOW);
      digitalWrite(right_2, HIGH);
      analogWrite(left_en, anlik_hiz);
      analogWrite(right_en, anlik_yavas_hiz);
    }
  }
}

void sol_geri_capraz() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    for (anlik_yavas_hiz = 0; anlik_yavas_hiz <= yavas_hiz; anlik_yavas_hiz = anlik_yavas_hiz + ramp_time) {
      digitalWrite(left_1, LOW);
      digitalWrite(left_2, HIGH);
      digitalWrite(right_1, HIGH);
      digitalWrite(right_2, LOW);
      analogWrite(left_en, anlik_hiz);
      analogWrite(right_en, anlik_yavas_hiz);
    }
  }
}

void sag_geri_capraz() {
  for (anlik_hiz = 0; anlik_hiz <= hiz; anlik_hiz = anlik_hiz + ramp_time) {
    for (anlik_yavas_hiz = 0; anlik_yavas_hiz <= yavas_hiz; anlik_yavas_hiz = anlik_yavas_hiz + ramp_time) {
      digitalWrite(left_1, LOW);
      digitalWrite(left_2, HIGH);
      digitalWrite(right_1, HIGH);
      digitalWrite(right_2, LOW);
      analogWrite(left_en, anlik_yavas_hiz);
      analogWrite(right_en, anlik_hiz);
    }
  }
}