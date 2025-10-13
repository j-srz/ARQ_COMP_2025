#  Señal S.O.S. y Secuencia Adicional de 7 blinks (Código Morse)

---

## Introducción

Este proyecto implementa la señal internacional de socorro **S.O.S.** del Código Morse a través de un LED en un microcontrolador **ESP32**. La ejecución sigue un patrón cíclico que incluye la secuencia S.O.S., una pausa y una secuencia de 7 pulsos cortos.


---

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | **ESP32-WROOM-32** |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Hardware** (Opcional) | LED y Resistencia (220 a 330) |

---

### **Carga del Código**

1.  **Copia y pega** el código en el **IDE de Arduino**.
2.  Selecciona la placa **ESP32** y el puerto **COM** correspondiente en el menú **Herramientas**.
3.  Haz clic en el botón **Subir** (Upload).

Una vez subido, el ESP32 iniciará la secuencia automáticamente.

---

## Patrón de Ejecución

El programa espera **5 segundos** (`delay(5000);`) al inicio.
El programa comienza el ciclo S.O.S `sos()`.
El programa espera **5 segundos** (`delay(5000);`)
El programa realiza una secuencia de 7 parpadeos cortos `corto()`.

* `corto()`: LED encendido por **$300\ \text{ms}$** (puntos del Morse).
* `largo()`: LED encendido por **$700\ \text{ms}$** (rayas del Morse).
* `sos()`: Realiza la secuancia de coros y largos necesarios para un SOS en codigo morse.

---

##  Demostración en Video

https://youtu.be/uSTwHZu95j0


---

##  Conocimientos Adquiridos

1.  **Manipulación de Pines Digitales (`pinMode`, `digitalWrite`):** Configuración y control de un pin de salida (GPIO 2).
2.  **Control de Tiempo (`delay`):** Uso de retrasos (`delay()`) para crear la **cadencia precisa** de los pulsos Morse.
3.  **Modularidad de Código (Funciones):** Uso de funciones (`corto()`, `largo()`, `sos()`) para encapsular la lógica de parpadeo y la secuencia S.O.S., haciendo el código más claro.
4.  **Estructuras de Control:** Implementación del bucle `for` para repetir la función `corto()` un número específico de veces (7) dentro del ciclo principal.
5.  **Lógica de Secuencias:** Construcción de una **secuencia compuesta y repetitiva** en la función `loop()`.
