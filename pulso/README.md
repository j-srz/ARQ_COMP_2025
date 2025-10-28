# Efecto de Pulso

---

## Introducción

Este proyecto implementa un **pulso** utilizando la modulación por ancho de pulso (**PWM**) a través de la función `analogWrite` en un LED conectado a un microcontrolador **ESP32**. La ejecución sigue un patrón cíclico de encendido gradual (fade in) y apagado gradual (fade out).

---

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | **ESP32-S3-WROOM-32** |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Hardware** (Opcional) | LED y Resistencia (220 a 330 $\Omega$) |

---

### **Carga del Código**

1. **Copia y pega** el código en el **IDE de Arduino**.
2. Selecciona la placa **ESP32** y el puerto **COM** correspondiente en el menú **Herramientas**.
3. Haz clic en el botón **Subir** (Upload).

Una vez subido, el ESP32 iniciará la secuencia automáticamente.

---

## Patrón de Ejecución

El programa espera **5 segundos** (`delay(5000);`) al inicio de cada ciclo.
Luego, ejecuta la función `pulso()`, que realiza la transición de brillo completa (Fade In y Fade Out).
El ciclo se repite indefinidamente.

* `pulso()`: Realiza el **encendido y apagado suave** del LED usando PWM.
    * **Encendido (Fade In):** El brillo (`brillo`) se incrementa de 0 a 255.
    * **Apagado (Fade Out):** El brillo (`brillo`) se reduce de 255 a 0. 

---

## Demostración en Video

https://youtu.be/YPe4sF5viaY

---

## Conocimientos Adquiridos

1. **Modulación por Ancho de Pulso (PWM):** Uso de la función `analogWrite` para generar una señal que permite controlar el brillo de un LED de manera gradual, en lugar de solo encenderlo y apagarlo (`digitalWrite`).
2. **Manipulación de Pines Digitales (`pinMode`):** Configuración del pin de salida (GPIO 2) para el control del LED.
3. **Control de Flujo (`for`):** Utilización del bucle `for` para iterar a través de los valores de brillo (0 a 255 y 255 a 0), creando la rampa de transición suave.
4. **Control de Tiempo (`delay`):** Uso de `delay()` para espaciar cada cambio de brillo en 10ms y definir la velocidad del efecto de respiración.
5. **Modularidad de Código (Funciones):** Encapsulación de la lógica de la secuencia de atenuación completa en la función `pulso()`.