//Poling y clases

#define BOTON 0
#define ACTIVO 2

#include "blink_class.h"

blink_class blink1(1000, 1000, 5, 5);
//blink_class blink1;
blink_class blink2(500, 500, 10, 4);
blink_class blink3(1000, 500, 7, 1);


void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    blink1.begin();
    blink2.begin();
    blink3.begin();

    digitalWrite(ACTIVO, 0);
}

void loop()
{
    if (digitalRead(ACTIVO) == 0)
    {
        blink1.reset();
        blink2.reset();
        blink3.reset();
        if (digitalRead(BOTON) == 0)
        {
            digitalWrite(ACTIVO, 1);
        }
    }
    else
    {
        bool ind1 = blink1.blinkear_p();
        bool ind2 = blink2.blinkear_p();
        bool ind3 = blink3.blinkear_p();
        digitalWrite(ACTIVO, !(ind1 && ind2 && ind3));
    }
}
