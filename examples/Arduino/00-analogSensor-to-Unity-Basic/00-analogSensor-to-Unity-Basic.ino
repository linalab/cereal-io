/* Ejemplo básico para enviar un Float
desde un sensor analógico a Unity
utilizando la librería Cereal-io
https://github.com/bernatGene/cereal-io*/

// Arduino code
#include "Cereal.h"
Cereal cereal(9600);
float valor;

void setup() {
  cereal.begin();
  pinMode(A0, INPUT);
}

void loop() {
  valor = analogRead(A0);
  valor=valor/1000;
  cereal.sendFloat(0, valor);
  cereal.passiveListen(100); 
}
