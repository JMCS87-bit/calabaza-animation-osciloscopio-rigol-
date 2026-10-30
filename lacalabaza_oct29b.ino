
#include <Arduino.h>
#include <math.h>

const int PIN_X = 25;
const int PIN_Y = 26;
const int PAUSA_US = 150;
const float ESCALA = 50.0f;

struct Punto {
  float x;
  float y;
};

const Punto boca1[] = {
  {-0.55,-0.12},
  {-0.35,-0.20},
  {-0.15,-0.23},
  { 0.00,-0.24},
  { 0.15,-0.23},
  { 0.35,-0.20},
  { 0.55,-0.12},
  { 0.35,-0.28},
  { 0.15,-0.31},
  { 0.00,-0.32},
  {-0.15,-0.31},
  {-0.35,-0.28},
  {-0.55,-0.12}
};

const Punto boca2[] = {
  {-0.59,-0.02},
  {-0.54,-0.23},
  {-0.43,-0.40},
  {-0.27,-0.46},
  {-0.12,-0.45},
  {-0.08,-0.27},
  { 0.00,-0.39},
  { 0.08,-0.27},
  { 0.12,-0.45},
  { 0.27,-0.46},
  { 0.43,-0.40},
  { 0.54,-0.23},
  { 0.59,-0.02},
  { 0.43,-0.08},
  { 0.30,-0.04},
  { 0.18,-0.10},
  { 0.00,-0.08},
  {-0.18,-0.10},
  {-0.30,-0.04},
  {-0.43,-0.08},
  {-0.59,-0.02}
};

// Silueta redondeada con lobulos
const Punto contorno[] = {
  {-0.12, 0.72}, {-0.28, 0.88}, {-0.48, 0.83},
  {-0.64, 0.65}, {-0.78, 0.42}, {-0.84, 0.12},
  {-0.83,-0.20}, {-0.72,-0.48}, {-0.53,-0.65},
  {-0.34,-0.69}, {-0.18,-0.60}, { 0.00,-0.72},
  { 0.18,-0.60}, { 0.34,-0.69}, { 0.53,-0.65},
  { 0.72,-0.48}, { 0.83,-0.20}, { 0.84, 0.12},
  { 0.78, 0.42}, { 0.64, 0.65}, { 0.48, 0.83},
  { 0.28, 0.88}, { 0.12, 0.72}, { 0.00, 0.78},
  {-0.12, 0.72}
};

// Tallo curvo
const Punto tallo[] = {
  {-0.12, 0.72}, {-0.10, 0.87}, {-0.04, 1.00},
  { 0.04, 1.04}, { 0.13, 1.00}, { 0.08, 0.92},
  { 0.02, 0.82}, { 0.02, 0.74}
};

// Ojo izquierdo, inclinado
const Punto ojoIzq[] = {
  {-0.61, 0.43}, {-0.48, 0.35}, {-0.30, 0.30},
  {-0.20, 0.34}, {-0.29, 0.19}, {-0.39, 0.15},
  {-0.49, 0.19}, {-0.56, 0.29}, {-0.61, 0.43}
};

// Ojo derecho, inclinado
const Punto ojoDer[] = {
  { 0.20, 0.34}, { 0.30, 0.30}, { 0.48, 0.35},
  { 0.61, 0.43}, { 0.56, 0.29}, { 0.49, 0.19},
  { 0.39, 0.15}, { 0.29, 0.19}, { 0.20, 0.34}
};

// Nariz triangular
const Punto nariz[] = {
  {-0.10, 0.08}, { 0.00, 0.25},
  { 0.10, 0.08}, { 0.00, 0.04},
  {-0.10, 0.08}
};

// Boca con dientes puntiagudos
const Punto boca[] = {
  {-0.59,-0.02}, {-0.54,-0.23},
  {-0.43,-0.40}, {-0.27,-0.46},
  {-0.12,-0.45}, {-0.08,-0.27},
  { 0.00,-0.39}, { 0.08,-0.27},
  { 0.12,-0.45}, { 0.27,-0.46},
  { 0.43,-0.40}, { 0.54,-0.23},
  { 0.59,-0.02}, { 0.43,-0.08},
  { 0.30,-0.04}, { 0.18,-0.10},
  { 0.00,-0.08}, {-0.18,-0.10},
  {-0.30,-0.04}, {-0.43,-0.08},
  {-0.59,-0.02}
};

void irA(float x, float y) {
  int vx = 128 + (int)roundf(x * ESCALA);
  int vy = 128 + (int)roundf(y * ESCALA);

  dacWrite(PIN_X, constrain(vx, 0, 255));
  dacWrite(PIN_Y, constrain(vy, 0, 255));
}

void dibujar(const Punto *p, int n) {
  // Desplazamiento directo al comienzo del trazo
  irA(p[0].x, p[0].y);
  delayMicroseconds(PAUSA_US);

  // Interpolar los puntos para formar lineas
  for (int i = 0; i < n - 1; i++) {
    float dx = p[i + 1].x - p[i].x;
    float dy = p[i + 1].y - p[i].y;

    int pasos = (int)(sqrtf(dx * dx + dy * dy) * 100.0f);
    if (pasos < 2) pasos = 2;

    for (int j = 1; j <= pasos; j++) {
      float t = (float)j / pasos;

      irA(p[i].x + dx * t,
          p[i].y + dy * t);

      delayMicroseconds(PAUSA_US);
    }
  }
}

void setup() {
  dacWrite(PIN_X, 128);
  dacWrite(PIN_Y, 128);
}


const int REPETICIONES_FRAME = 5;

void loop() {
  // Frame 1: boca cerrada
  for (int i = 0; i < REPETICIONES_FRAME; i++) {
    dibujar(contorno, sizeof(contorno) / sizeof(contorno[0]));
    dibujar(tallo, sizeof(tallo) / sizeof(tallo[0]));
    dibujar(ojoIzq, sizeof(ojoIzq) / sizeof(ojoIzq[0]));
    dibujar(ojoDer, sizeof(ojoDer) / sizeof(ojoDer[0]));
    dibujar(nariz, sizeof(nariz) / sizeof(nariz[0]));
    dibujar(boca1, sizeof(boca1) / sizeof(boca1[0]));
  }

  // Frame 2: boca abierta
  for (int i = 0; i < REPETICIONES_FRAME; i++) {
    dibujar(contorno, sizeof(contorno) / sizeof(contorno[0]));
    dibujar(tallo, sizeof(tallo) / sizeof(tallo[0]));
    dibujar(ojoIzq, sizeof(ojoIzq) / sizeof(ojoIzq[0]));
    dibujar(ojoDer, sizeof(ojoDer) / sizeof(ojoDer[0]));
    dibujar(nariz, sizeof(nariz) / sizeof(nariz[0]));
    dibujar(boca2, sizeof(boca2) / sizeof(boca2[0]));
  }
}

