int ledPin = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);


  corto();
  corto();
  corto();
  largo();
  largo();
  largo();
  corto();
  corto();
  corto();


}



void largo() {
  digitalWrite(ledPin, HIGH);
  delay(700);

  
  digitalWrite(ledPin, LOW);
  delay(300);
} 


void corto() {
  digitalWrite(ledPin, HIGH);
  delay(300);

  
  digitalWrite(ledPin, LOW);
  delay(300);
} 
