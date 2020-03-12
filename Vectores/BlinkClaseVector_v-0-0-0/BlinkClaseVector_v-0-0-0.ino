//Poling y clases
#include <vector>
using namespace std;

#define BOTON 0
#define ACTIVO 2

#include "blink_class.h"

blink_class blink1(1000, 1000, 5, 5);
//blink_class blink1;
blink_class blink2(500, 500, 10, 4);
blink_class blink3(1000, 500, 7, 1);

vector<blink_class> leds = {
    blink1,
    blink2,
    blink3,
};

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    for (uint8_t i = 0; i < leds.size(); i++)
    {
        leds[i].begin();
    }

    digitalWrite(ACTIVO, 0);
}

void loop()
{
    if (digitalRead(ACTIVO) == 0)
    {
        for (uint8_t i = 0; i < leds.size(); i++)
        {
            leds[i].reset();
        }
        if (digitalRead(BOTON) == 0)
        {
            digitalWrite(ACTIVO, 1);
        }
    }
    else
    {
        bool ind1 = true;
        bool ind2 = true;
        for (uint8_t i = 0; i < leds.size(); i++)
        {
            ind1 = leds[i].blinkear_p();
            ind2 = (ind2 && ind1);
        }
        digitalWrite(ACTIVO, !(ind2));
    }
}
