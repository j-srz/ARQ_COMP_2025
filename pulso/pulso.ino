
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
  for (int brillo = 0; brillo <= 255; brillo++) {
    analogWrite(LED_PIN, brillo);  // Salida PWM
    delay(10);
  }

  for (int brillo = 255; brillo >= 0; brillo--) {
    analogWrite(LED_PIN, brillo);
    delay(10);
  }
}
