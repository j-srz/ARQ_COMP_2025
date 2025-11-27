
// CONSTANTES
// LEDS
int pin_led_show = 2;
int pin_led_1 = 40;
int pin_led_2 = 39;
int pin_led_3 = 38;
int pin_led_4 = 37;
int pin_led_5 = 36;
int pin_led_6 = 35;
// BOTONES
int pin_btn_1 = 16;
int pin_btn_2 = 15;
int pin_btn_3 = 7;
int pin_btn_4 = 4;
int pin_btn_5 = 5;
int pin_btn_6 = 6;

// BUZZER
const int buzzerPin = 21;


// VARIABLES
bool gano = false;
bool perdio = false;
int intentos = 3;
int numSecreto = random(1,7);

bool fueClickeado_btn_1 = false;
bool fueClickeado_btn_2 = false;
bool fueClickeado_btn_3 = false;
bool fueClickeado_btn_4 = false;
bool fueClickeado_btn_5 = false;
bool fueClickeado_btn_6 = false;







void setup() {
  pinMode(pin_led_1, OUTPUT);
  pinMode(pin_led_2, OUTPUT);
  pinMode(pin_led_3, OUTPUT);
  pinMode(pin_led_4, OUTPUT);
  pinMode(pin_led_5, OUTPUT);
  pinMode(pin_led_6, OUTPUT);

  pinMode(pin_led_show, OUTPUT);

  pinMode(pin_btn_1, INPUT_PULLUP);
  pinMode(pin_btn_2, INPUT_PULLUP);
  pinMode(pin_btn_3, INPUT_PULLUP);
  pinMode(pin_btn_4, INPUT_PULLUP);
  pinMode(pin_btn_5, INPUT_PULLUP);
  pinMode(pin_btn_6, INPUT_PULLUP);
  

}

void loop() {
  
  if ( gano ) {
    ganar();
    finChido();

    delay(1000);
    restablecer();

    return;
    

    
  } else if ( perdio ) {
    perder();
     fin();

     
     delay(1000);
     restablecer();
     return;

     
  } else if (digitalRead(pin_btn_1) == LOW && !fueClickeado_btn_1) {
    presionarBtn();
    digitalWrite(pin_led_1, HIGH);
    delay(1000);
    digitalWrite(pin_led_1, LOW);

    intentos -= 1;
    check(1);

    fueClickeado_btn_1 = true;
    
    
    
  } else if (digitalRead(pin_btn_2) == LOW  && !fueClickeado_btn_2) {
    presionarBtn();
    digitalWrite(pin_led_2, HIGH);
    delay(1000);
    digitalWrite(pin_led_2, LOW);


intentos -= 1;
    check(2);
    
    fueClickeado_btn_2 = true;
    
    
  } else if (digitalRead(pin_btn_3) == LOW  && !fueClickeado_btn_3) {
    presionarBtn();
    digitalWrite(pin_led_3, HIGH);
    delay(1000);
    digitalWrite(pin_led_3, LOW);

intentos -= 1;
    check(3);
    
    fueClickeado_btn_3 = true;
    
  } else if (digitalRead(pin_btn_4) == LOW  && !fueClickeado_btn_4) {
    presionarBtn();
    digitalWrite(pin_led_4, HIGH);
    delay(1000);
    digitalWrite(pin_led_4, LOW);


intentos -= 1;
    check(4);
    
    fueClickeado_btn_4 = true;

    
    
  } else if (digitalRead(pin_btn_5) == LOW  && !fueClickeado_btn_5) {
    presionarBtn();
    digitalWrite(pin_led_5, HIGH);
    delay(1000);
    digitalWrite(pin_led_5, LOW);

intentos -= 1;
    check(5);
    
    fueClickeado_btn_5 = true;
    
    
  } else if (digitalRead(pin_btn_6) == LOW  && !fueClickeado_btn_6) {
    presionarBtn();
    digitalWrite(pin_led_6, HIGH);
    delay(1000);
    digitalWrite(pin_led_6, LOW);


intentos -= 1;
    check(6);
    
    fueClickeado_btn_6 = true;
    
  }


  

  
  digitalWrite(pin_led_show, HIGH);

}





