#include <vector>
#define BOTON 0
#define ACTIVO 2
using namespace std;

struct blink
{
    const uint16_t tiempoON;    //ms
    const uint16_t tiempoOFF;   //ms
    const uint8_t repeticiones; //veces
    const uint8_t pin;          //pin de salida

    uint16_t tiempo;
    uint16_t contador;
};

uint8_t pines_disp[4] = {5, 4, 1, 16};

vector<blink> leds = {
    {1000, 1000, 5, 5, 0, 0},
    {500, 500, 10, 4, 0, 0},
    {1000, 500, 7, 1, 0, 0},
};

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);

    for (uint8_t i = 0; i < leds.size(); i++)
    {
        pinMode(leds[i].pin, OUTPUT);
    }

    digitalWrite(ACTIVO, 0);
}

void loop()
{
    if (digitalRead(ACTIVO) == 0)
    {
        for (uint8_t i = 0; i < leds.size(); i++)
        {
            leds[i].contador = 0;
            leds[i].tiempo = millis();
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
            ind1 = blinkear_p(&leds[i]);
            ind2 = (ind2 && ind1);
        }
        digitalWrite(ACTIVO, !(ind2));
    }
}

void blinkear(struct blink *b)
{
    for (uint8_t i = 0; i < b->repeticiones; i++)
    {
        digitalWrite(b->pin, 1);
        delay(b->tiempoON);
        digitalWrite(b->pin, 0);
        delay(b->tiempoOFF);
    }
}

bool blinkear_p(struct blink *b)
{
    Serial.println(b->repeticiones);
    if (b->contador == b->repeticiones)
        return true; //Acabo el blink

    uint16_t dt = millis() - (b->tiempo);

    if (digitalRead(b->pin) == 1)
    {
        if (dt >= b->tiempoON)
        {
            b->tiempo = millis();
            digitalWrite(b->pin, 0);
            b->contador++;
        }
    }
    else
    {
        if (dt >= b->tiempoOFF)
        {
            b->tiempo = millis();
            digitalWrite(b->pin, 1);
        }
    }
    return false;
}