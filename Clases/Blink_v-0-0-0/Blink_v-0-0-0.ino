#define BOTON 0
#define ACTIVO 2

#include "blink_class.h"

blink_class blink;

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    blink.begin();
}

void loop()
{
    digitalWrite(ACTIVO, digitalRead(BOTON));
    if (digitalRead(BOTON) == 0)
    {
        digitalWrite(ACTIVO, digitalRead(BOTON));
        blink.blinkear();
    }
}
