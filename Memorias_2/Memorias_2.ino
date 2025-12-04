#include <Keypad.h>
#include "LedControl.h"
#include <Arduino.h>

const int BUZZER_PIN = 41; 

const byte FILAS = 3; 
const byte COLUMNAS = 4;

char teclas [FILAS] [COLUMNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'*', '0', '#', 'D'}
};

byte Pinesfila [FILAS] = { 18, 19, 21 }; 

byte Pinescol [COLUMNAS] = { 1, 2, 3, 4 }; 

Keypad keypad = Keypad (makeKeymap(teclas), Pinesfila, Pinescol, FILAS, COLUMNAS);

LedControl lc = LedControl(12, 11, 10, 1);

int juego[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
};

bool esTurnoJugador = true;

const byte happyFace[8] = {0x00, 0x00, 0x24, 0x00, 0x42, 0x3C, 0x00, 0x00}; 
const byte sadFace[8] = {0x00, 0x00, 0x24, 0x00, 0x3C, 0x42, 0x00, 0x00}; 
const byte drawFace[8] = {0x00, 0x00, 0x24, 0x00, 0x00, 0x3C, 0x00, 0x00}; 

void dibujarX(int fila, int columna);
void dibujarO(int fila, int columna);
void mostrarJuego();
int verificarGanador();
bool verificarEmpate();
void mostrarResultado(int resultado);
int keyToCellIndex(char key);
void computerMove();
void resetGame();
void beep();
void playWinSound();
void playLoseSound();
void playDrawSound();


void beep() {
    tone(BUZZER_PIN, 1000, 50); 
}

void playWinSound() {
    tone(BUZZER_PIN, 523, 100); delay(100); 
    tone(BUZZER_PIN, 659, 100); delay(100); 
    tone(BUZZER_PIN, 784, 200); delay(200); 
    noTone(BUZZER_PIN);
}

void playLoseSound() {
    tone(BUZZER_PIN, 392, 200); delay(200); 
    tone(BUZZER_PIN, 330, 200); delay(200); 
    tone(BUZZER_PIN, 262, 400); delay(400); 
    noTone(BUZZER_PIN);
}

void playDrawSound() {
    tone(BUZZER_PIN, 440, 100); delay(100); 
    noTone(BUZZER_PIN);
    delay(50);
    tone(BUZZER_PIN, 440, 100); delay(100); 
    noTone(BUZZER_PIN);
}


void setup() {
    
    pinMode(BUZZER_PIN, OUTPUT); 

    lc.shutdown(0, false); 
    lc.setIntensity(0, 15); 
    
    randomSeed(analogRead(0)); 
    
    resetGame();
}


void loop() {
    char key = keypad.getKey();

    if (key) {
        if (key == 'D') {
            beep(); 
            resetGame();
            return; 
        }

        if (esTurnoJugador) {
            int cellIndex = keyToCellIndex(key);
            
            if (cellIndex != -1) {
                int r = cellIndex / 3; 
                int c = cellIndex % 3; 

                if (juego[r][c] == 0) {
                    juego[r][c] = 2; 
                    beep(); 
                    
                    mostrarJuego();
                    esTurnoJugador = false; 
                }
            }
        }
    }
    
    if (!esTurnoJugador) {
        int ganador = verificarGanador();
        bool empate = verificarEmpate();

        if (ganador != 0 || empate) {
            mostrarResultado(ganador); 
            
            delay(5000); 
            
            resetGame(); 
        } else {
            
            computerMove(); 
            mostrarJuego();

            ganador = verificarGanador();
            empate = verificarEmpate();

            if (ganador != 0 || empate) {
                mostrarResultado(ganador);
                delay(5000);
                resetGame(); 
            } else {
                esTurnoJugador = true;
            }
        }
    }
}


void resetGame() {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            juego[r][c] = 0;
        }
    }
    esTurnoJugador = true; 
    mostrarJuego();
    
    lc.clearDisplay(0);
    lc.setRow(0, 2, B11111111);
    lc.setRow(0, 5, B11111111);
    lc.setColumn(0, 2, B11111111);
    lc.setColumn(0, 5, B11111111);
}

int keyToCellIndex(char key) {
    switch (key) {
        case '1': return 0; 
        case '2': return 1; 
        case '3': return 2; 
        case '4': return 3; 
        case '5': return 4; 
        case '6': return 5; 
        case '*': return 6; 
        case '0': return 7; 
        case '#': return 8; 
        default: return -1; 
    }
}

void computerMove() {
    int vacios[9][2]; 
    int count = 0;
    
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (juego[r][c] == 0) {
                vacios[count][0] = r;
                vacios[count][1] = c;
                count++;
            }
        }
    }

    if (count > 0) {
        int index = random(count);
        int r = vacios[index][0];
        int c = vacios[index][1];
        
        juego[r][c] = 1; 
        
    }
}


int verificarGanador() {
    for (int i = 0; i < 3; i++) {
        if (juego[i][0] == juego[i][1] && juego[i][1] == juego[i][2] && juego[i][0] != 0) {
            return juego[i][0];
        }
        if (juego[0][i] == juego[1][i] && juego[1][i] == juego[2][i] && juego[0][i] != 0) {
            return juego[0][i];
        }
    }

    if (juego[0][0] == juego[1][1] && juego[1][1] == juego[2][2] && juego[0][0] != 0) {
        return juego[0][0];
    }
    if (juego[0][2] == juego[1][1] && juego[1][1] == juego[2][0] && juego[0][2] != 0) {
        return juego[0][2];
    }

    return 0; 
}

bool verificarEmpate() {
    if (verificarGanador() != 0) return false; 

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (juego[r][c] == 0) {
                return false; 
            }
        }
    }
    return true; 
}

void mostrarResultado(int resultado) {
    lc.clearDisplay(0);
    
    if (resultado == 2) { 
        playWinSound(); 
        for (int fila = 0; fila < 8; fila++) {
            lc.setRow(0, fila, happyFace[fila]);
        }
    } else if (resultado == 1) { 
        playLoseSound(); 
        for (int fila = 0; fila < 8; fila++) {
            lc.setRow(0, fila, sadFace[fila]);
        }
    } else { 
        playDrawSound(); 
        for(int i=0; i<8; i++) lc.setRow(0, i, B11111111);
    }
}

void dibujarX(int fila, int columna) {
    int start_row = fila * 3;
    int start_col = columna * 3;
    lc.setLed(0, start_row, start_col, true);
    lc.setLed(0, start_row + 1, start_col + 1, true);
}

void dibujarO(int fila, int columna) {
    int start_row = fila * 3;
    int start_col = columna * 3;
    lc.setLed(0, start_row, start_col, true);
    lc.setLed(0, start_row, start_col + 1, true);
    lc.setLed(0, start_row + 1, start_col, true);
    lc.setLed(0, start_row + 1, start_col + 1, true);
}

void mostrarJuego() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (r != 2 && r != 5 && c != 2 && c != 5) {
                lc.setLed(0, r, c, false);
            }
        }
    }

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (juego[r][c] == 1) { 
                dibujarX(r, c);
            } else if (juego[r][c] == 2) { 
                dibujarO(r, c);
            }
        }
    }
}
