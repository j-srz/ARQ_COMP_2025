# Plactica IRQ ( Interrupción ) 

## Introducción

Este proyecto es una evolución proyecto anterior, añadiendo una característica fundamental en sistemas embebidos: la **Interrupción (IRQ) por Software**.

El sistema utiliza **cuatro botones pulsadores** para seleccionar y activar diferentes patrones de luz, combinando el control de un **LED estándar (PWM)** con un **LED RGB direccionable (NeoPixel)**.

La nueva funcionalidad permite que cualquier secuencia de LED en ejecución (S.O.S., Blink o Pulso) sea **detenida de inmediato** al presionar un botón dedicado (`BTN_IRQ`), ejecutando una acción de emergencia y restableciendo el sistema al modo de espera. Esto se logra mediante una **bandera lógica** (`bandera`) que se verifica constantemente dentro de las rutinas de la secuencia.

---

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | ESP32-S3 |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Librería Requerida** | `Adafruit NeoPixel` |
| **Hardware** | LED estándar y Resistencia (Conectado a **GPIO 2**) |
| **Hardware** | 4 Botones Pulsadores de Modo (Conectados a **GPIO 4, 5, 6 y 7**) |


---

## Instalación y Carga del Código

1.  **Instala la librería:** Abre el **IDE de Arduino**, ve a **Programa** → **Incluir Librería** → **Administrar Librerías...** y busca e instala **"Adafruit NeoPixel"**.
2.  **Copia y pega** el código.
3.  **Selecciona la placa ESP32** y el puerto **COM** correspondiente.
4.  Haz clic en el botón **Subir** (Upload).

El sistema estará activo y esperando la pulsación de un botón para iniciar una secuencia o una interrupción.

---

## Patrón de Ejecución (Funciones y Modos)

El programa usa la configuración `INPUT_PULLUP` en todos los botones, por lo que la secuencia se activa al detectar un estado **BAJO** (`LOW`). **Todas las secuencias de modo (1-3) son ahora interrumpibles.**

### Funciones Base de las Señales

| Función | LED Estándar | NeoPixel | Interrupción |
| :--- | :--- | :--- | :--- |
| `corto()` (Punto) | ON por **200 ms** | Color **aleatorio** | Llama a `check()` antes de encender |
| `largo()` (Raya) | ON por **400 ms** | Color **aleatorio** | Llama a `check()` antes de encender |

### 1. Modo Señal S.O.S. (Botón `BTN_SOS` - GPIO 4)

Ejecuta la secuencia de socorro del Código Morse **S.O.S.** (`sos()`), que consiste en:
$$
\text{Corto} \cdot \text{Corto} \cdot \text{Corto} \quad \text{Largo} - \text{Largo} - \text{Largo} \quad \text{Corto} \cdot \text{Corto} \cdot \text{Corto}
$$

### 2. Modo 7 Blinks (Botón `BTN_BLINK` - GPIO 5)

Ejecuta la función `blink()`, que realiza **7 pulsos cortos** utilizando la cadencia de la función `corto()`.

### 3. Modo Efecto Pulso / Respiración (Botón `BTN_PULSO` - GPIO 6)

Ejecuta la función `pulso()`, que combina atenuación suave con un efecto de colores dinámicos:

* **LED Estándar:** Realiza un **Fade In/Out** (de 0 a 255 y viceversa) usando `analogWrite`.
* **LED RGB (NeoPixel):** Sincroniza su brillo (`setBrightness`) con la rampa de atenuación y cambia a un **color RGB aleatorio** (`random()`) al inicio de la función.
* **Control de Interrupción:** La función `check()` se llama en cada iteración del bucle `for`, permitiendo una **detención casi inmediata** si se pulsa el `BTN_IRQ`.

---

## 4. Modo Interrupción por Software (Botón `BTN_IRQ` - GPIO 7)

Este es el nuevo modo que prioriza la detención de cualquier secuencia en curso.

### Mecanismo de Interrupción

1.  **Activación:** El bucle de ejecución de las secuencias llama repetidamente a la función `check()`.
2.  **Función `check()`:** Detecta si el botón `BTN_IRQ` (GPIO 7) está en estado **LOW**. Si lo está, llama a `interrupcion()`.
3.  **Función `interrupcion()` (Rutina de Atención):**
    * **Señal de Emergencia:** El LED estándar se enciende al máximo (`255`) y el NeoPixel se ilumina de color **Rojo** (`255, 0, 0`).
    * La señal se mantiene por **2 segundos** (`delay(2000)`).
    * Ambos LEDs se apagan.
    * Se establece la **bandera lógica** global: `bandera = true;`.
4.  **Salida de Modo:** Una vez que `bandera` es `true`, las funciones de secuencia (`corto()`, `largo()`, `pulso()`) detectan esta condición y ejecutan un `return;` para salir inmediatamente de la función actual.
5.  **Reinicio:** El `loop()` principal **reinicia** la bandera (`bandera = false;`) antes de chequear los botones de modo, asegurando que el sistema pueda reanudar sus operaciones normales.

---

## Demostración en Video

[**[Link - Practica IRQ](https://youtu.be/4LPUQvKdGJU)**]

---

## Conocimientos Adquiridos

* **Manejo de Interrupciones por Software:** Implementación de un mecanismo de interrupción reactivo mediante un pin de entrada dedicado y una **bandera lógica** (`bandera`).
* **Control de Flujo Condicional:** Uso de la función auxiliar `check()` y la sentencia `return` dentro de las secuencias para forzar la **terminación anticipada** del modo activo.
* **Diseño de Sistemas Reactivos:** Creación de una rutina de atención (`interrupcion()`) para señalizar un evento crítico (LED Rojo) y luego restablecer las condiciones del sistema.
* **Sincronización de Salidas:** Coordinación del control de un LED estándar (PWM) y un LED RGB direccionable dentro de las mismas funciones de secuencia (`corto()`, `largo()`, `pulso()`).