bool check (int num) {
  if (num == numSecreto) {
    gano = true;
    return true;
  } else if (intentos == 0) { 
    perdio = true;
    return false;
  }
  return false;
}

void finChido() {
digitalWrite(pin_led_1, HIGH);
    delay(200); 
    digitalWrite(pin_led_1, LOW);
    
    digitalWrite(pin_led_2, HIGH);
    delay(200);
    digitalWrite(pin_led_2, LOW);
    
    digitalWrite(pin_led_3, HIGH);
    delay(200);
    digitalWrite(pin_led_3, LOW);
    
    digitalWrite(pin_led_4, HIGH);
    delay(200);
    digitalWrite(pin_led_4, LOW);
    
    digitalWrite(pin_led_5, HIGH);
    delay(200);
    digitalWrite(pin_led_5, LOW);
    
    digitalWrite(pin_led_6, HIGH);
    delay(200);
    digitalWrite(pin_led_6, LOW); 
}



void fin() {
    digitalWrite(pin_led_show, LOW);
    digitalWrite(pin_led_1, HIGH);
    digitalWrite(pin_led_2, HIGH);
    digitalWrite(pin_led_3, HIGH);
    digitalWrite(pin_led_4, HIGH);
    digitalWrite(pin_led_5, HIGH);
    digitalWrite(pin_led_6, HIGH);


    delay(500);

    digitalWrite(pin_led_1, LOW);
    digitalWrite(pin_led_2, LOW);
    digitalWrite(pin_led_3, LOW);
    digitalWrite(pin_led_4, LOW);
    digitalWrite(pin_led_5, LOW);
    digitalWrite(pin_led_6, LOW);

    delay(500);


    digitalWrite(pin_led_1, HIGH);
    digitalWrite(pin_led_2, HIGH);
    digitalWrite(pin_led_3, HIGH);
    digitalWrite(pin_led_4, HIGH);
    digitalWrite(pin_led_5, HIGH);
    digitalWrite(pin_led_6, HIGH);


    delay(500);

    digitalWrite(pin_led_show, HIGH);
    digitalWrite(pin_led_1, LOW);
    digitalWrite(pin_led_2, LOW);
    digitalWrite(pin_led_3, LOW);
    digitalWrite(pin_led_4, LOW);
    digitalWrite(pin_led_5, LOW);
    digitalWrite(pin_led_6, LOW);
}









void restablecer() {
  gano = false;
  perdio = false;
  fueClickeado_btn_1 = false;
  fueClickeado_btn_2 = false;
  fueClickeado_btn_3 = false;
  fueClickeado_btn_4 = false;
  fueClickeado_btn_5 = false;
  fueClickeado_btn_6 = false;
  intentos = 3;
  numSecreto = random(1,7);

}










void presionarBtn() {

  // Tono de 1200 Hz por 100 ms
  tone(buzzerPin, 1200, 100);
  delay(100);
  noTone(buzzerPin); 
}



void ganar() {

  

  int notas[] = {523, 659, 784, 1047};
  int duracionNota = 150; // Duración de cada nota en ms
  
  for (int i = 0; i < 4; i++) {
    tone(buzzerPin, notas[i], duracionNota);
    delay(duracionNota + 20); // Pausa ligeramente más larga que la nota
  }
  noTone(buzzerPin);
}



void perder() {

  

  

  for (int freq = 800; freq >= 400; freq -= 50) {
    tone(buzzerPin, freq, 25);
    delay(20);
  }
  noTone(buzzerPin);
  delay(100);
  

  for (int freq = 700; freq >= 300; freq -= 50) {
    tone(buzzerPin, freq, 25);
    delay(20);
  }
  noTone(buzzerPin);
}
