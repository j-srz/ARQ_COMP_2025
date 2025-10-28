
#include <Adafruit_NeoPixel.h> // Librería necesaria, instalarla desde el gestor de librerías

Adafruit_NeoPixel LED_RGB(1, 48, NEO_GRBW + NEO_KHZ800); // Creamos el objeto que manejará el led RGB GPIO48

// CONSTANTES
int LED_PIN = 2;
int BTN_SOS = 4;
int BTN_BLINK = 5;
int BTN_PULSO = 6;




void setup() {
  LED_RGB.begin(); // Inicia el objeto que hemos creado asociado a la librería NeoPixel
  LED_RGB.setBrightness(150); // Para el brillo del led
  colorearRGB(0,0,0);
  
  pinMode(LED_PIN, OUTPUT);


  pinMode(BTN_SOS, INPUT_PULLUP);
  pinMode(BTN_BLINK, INPUT_PULLUP);
  pinMode(BTN_PULSO, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(BTN_SOS) == LOW) {
    sos();
  }

  else if (digitalRead(BTN_BLINK) == LOW) {
    blink();
  }

  
  else if (digitalRead(BTN_PULSO) == LOW) {
    pulso();
  }

  
}


void colorearRGB(int red, int green, int blue) {
  LED_RGB.setPixelColor(0, (uint32_t(LED_RGB.Color(red, green, blue))));
  LED_RGB.show(); // Enciende el color
}


void sos() {
  // S
  corto();
  corto();
  corto();

  // O
  largo();
  largo();
  largo();

  // S
  corto();
  corto();
  corto();

  
}

void blink() {
  for(int i = 1; i <= 7; i++) {
    corto();
  }
}


void pulso() {
  for (int brillo = 0; brillo <= 255; brillo++) {
    analogWrite(LED_PIN, brillo);  // Salida PWM
    colorearRGB(random(0, 256), random(0, 256), random(0, 256));
    LED_RGB.setBrightness(brillo); 
    
    
    delay(10);
  }

  for (int brillo = 255; brillo >= 0; brillo--) {
    analogWrite(LED_PIN, brillo);
    colorearRGB(random(0, 256), random(0, 256), random(0, 256));
    LED_RGB.setBrightness(brillo); 
    
    delay(10);
  }

  colorearRGB(0,0,0); 
  LED_RGB.setBrightness(150);
  digitalWrite(LED_PIN, LOW);
}




void largo() {
  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
  delay(400);

  
  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  delay(100);
} 


void corto() {
  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
  delay(200);

  
  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  delay(100);
} 
