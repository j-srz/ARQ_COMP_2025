# Práctica: Memoria Bidimensional (Juego del Gato / Tic-Tac-Toe)

## Instituto Tecnológico de Aguascalientes (ITA)
### Materia: Arquitectura de Computadoras
#### Equipo:
* **García Castorena José Guadalupe**
* **Suárez Licea Jesús**

---

## Introducción

Este proyecto implementa el clásico juego de **Gato (Tic-Tac-Toe)** utilizando un microcontrolador **ESP32**. El objetivo principal es demostrar el manejo de **arreglos bidimensionales** para gestionar la memoria de estado del juego y la resolución de problemas de hardware mediante lógica de software.

El sistema enfrenta al usuario (que juega como 'O') contra la computadora (que juega como 'X'). La interfaz se compone de una **Matriz de LEDs 8x8** para la visualización gráfica del tablero y las animaciones, y un **Teclado Matricial 4x4** para la entrada de coordenadas. Debido a una falla física en la tercera fila del teclado, se implementó un algoritmo de mapeo personalizado que permite jugar correctamente reasignando las teclas funcionales.

---

## Plataforma y Requisitos

| Categoría | Detalle | Conexión (GPIO ESP32) |
| :--- | :--- | :--- |
| **Placa de Desarrollo** | **ESP32-S3 / C3** (SuperMini) | N/A |
| **Lenguaje** | C/C++ (IDE de Arduino) | N/A |
| **Salida Visual** | **Matriz LED 8x8** (Driver MAX7219) | **DIN:** 12, **CLK:** 11, **CS:** 10 |
| **Salida Auditiva** | **Zumbador Pasivo** (Buzzer) | 41 |
| **Entrada** | **Teclado Matricial 4x4** (Modo Adaptado) | **Filas:** 18, 19, 21 (Fila 3 omitida)<br>**Columnas:** 1, 2, 3, 4 |

> **Nota de Hardware:** Se utiliza un teclado físico de 4x4. Sin embargo, la **Fila 3 no es funcional**. Por software, se ignoró esa fila y se remapearon las teclas de la Fila 4 para completar las 9 casillas necesarias y asignar la función de *Reset* a la tecla 'D'.

---

## Patrón de Ejecución (Lógica del Juego)

El núcleo del programa es una matriz de enteros de 3x3 (`int juego[3][3]`) que actúa como la memoria del sistema:
* `0`: Casilla Vacía.
* `1`: Casilla ocupada por CPU ('X').
* `2`: Casilla ocupada por Jugador ('O').

### Secuencia de Turnos
1.  **Inicio:** El tablero inicia vacío. El usuario siempre tiene el primer turno ('O').
2.  **Entrada Usuario:** El usuario presiona una tecla. El sistema valida si corresponde a una coordenada vacía en la memoria `3x3`. Si es válida, guarda el dato, emite un sonido y actualiza la matriz LED.
3.  **Verificación:** Inmediatamente se barre la memoria para ver si el usuario ganó.
4.  **Turno CPU:** La computadora escanea la memoria, lista los espacios vacíos (`0`) y selecciona uno al azar para colocar su 'X'.
5.  **Verificación Final:** Se barre nuevamente la memoria para ver si la CPU ganó o si hay empate (tablero lleno).

---

## Descripción de Funciones del Código

A continuación se detalla la funcionalidad de cada bloque lógico programado:

### 1. Funciones de Control Principal
* **`setup()`**: Inicializa la comunicación con el driver MAX7219 (Matriz LED), configura el pin del Buzzer como salida, inicializa la semilla para números aleatorios (`randomSeed`) y llama a `resetGame()` para comenzar limpio.
* **`loop()`**: Es la máquina de estados del juego.
    * Escucha el teclado constantemente.
    * Si detecta la tecla 'D', reinicia el juego.
    * Si es turno del jugador, espera una tecla válida, actualiza la memoria y pasa el turno.
    * Si es turno de la CPU, llama a la IA y verifica resultados inmediatamente.

### 2. Funciones de Lógica de Juego
* **`keyToCellIndex(char key)`**: **Función Crítica de Adaptación**. Resuelve el problema del hardware traduciendo el carácter de la tecla a un índice lineal (0-8).
    * Mapea `1-6` a las primeras dos filas del juego.
    * Omite la fila física 3 defectuosa.
    * Mapea `*`, `0`, `#` de la fila 4 a la tercera fila del juego virtual.
* **`computerMove()`**: Implementa la "Inteligencia Artificial".
    * Recorre la matriz `juego[3][3]`.
    * Almacena las coordenadas de todas las celdas vacías en un arreglo temporal.
    * Selecciona una coordenada aleatoria de ese arreglo y marca un `1` (CPU).
* **`verificarGanador()`**: Realiza un barrido completo de la memoria bidimensional buscando "tres en línea" (horizontal, vertical o diagonal) de un mismo valor no nulo.
* **`verificarEmpate()`**: Se ejecuta si no hay ganador. Verifica si queda algún `0` en la memoria. Si no hay ceros, declara empate.
* **`resetGame()`**: Limpia la memoria (llena la matriz `juego` con ceros), reinicia la variable de turno al jugador y redibuja la cuadrícula limpia en los LEDs.

### 3. Funciones de Visualización y Audio
* **`mostrarJuego()`**: Traduce el estado lógico de la memoria `juego[3][3]` a píxeles físicos. Recorre la matriz y llama a `dibujarX` o `dibujarO` según corresponda.
* **`dibujarX` / `dibujarO`**: Algoritmos de dibujo que encienden los LEDs específicos en coordenadas relativas (multiplican la coordenada lógica por 3 para posicionarse en la matriz de 8x8 píxeles).
* **`mostrarResultado(int resultado)`**: Se activa al finalizar la partida. Limpia la pantalla y dibuja un *bitmap* de **Carita Feliz** (Gana Jugador), **Carita Triste** (Gana CPU) o **Patrón Lleno** (Empate).
* **`beep()`, `playWinSound()`, `playLoseSound()`**: Generan retroalimentación auditiva inmediata usando frecuencias (`tone`) y duraciones específicas para indicar pulsación, victoria, derrota o empate.

---

##  Demostración en Video

https://youtu.be/f9eVS5_4RmY



## Conocimientos Adquiridos

1.  **Adaptación Hardware-Software:** Se aprendió a solucionar fallas físicas (fila dañada del teclado) mediante lógica de programación, reasignando funciones a teclas disponibles sin comprometer la usabilidad.
2.  **Manejo de Arreglos Bidimensionales:** Implementación de una matriz de 3x3 para modelar la lógica abstracta del juego separada de la representación física.
3.  **Lógica de Inteligencia Artificial Estocástica:** Creación de un algoritmo no determinista que permite a la máquina jugar de forma impredecible seleccionando espacios vacíos.
4.  **Interfaz Multimedia:** Coordinación sincronizada de entrada (Teclado), salida visual (Matriz LED con driver MAX7219) y salida de audio (Buzzer) en tiempo real.
5.  **Validación de Datos:** Implementación de candados lógicos para asegurar la integridad de la memoria del juego (evitar sobrescritura de jugadas previas).