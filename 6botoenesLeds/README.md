## Práctica 4: Memorias 1 (Batalla Naval Binaria) 🕹️

---

## Introducción

Este proyecto implementa un sencillo **juego de memoria y adivinanza** para el microcontrolador **ESP32**, emulando la lógica de buscar un elemento oculto en una matriz lineal de 6 "espacios de memoria". El objetivo es que el usuario encuentre el único espacio de memoria que contiene un valor binario '1' (el **número secreto**), con un límite de **3 intentos**.

Se utiliza una **Barra de LEDs de 12 Segmentos** para compactar la visualización de los 6 espacios de memoria y los efectos de finalización.

---

## Plataforma y Requisitos

| Categoría | Detalle | Conexión (GPIO) |
| :--- | :--- | :--- |
| **Placa de Desarrollo** | **ESP32-WROOM-32** | N/A |
| **Lenguaje** | C/C++ (IDE de Arduino) | N/A |
| **Librería Requerida** | Funciones estándar (no se requieren librerías externas) | N/A |
| **Salida** | **Barra de LEDs de 12 Segmentos** (Se usan 6 pares/pines como indicadores) | 40, 39, 38, 37, 36, 35 |
| **Salida** | **1 LED** de Estado (`pin_led_show`) | 2 |
| **Salida** | **1 Zumbador** (Buzzer) para efectos de sonido | 21 |
| **Entrada** | **6 Botones Pulsadores** (Configuración `INPUT_PULLUP`) | 16, 15, 7, 4, 5, 6 |

> **Nota sobre la Visualización:** Los 6 pines de salida (`pin_led_1` a `pin_led_6`) controlan los 12 segmentos de la barra de LEDs, agrupando dos segmentos por pin, lo que permite visualizar los 6 espacios de memoria en un formato compacto.

---

### **Instalación y Carga del Código**

1.  **Abre el IDE de Arduino** y asegúrate de tener seleccionada la placa **ESP32** y el puerto **COM** correcto.
2.  **Copia y pega** el código proporcionado en el IDE.
3.  Haz clic en el botón **Subir** (Upload).

El sistema inicializará sus variables y el LED de estado (`pin_led_show`) se encenderá, indicando que el juego está activo y listo para la interacción.

---

## Patrón de Ejecución (Lógica del Juego)

El programa se estructura en torno al **bucle principal** (`loop()`) que gestiona los estados de juego, la lectura de los botones y la actualización visual.

### 1. Inicialización del Juego

Al inicio, las variables de estado se establecen en `false`, los intentos en **3**, y se genera el valor a encontrar:

* **Memoria Secreta:** `numSecreto = random(1, 7);` genera un número entero aleatorio entre 1 y 6, que corresponde al botón/par de segmentos LED que el usuario debe encontrar.
* **LED de Estado:** El LED `pin_led_show` (GPIO 2) permanece **HIGH** durante el juego, actuando como el indicador de "Juego Activo".

### 2. Detección y Lógica de Interacción

Todos los botones están configurados con **`INPUT_PULLUP`**, por lo que se activan al leer un estado **BAJO** (`LOW`).

Al presionar un botón, ocurre la siguiente secuencia:

* **Feedback de Sonido:** Se ejecuta la función `presionarBtn()` para emitir un pitido de confirmación con el **Buzzer**.
* **Feedback Visual:** El par de segmentos LED asociado al botón presionado se enciende por **1 segundo** (ej: `digitalWrite(pin_led_1, HIGH);`).
* **Consumo de Intento:** La variable `intentos` se reduce en 1.
* **Bloqueo de Memoria:** Se establece un *flag* booleano por botón (`fueClickeado_btn_X = true;`) para **ignorar futuras pulsaciones** de ese mismo botón, asegurando que el usuario solo pueda "consultar" cada espacio de memoria una vez por juego.
* **Verificación:** Se llama a la función `check(num)`, que compara el número del botón presionado con el `numSecreto`.

### 3. Estados de Finalización (`check()` y Efectos)

La función `check(num)` es el motor de la lógica de juego. Los efectos de victoria y derrota utilizan la barra de LEDs para crear un *feedback* dinámico:

| Estado Final | Función de Lógica | Visualización | Sonido |
| :--- | :--- | :--- | :--- |
| **Victoria** (`gano = true`) | `num == numSecreto` | **`finChido()`:** Los 6 pares de LEDs se encienden y apagan en secuencia rápida. | **`ganar()`:** Melodía ascendente y alegre. |
| **Derrota** (`perdio = true`) | `intentos == 0` | **`fin()`:** Todos los 6 pares de LEDs parpadean sincrónicamente. | **`perder()`:** Secuencia de tonos descendentes y graves. |

Una vez que el juego finaliza, la función **`restablecer()`** se ejecuta después de un breve retardo, limpiando todos los *flags*, reiniciando `intentos = 3`, y generando un nuevo `numSecreto`, dejando el sistema listo para la siguiente partida.



##  Demostración en Video

https://www.youtube.com/watch?v=bKW5_UoGtM0

## Conocimientos Adquiridos

1.  **Generación de Aleatoriedad:** Uso de la función `random()` para generar el dato secreto y asegurar la rejugabilidad.
2.  **Lógica de Juego por Estado:** Implementación de un sistema de estados simple mediante banderas booleanas (`gano`, `perdio`) para controlar el flujo del programa en el `loop()`.
3.  **Visualización Compacta de E/S:** Uso eficiente de una **Barra de LEDs de Múltiples Segmentos** (12 segmentos) para representar una matriz de 6 memorias, optimizando el número de pines utilizados.
4.  **Control de Interacciones Únicas:** Aplicación de **variables *flag* por botón** para imponer la regla de "un solo intento por memoria" en el juego.
5.  **Feedback Auditivo:** Programación de efectos de sonido específicos para cada estado del juego (presión, victoria, derrota) utilizando la función `tone()` con el Buzzer.