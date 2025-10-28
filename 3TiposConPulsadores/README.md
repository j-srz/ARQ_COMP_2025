# Controlador LED Multi-Modo: Morse, Blink y Efecto Pulso con NeoPixel 🚥

---

## Introducción

Este proyecto implementa un sistema interactivo de iluminación multi-modo para el microcontrolador **ESP32**. El sistema utiliza **tres botones pulsadores** para seleccionar y activar diferentes patrones de luz, combinando:

1.  Control de un **LED estándar** mediante **PWM** (`analogWrite`).
2.  Control de un **LED RGB direccionable** (NeoPixel) que se ilumina con colores aleatorios en sincronía con los patrones.

---

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | **ESP32-WROOM-32** |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Librería Requerida** | **Adafruit NeoPixel** |
| **Hardware** | LED estándar y Resistencia (Conectado a **GPIO 2**) |
| **Hardware** | LED RGB Direccionable (NeoPixel, Conectado a **GPIO 48**) |
| **Hardware** | 3 Botones Pulsadores (Conectados a **GPIO 4, 5 y 6**) |

---

### **Instalación y Carga del Código**

1.  **Instala la librería:** Abre el **IDE de Arduino**, ve a **Programa** $\rightarrow$ **Incluir Librería** $\rightarrow$ **Administrar Librerías...** y busca e instala **"Adafruit NeoPixel"**.
2.  **Copia y pega** el código.
3.  **Selecciona la placa ESP32** y el puerto **COM** correspondiente.
4.  Haz clic en el botón **Subir** (Upload).

El sistema estará activo y esperando la pulsación de un botón para iniciar una secuencia.

---

## Patrón de Ejecución (Funciones y Modos)

El programa usa la configuración **INPUT\_PULLUP** en los botones, por lo que la secuencia se activa al detectar un estado **BAJO** (`LOW`).

### 1. Modo Señal S.O.S. (Botón `BTN_SOS` - GPIO 4)

Ejecuta la secuencia de socorro del Código Morse **S.O.S.** (`sos()`).

| Función | LED Estándar | NeoPixel |
| :--- | :--- | :--- |
| `corto()` (Punto) | ON por $200\ \text{ms}$ | Color **aleatorio** |
| `largo()` (Raya) | ON por $400\ \text{ms}$ | Color **aleatorio** |

### 2. Modo 7 Blinks (Botón `BTN_BLINK` - GPIO 5)

Ejecuta `blink()`, que realiza **7 pulsos cortos** utilizando la cadencia de la función `corto()`.

### 3. Modo Efecto Pulso / Respiración (Botón `BTN_PULSO` - GPIO 6)

Ejecuta la función `pulso()`, que combina atenuación suave con un efecto de colores dinámicos.

* **LED Estándar:** Realiza un **Fade In/Out** (de 0 a 255 y viceversa) usando `analogWrite`.
* **LED RGB (NeoPixel):** En cada paso del `Fade In/Out`, el NeoPixel cambia a un **color RGB aleatorio** (`random()`) y su brillo se sincroniza con la rampa de atenuación.
* **Finalización:** Ambos LEDs se apagan.

---

## Demostración en Video

https://youtu.be/g8koNzcYzyk

---

## Conocimientos Adquiridos

1.  **Control de Entradas con Pull-up:** Uso de `INPUT_PULLUP` para detectar botones de forma eficiente.
2.  **Manejo de NeoPixel:** Uso avanzado de la librería **Adafruit NeoPixel** para controlar el color (`colorearRGB`) y el brillo dinámicamente.
3.  **Generación Aleatoria:** Aplicación de la función `random()` para crear efectos visuales vibrantes y cambiantes en los colores del NeoPixel.
4.  **Sincronización de Salidas:** Coordinación del control de un LED estándar (PWM) y un LED RGB direccionable dentro de las mismas funciones de secuencia (`corto()`, `largo()`, `pulso()`).
5.  **Estructura de Control por Hardware:** Implementación de un menú de selección robusto usando la estructura `if-else if` en el `loop()`.