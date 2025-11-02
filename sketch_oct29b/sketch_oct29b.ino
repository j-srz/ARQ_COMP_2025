// CONSTANTES
int LED_PIN = 2; 
int BTN_SOS = 4;
int BTN_BLINK = 5;
int BTN_PULSO = 6;
int BTN_IRQ = 7;

// Variable 'volatile' para comunicar la interrupción con el loop principal.
// The 'volatile' keyword ensures the compiler doesn't optimize away its checks.
volatile bool irq_flag = false;

// The 'IRAM_ATTR' attribute is only necessary for ESP-series microcontrollers.
// I'll keep it for robustness if you are using an ESP32.
void IRAM_ATTR interrupcion() {
    // Just set the flag to true. Avoid complex code, delays, or I/O in an ISR.
    irq_flag = true; 
}


void setup() {
    pinMode(LED_PIN, OUTPUT);
    
    // INPUT_PULLUP is correct for buttons wired to GND.
    pinMode(BTN_SOS, INPUT_PULLUP);
    pinMode(BTN_BLINK, INPUT_PULLUP);
    pinMode(BTN_PULSO, INPUT_PULLUP);
    pinMode(BTN_IRQ, INPUT_PULLUP);

    // Attach interrupt: RISING (LOW to HIGH) or FALLING (HIGH to LOW).
    // With INPUT_PULLUP, the pin is HIGH normally. 
    // Pressing the button pulls it LOW. Releasing makes it HIGH.
    // I'll use FALLING to detect the *press* (HIGH to LOW).
    attachInterrupt(digitalPinToInterrupt(BTN_IRQ), interrupcion, FALLING);
}


void loop() {
    // 1. Handle the Interrupt
    if (irq_flag) {
        // Debouncing: The delay() will be handled inside a dedicated function 
        // to prevent the main loop from blocking, but for simplicity we'll 
        // keep it simple here.
        
        // This is a simple toggle function for the IRQ button:
        static bool led_state = false; // State persistence
        led_state = !led_state;        // Toggle the state
        digitalWrite(LED_PIN, led_state); // Apply the new state
        
        // Clear the flag to wait for the next interrupt
        irq_flag = false; 
        
        // Add a small delay for debouncing the mechanical button (optional but good practice)
        delay(50);
    }
    
    // 2. Handle the Polled Buttons
    // Check buttons, and use a small delay for debouncing after calling the function.
    if (digitalRead(BTN_SOS) == LOW) {
        sos();
        delay(200); // Debounce delay
    }
    else if (digitalRead(BTN_BLINK) == LOW) {
        blink();
        delay(200); // Debounce delay
    }
    else if (digitalRead(BTN_PULSO) == LOW) {
        pulso();
        delay(200); // Debounce delay
    }
}


// --- LED Pattern Functions ---

void sos() {
    // S (Short)
    corto(); corto(); corto();
    delay(500); // Pause between letters

    // O (Long)
    largo(); largo(); largo();
    delay(500); // Pause between letters

    // S (Short)
    corto(); corto(); corto();
    delay(1000); // Longer pause after the whole message
}

void blink() {
    for(int i = 1; i <= 7; i++) {
        corto();
    }
}

void pulso() {
    // Fade in
    for (int brillo = 0; brillo <= 255; brillo++) {
        analogWrite(LED_PIN, brillo); // PWM output
        delay(10);
    }

    // Fade out
    for (int brillo = 255; brillo >= 0; brillo--) {
        analogWrite(LED_PIN, brillo);
        delay(10);
    }

    // Ensure the LED is completely off after the pulse effect
    analogWrite(LED_PIN, 0); // Use analogWrite(0) instead of digitalWrite(LOW) for consistency
}


// --- Morse Code Element Functions ---

// Note: Using digitalWrite for ON/OFF will be faster/simpler if you don't care about PWM
void largo() {
    digitalWrite(LED_PIN, HIGH);
    delay(400); // Long duration
    
    digitalWrite(LED_PIN, LOW);
    delay(100); // Inter-element pause
}

void corto() {
    digitalWrite(LED_PIN, HIGH);
    delay(200); // Short duration
    
    digitalWrite(LED_PIN, LOW);
    delay(100); // Inter-element pause
}
