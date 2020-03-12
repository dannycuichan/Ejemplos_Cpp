//Funciones con Estructuras

#define BOTON 0
#define ACTIVO 2

#include "blink_class.h"

blink_class blink1(1000, 1000, 5, 5);
blink_class blink2(500, 500, 10, 4);
blink_class blink3(1000, 500, 7, 1);

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    blink1.begin();
    blink2.begin();
    blink3.begin();
}

void loop()
{
    digitalWrite(ACTIVO, digitalRead(BOTON));
    if (digitalRead(BOTON) == 0)
    {
        digitalWrite(ACTIVO,digitalRead(BOTON));
        blink1.blinkear();
        blink2.blinkear();
        blink3.blinkear();
    }
}