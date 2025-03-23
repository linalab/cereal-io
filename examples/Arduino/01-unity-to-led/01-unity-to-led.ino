#include "Cereal.h"

Cereal cereal(9600);

void setup()
{
  pinMode(6, OUTPUT);
  cereal.begin();
}


void loop()
{

  cereal.passiveListen(500);
  int32_t readVal = cereal.readInt(0);
  analogWrite(6, readVal);
 cereal.passiveListen(100); 
}
