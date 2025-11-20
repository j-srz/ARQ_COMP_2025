#include <Adafruit_NeoPixel.h> 

Adafruit_NeoPixel LED_RGB(1, 48, NEO_GRBW + NEO_KHZ800); 

const int LED_PIN = 2;
const int BTN_SOS = 4;
const int BTN_BLINK = 5;
const int BTN_PULSO = 6;
const int BTN_IRQ = 7; 

const int ACCION_NINGUNA = 0;
const int ACCION_SOS = 1;
const int ACCION_BLINK = 2;
const int ACCION_PULSO = 3;

int pasoSOS = 0;
int pasoBlink = 0;
int pasoPulso = 0;

bool bandera = false;
int proximaAccion = ACCION_NINGUNA;

void setup() {
  LED_RGB.begin();
  LED_RGB.setBrightness(150); 
  colorearRGB(0,0,0);
   
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_SOS, INPUT_PULLUP);
  pinMode(BTN_BLINK, INPUT_PULLUP);
  pinMode(BTN_PULSO, INPUT_PULLUP);
  pinMode(BTN_IRQ, INPUT_PULLUP);
}

void loop() {
  if (proximaAccion != ACCION_NINGUNA) {
     int accionAEjecutar = proximaAccion;
     proximaAccion = ACCION_NINGUNA;
     
     bandera = false;
     
     if (accionAEjecutar == ACCION_SOS) sos();
     else if (accionAEjecutar == ACCION_BLINK) blink();
     else if (accionAEjecutar == ACCION_PULSO) pulso();
  }

  bandera = false; 

  if (digitalRead(BTN_SOS) == LOW) {
    sos();
    delay(200); 
  }
  else if (digitalRead(BTN_BLINK) == LOW) {
    blink();
    delay(200);
  }
  else if (digitalRead(BTN_PULSO) == LOW) {
    pulso();
    delay(200);
  }
   
  if (bandera == false && proximaAccion == ACCION_NINGUNA) {
    analogWrite(LED_PIN, 0);
    colorearRGB(0,0,0);
  }
}

void colorearRGB(int red, int green, int blue) {
  LED_RGB.setPixelColor(0, (uint32_t(LED_RGB.Color(red, green, blue))));
  LED_RGB.show(); 
}

void esperar_y_checar(int tiempo) {
  for (int i = 0; i < tiempo; i++) {
    
    if (digitalRead(BTN_IRQ) == LOW) {
       interrupcion();
       if (proximaAccion != ACCION_NINGUNA) {
          bandera = true;
          return; 
       }
    }

    if (digitalRead(BTN_SOS) == LOW) {
       proximaAccion = ACCION_SOS;
       bandera = true;
       return;
    }
    if (digitalRead(BTN_BLINK) == LOW) {
       proximaAccion = ACCION_BLINK;
       bandera = true;
       return;
    }
    if (digitalRead(BTN_PULSO) == LOW) {
       proximaAccion = ACCION_PULSO;
       bandera = true;
       return;
    }

    delay(1);
  }
}

void sos() {
  corto(); if(bandera) return; 
  pasoSOS += 1;
  corto(); if(bandera) return;
  pasoSOS += 1;
  corto(); if(bandera) return;
  pasoSOS += 1;

  largo(); if(bandera) return;
  pasoSOS += 1;
  largo(); if(bandera) return;
  pasoSOS += 1;
  largo(); if(bandera) return;
  pasoSOS += 1;

  corto(); if(bandera) return;
  pasoSOS += 1;
  corto(); if(bandera) return;
  pasoSOS += 1;
  corto(); if(bandera) return;
  pasoSOS = 0;
}

void blink() {
  for(int i = 1; i <= 7; i++) {
    pasoBlink += 1;
    if(bandera) return; 
    corto();
  }
  pasoBlink = 0;
}

void pulso() {
  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  for (int brillo = 0; brillo <= 255; brillo++) {
    if(bandera) return;

    pasoPulso += 1;
    analogWrite(LED_PIN, brillo); 
    LED_RGB.setBrightness(brillo); 
    colorearRGB(r, g, b);
    
    esperar_y_checar(10); 
  }

  for (int brillo = 255; brillo >= 0; brillo--) {
    if(bandera) return;

    pasoPulso += 1;
    analogWrite(LED_PIN, brillo);
    LED_RGB.setBrightness(brillo); 
    colorearRGB(r, g, b);
    
    esperar_y_checar(10);
  }

  colorearRGB(0,0,0); 
  LED_RGB.setBrightness(150);
  digitalWrite(LED_PIN, LOW);
  pasoPulso = 0;
}

void largo() {
  if (bandera) return;
  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
   
  esperar_y_checar(400); 
  if (bandera) return;

  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  esperar_y_checar(100);
} 

void corto() {
  if (bandera) return;
  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
   
  esperar_y_checar(200);
  if (bandera) return;

  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  esperar_y_checar(100);
} 

void interrupcion() {
  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  delay(200); 

  while (digitalRead(BTN_IRQ) == HIGH) {
    
    if (digitalRead(BTN_SOS) == LOW) {
      proximaAccion = ACCION_SOS;
      break;
    }
    if (digitalRead(BTN_BLINK) == LOW) {
      proximaAccion = ACCION_BLINK;
      break; 
    }
    if (digitalRead(BTN_PULSO) == LOW) {
      proximaAccion = ACCION_PULSO;
      break; 
    }
    
    delay(10); 
  }
   
  delay(200); 
}
