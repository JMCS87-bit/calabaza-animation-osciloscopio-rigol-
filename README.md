\# 🎃 Calabaza Halloween - ESP32 + Rigol DHO804



Proyecto experimental que utiliza un \*\*ESP32\*\* para dibujar una calabaza de Halloween en la pantalla de un osciloscopio digital Rigol DHO804 mediante el modo \*\*XY\*\*.



El dibujo se genera utilizando dos señales analógicas sincronizadas que representan las coordenadas X e Y. Mediante una secuencia de puntos se construye la silueta de la calabaza, sus ojos, nariz y boca.



Además, incorpora una animación de dos frames que permite alternar entre una boca cerrada y una boca abierta.



\## ✨ Características



\- Dibujo vectorial mediante coordenadas X/Y.

\- Generación de señales analógicas utilizando los DAC internos del ESP32.

\- Visualización en modo XY del Rigol DHO804.

\- Silueta de calabaza con detalles faciales.

\- Animación de la boca mediante dos frames.

\- Control del tamaño de la figura mediante un factor de escala.

\- Ajuste de la velocidad de dibujo mediante retardos entre puntos.



\## 🛠️ Hardware utilizado



\- ESP32-WROOM-32.

\- Osciloscopio digital Rigol DHO804.

\- Dos sondas de osciloscopio.

\- Cables de conexión.



\## 🔌 Conexiones



| ESP32 | Rigol DHO804 | Función |

|---|---|---|

| GPIO25 (DAC1) | CH1 | Coordenada X |

| GPIO26 (DAC2) | CH2 | Coordenada Y |

| GND | GND | Tierra común |



\## ⚙️ Configuración del osciloscopio



1\. Conectar las señales del ESP32 a los canales CH1 y CH2.

2\. Activar ambos canales.

3\. Seleccionar el modo XY.

4\. Configurar CH1 como eje horizontal (X).

5\. Configurar CH2 como eje vertical (Y).

6\. Ajustar las escalas verticales de ambos canales.

7\. Centrar la figura utilizando los controles de posición.



La escala y posición deben ajustarse para conseguir una visualización adecuada de la imagen.



&#x20;Configuración del código



El proyecto está desarrollado utilizando Arduino IDE.



Parámetros principales:



| Parámetro | Valor inicial |

|---|---:|

| GPIO DAC X | 25 |

| GPIO DAC Y | 26 |

| Resolución DAC | 8 bits |

| Pausa entre puntos | 150 µs |

| Factor de escala | 65 |



El tamaño de la figura puede modificarse mediante:



```cpp

const float ESCALA = 65.0f;

```



La velocidad de dibujo se controla mediante:



```cpp

const int PAUSA\_US = 150;

```



\## 🎞️ Animación de la boca



La animación utiliza dos conjuntos de coordenadas:



\- \*\*Frame 1:\*\* boca cerrada.

\- \*\*Frame 2:\*\* boca abierta.



Cada frame se dibuja varias veces antes de pasar al siguiente. Esto permite mantener una mayor persistencia visual sin introducir pausas que interrumpan la generación de señales.



La cantidad de repeticiones se controla mediante:





const int REPETICIONES\_FRAME = 8;





&#x20;Funcionamiento



El ESP32 genera dos señales analógicas independientes:



\- La primera señal determina la posición horizontal.

\- La segunda señal determina la posición vertical.



El osciloscopio combina ambas señales en modo XY y representa gráficamente los puntos recibidos.



El resultado es un dibujo vectorial que se reproduce continuamente en la pantalla del osciloscopio.



\##  Consideraciones



\- Este proyecto está diseñado para el ESP32 clásico con DAC interno.

\- Los GPIO25 y GPIO26 trabajan con una resolución de 8 bits.

\- No conectar tensiones negativas ni superiores al rango permitido en las entradas del ESP32.

\- Compartir GND entre el ESP32 y las sondas del osciloscopio.

\- Ajustar las escalas del osciloscopio para evitar que la figura quede recortada.

\- La calidad visual depende de la velocidad de actualización y de la persistencia del osciloscopio.



&#x20;Tecnologías utilizadas



\- ESP32

\- Arduino IDE

\- C/C++

\- DAC de 8 bits

\- Osciloscopio digital Rigol DHO804

\- Visualización XY



&#x20;Licencia



Este proyecto se distribuye bajo la licencia \*\*MIT\*\*.



Consulta el archivo `LICENSE` para conocer los términos de uso, modificación y distribución.







\*\*Proyecto experimental de dibujo vectorial mediante señales analógicas y osciloscopio digital.\*\*



🎃 ¡Feliz Halloween!



