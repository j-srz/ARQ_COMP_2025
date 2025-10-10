#  Señal S.O.S. (Código Morse)

##  Introducción

Este proyecto implementa la señal internacional de socorro **S.O.S.** del Código Morse a través de un LED. La secuencia, **3 pulsos cortos** (S), **3 pulsos largos** (O), **3 pulsos cortos** (S), se repite continuamente después de una pausa inicial.

---

##  Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | **ESP32-WROOM-32** |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Hardware** (Opcional) | LED y Resistencia (220 a 330) |

---

##  Instalación y Uso

### **Carga del Código**

1.  **Copia y pega** el código en el **IDE de Arduino**.
2.  Selecciona la placa **ESP32** y el puerto **COM** correspondiente en el menú **Herramientas**.
3.  Haz clic en el botón **Subir** (Upload).

Una vez subido, el ESP32 iniciará la secuencia automáticamente.

### **Patrón de Ejecución**

El programa espera **5 segundos** (`delay(5000);`) al inicio y luego comienza el ciclo S.O.S.

* `corto()`: LED encendido por **$300\ \text{ms}$** (puntos del Morse).
* `largo()`: LED encendido por **$700\ \text{ms}$** (rayas del Morse).

---

##  Demostración en Video

<iframe width="560" height="315" src="https://www.youtube.com/embed/bKW5_UoGtM0" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


---

##  Conocimientos Adquiridos

La realización de este proyecto consolida los siguientes conocimientos fundamentales en programación de microcontroladores:

1.  **Manipulación de Pines Digitales (`pinMode`, `digitalWrite`):** Entendimiento y control de las salidas digitales para activar componentes (LED).
2.  **Control de Tiempo (`delay`):** Uso de la función `delay()` para generar pulsos con duraciones precisas, esencial para la correcta cadencia del Código Morse.
3.  **Modularidad de Código (Funciones):** Creación de funciones (`corto()` y `largo()`) para hacer el código más legible y reutilizable al definir patrones específicos de parpadeo.
4.  **Lógica de Secuencias:** Implementación de una secuencia específica y repetitiva (S.O.S.) dentro del bucle principal (`loop()`) de Arduino/ESP32.