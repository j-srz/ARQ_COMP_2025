
#include <Adafruit_NeoPixel.h> 

Adafruit_NeoPixel LED_RGB(1, 48, NEO_GRBW + NEO_KHZ800); 

// CONSTANTES
int LED_PIN = 2;
int BTN_SOS = 4;
int BTN_BLINK = 5;
int BTN_PULSO = 6;

int BTN_IRQ = 7;


bool bandera = false;








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

  int r = random(0, 256);
  int g = random(0, 256);
  int b = random(0, 256);

  
  
  for (int brillo = 0; brillo <= 255; brillo++) {

    check();
    if (bandera) {

      return;
    }

    
    analogWrite(LED_PIN, brillo);  // Salida PWM
    
    LED_RGB.setBrightness(brillo); 
    colorearRGB(r, g, b);
    LED_RGB.show();
    
    delay(10);
  }

  for (int brillo = 255; brillo >= 0; brillo--) {

    check();
    if (bandera) {

      return;
    }

    
    analogWrite(LED_PIN, brillo);

    LED_RGB.setBrightness(brillo); 
    colorearRGB(r, g, b);
    LED_RGB.show();
    
    delay(10);
  }

  colorearRGB(0,0,0); 
  LED_RGB.setBrightness(150);
  digitalWrite(LED_PIN, LOW);
}




void largo() {

  check();
  if (bandera) {

    return;
  }

  
  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
  delay(400);

  check();
  if (bandera) {

    return;
  }

  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  delay(100);
} 


void corto() {

  check();
  if (bandera) {

    return;
  }

  analogWrite(LED_PIN, 255);
  colorearRGB(random(0, 256), random(0, 256), random(0, 256));
  delay(200);

  check();
  if (bandera) {

    return;
  }

  
  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);
  delay(100);


  
} 


void interrupcion() {
  
  analogWrite(LED_PIN, 255);
  colorearRGB(255, 0, 0);

  delay(2000);

  analogWrite(LED_PIN, 0);
  colorearRGB(0, 0, 0);

  bandera = true;




  

}

void check() {
  if (digitalRead(BTN_IRQ) == LOW) {
    interrupcion();
  }
}
