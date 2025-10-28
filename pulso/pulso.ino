
// CONSTANTES
int LED_PIN = 2;


void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(5000);
  pulso();

}


// FUNCION PARA HACER PULSOS
void pulso() {
  while (digitalRead(BTN_PULSO) == LOW) { // mientras el botón siga presionado
    for (int brillo = 0; brillo <= 255; brillo++) {
      analogWrite(LED_PIN, brillo);
      delay(5);
      if (digitalRead(BTN_PULSO) == HIGH) return; // si se suelta, salir
    }

    for (int brillo = 255; brillo >= 0; brillo--) {
      analogWrite(LED_PIN, brillo);
      delay(5);
      if (digitalRead(BTN_PULSO) == HIGH) return;
    }
  }
  digitalWrite(LED_PIN, LOW);
}
