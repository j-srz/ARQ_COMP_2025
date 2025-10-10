// Pin de salida del led (interno del ESP-32 y de la salida)
int ledPin = 2;


void setup() {
  // put your setup code here, to run once:

  // Definimos el pin como salida
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);

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


// Funcion para hacer un pulso largo de 700ms con una pausa de 300ms
void largo() {
  digitalWrite(ledPin, HIGH);
  delay(700);

  
  digitalWrite(ledPin, LOW);
  delay(300);
} 

// Funcion para hacer un pulso corto de 300ms con una pausa de 300ms
void corto() {
  digitalWrite(ledPin, HIGH);
  delay(300);

  
  digitalWrite(ledPin, LOW);
  delay(300);
} 
