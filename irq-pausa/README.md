# IRQ+Memoria

## Introducción

Este proyecto implementa un sistema de control de iluminación LED (RGB NeoPixel y LED estándar) basado en una lógica de **multitarea cooperativa simulada**. El objetivo principal es resolver el problema clásico de los "tiempos de espera bloqueantes" (como `delay()`), permitiendo que el microcontrolador siga respondiendo a las entradas del usuario mientras ejecuta animaciones complejas.

El sistema cuenta con capacidades de **Interrupción (IRQ)** para pausar el sistema y **Memoria de Acción**, lo que permite al usuario pre-seleccionar la siguiente animación mientras la actual sigue ejecutándose o mientras el sistema está pausado.

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | ESP32-S3-WROOM-32 (Compatible con Arduino/ESP8266) |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Librería Requerida** | `Adafruit_NeoPixel` |
| **Hardware (Salidas)** | 1x LED RGB NeoPixel (Pin 48), 1x LED Estándar (Pin 2) + Resistencia (220-330Ω) |
| **Hardware (Entradas)** | 4x Pulsadores (Configuración Pull-up interna) |

## Carga del Código

1. **Instalar Librerías:** Asegúrate de tener instalada la librería `Adafruit_NeoPixel` desde el Gestor de Librerías del IDE de Arduino.
2. **Configuración de Hardware:** Conecta los pulsadores a los pines definidos:
    * `BTN_SOS` (Pin 4)
    * `BTN_BLINK` (Pin 5)
    * `BTN_PULSO` (Pin 6)
    * `BTN_IRQ` (Pin 7 - Pausa)
3. **Selección de Placa:** En el IDE, selecciona tu placa ESP32-S3.
4. **Subida:** Compila y sube el código.

## Patrón de Ejecución

El código está estructurado para evitar bloqueos totales mediante el uso de funciones personalizadas de tiempo y banderas de estado. A continuación se detalla el funcionamiento de cada componente:

### 1. Variables de Estado (`bandera` y `proximaAccion`)
Son el núcleo lógico del programa:
* **`bandera` (bool):** Actúa como una señal de aborto. Si se vuelve `true`, indica a la animación actual que debe detenerse inmediatamente para dar paso a una nueva orden.
* **`proximaAccion` (int):** Funciona como una memoria buffer. Si el usuario presiona un botón mientras el LED está ocupado, esa orden se guarda aquí para ejecutarse apenas termine (o se cancele) la tarea actual.

### 2. Función `esperar_y_checar(int tiempo)`
Esta función reemplaza al `delay()` tradicional. En lugar de congelar el procesador, ejecuta un ciclo milisegundo a milisegundo que:
* **Verifica Pausa (IRQ):** Si se presiona `BTN_IRQ`, entra en un bucle de pausa (`interrupcion()`) hasta que se libere el botón.
* **Verifica Cambio de Animación:** Si se presiona un botón de acción (SOS, Blink, Pulso), actualiza `proximaAccion`, activa la `bandera` de aborto y termina la espera inmediatamente.

### 3. El `loop()` Principal
El ciclo principal opera en dos fases:
* **Gestor de Acciones Pendientes:** Primero revisa si `proximaAccion` tiene algo guardado. Si es así, ejecuta esa función inmediatamente.
* **Lectura de Reposo:** Si no hay acciones pendientes ni animaciones corriendo, lee los botones físicamente. Si se detecta una pulsación, inicia la animación correspondiente.

### 4. Las Animaciones (`sos`, `blink`, `pulso`)
Cada función de animación está diseñada para ser interrumpible:
* Realizan pasos pequeños (encender, esperar, apagar).
* Después de cada paso crítico, verifican `if(bandera) return;`. Si la bandera está activa (porque `esperar_y_checar` detectó un botón), la función termina prematuramente para devolver el control al `loop()`.

### 5. Función `interrupcion()`
Maneja el estado de pausa:
* Apaga los LEDs para indicar el estado de "suspendido".
* Mantiene al procesador en un bucle `while` mientras el botón de pausa esté presionado.
* **Característica Clave:** Permite "pre-cargar" una acción. Si durante la pausa presionas un botón de animación, el sistema rompe la pausa y agenda esa acción en `proximaAccion`.

## Demostración en Video

[**[Link - Practica IRQ+Memoria](https://youtu.be/cd6YpJSOqsg)**]

## Conocimientos Adquiridos

Al desarrollar e implementar este código, se han aplicado y reforzado los siguientes conceptos de programación embebida:

1. **Programación No Bloqueante:** Sustitución de retardos fijos por bucles de comprobación activa para mejorar la respuesta del sistema (Responsiveness).
2. **Máquinas de Estado Finitas (FSM):** Gestión de estados del sistema (Reposo, Ejecutando, Pausado, Transición) mediante variables de control.
3. **Manejo de Banderas (Flags):** Uso de variables booleanas para comunicar eventos entre diferentes niveles de la jerarquía del código (desde la función de espera hacia la lógica principal).
4. **Interrupciones por Software:** Simulación de interrupciones mediante *polling* rápido para priorizar acciones críticas (como el botón de pausa).
5. **Control de Hardware Mixto:** Sincronización de LEDs estándar (PWM/Digital) con LEDs direccionables (Protocolo NeoPixel).