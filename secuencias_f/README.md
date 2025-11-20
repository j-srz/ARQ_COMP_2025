# Secuencial

## Introducción

Este proyecto implementa una secuencia automática de patrones de luz utilizando un LED RGB NeoPixel y un LED estándar monocromático. A diferencia de versiones más complejas, este código utiliza una arquitectura **secuencial lineal**. 

El sistema ejecuta tres animaciones predefinidas (SOS, Parpadeo y Pulso) en un bucle infinito. Utiliza la función estándar `delay()`, lo que significa que el procesador se dedica exclusivamente a la iluminación y espera a terminar una animación antes de pasar a la siguiente.

## Plataforma y Requisitos

| Categoría | Detalle |
| :--- | :--- |
| **Placa de Desarrollo** | ESP32-S3-WROOM-32 (Compatible con Arduino) |
| **Lenguaje** | C/C++ (IDE de Arduino) |
| **Librería Requerida** | `Adafruit_NeoPixel` |
| **Hardware (Salidas)** | 1x LED RGB NeoPixel (Pin 48), 1x LED Estándar (Pin 2) |
| **Hardware (Entradas)** | 4x Pulsadores (Definidos en pines 4, 5, 6, 7 pero no activos en esta lógica) |

## Carga del Código

1. **Instalar Librerías:** Asegúrate de tener instalada la librería `Adafruit_NeoPixel`.
2. **Configuración de Hardware:** Conecta los LEDs a los pines definidos:
    * `LED_PIN` (Pin 2 - LED Estándar)
    * `LED_RGB` (Pin 48 - NeoPixel)
3. **Compilación:** Selecciona tu placa ESP32-S3 y sube el código.
4. **Funcionamiento:** Al encender, la placa comenzará la secuencia automáticamente sin necesidad de presionar botones.

## Patrón de Ejecución

El ciclo principal (`loop`) controla el flujo del programa de manera rígida y ordenada. El patrón de ejecución es el siguiente:

1. **Inicio del Loop:**
2. **Ejecución de `sos()`:** Reproduce el patrón de auxilio visual.
3. **Ejecución de `blink()`:** Realiza una serie rápida de parpadeos.
4. **Ejecución de `pulso()`:** Realiza un efecto de respiración (fade in/out).
5. **Repetición:** Vuelve al paso 1 indefinidamente.



### Descripción de las Funciones

* **`sos()`:**
  Genera la señal Morse S-O-S (3 cortos, 3 largos, 3 cortos). Utiliza las funciones auxiliares `corto()` y `largo()` para manejar los tiempos de encendido y apagado.

* **`blink()`:**
  Ejecuta un bucle `for` que llama a la función `corto()` 7 veces consecutivas, creando un efecto de estrobo rápido con colores aleatorios.

* **`pulso()`:**
  Genera un color aleatorio (`random(0, 256)`) y realiza dos ciclos:
  1. **Aumento:** Sube el brillo de 0 a 255 usando `PWM` (para el LED normal) y `setBrightness` (para el RGB).
  2. **Disminución:** Baja el brillo de 255 a 0.
  Esto crea un efecto suave de "respiración".

* **`corto()` y `largo()`:**
  Son funciones de utilidad que:
  1. Encienden ambos LEDs con un color aleatorio.
  2. Esperan un tiempo definido (`delay(200)` para corto, `delay(400)` para largo).
  3. Apagan los LEDs y esperan un tiempo de silencio (`delay(100)`).

## Demostración en Video

-- DENTRO DEL REPOSITORIO SE ENCUENTRA EL VIDEO --

## Conocimientos Adquiridos

Este código demuestra los fundamentos de la programación secuencial en sistemas embebidos:

1. **Lógica Secuencial:** Estructuración de tareas una tras otra dentro del `loop()` principal.
2. **Control de Tiempo (Timing):** Uso de `delay()` para controlar la duración de los estados (encendido/apagado), entendiendo que esto detiene el flujo del procesador.
3. **Generación de Aleatoriedad:** Uso de `random()` para crear efectos visuales dinámicos que cambian en cada iteración.
4. **Modulación por Ancho de Pulso (PWM):** Uso de `analogWrite()` para controlar la intensidad del LED estándar, creando efectos de desvanecimiento (fading).
5. **Abstracción de Funciones:** Creación de bloques de código reutilizables (`corto`, `largo`) para simplificar la lectura del algoritmo principal.