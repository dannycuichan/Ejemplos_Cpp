//Poling y clases
#include <vector>
using namespace std;

#define BOTON_ADD 0
#define BOTON_REM 3
#define ACTIVO 2

#include "blink_class.h"

uint8_t pines_disp[4] = {5, 4, 1, 16};

vector<blink_class> leds;

void setup()
{
    Serial.begin(115200);
    pinMode(BOTON_ADD, INPUT);
    pinMode(BOTON_REM, INPUT);
    pinMode(ACTIVO, OUTPUT);

    digitalWrite(ACTIVO, 0);
}

void loop()
{
    //Verificacion de Botones para aniadir blink
    digitalWrite(ACTIVO, digitalRead(BOTON_ADD));
    if (digitalRead(BOTON_ADD) == 0)
    {
        digitalWrite(ACTIVO, digitalRead(BOTON_ADD));
        add_blink();
        print_VectorCar(leds);
        while (digitalRead(BOTON_ADD) == 0)
            ;
    }
    //Verificacion de Botones para remover blink
    digitalWrite(ACTIVO, digitalRead(BOTON_REM));
    if (digitalRead(BOTON_REM) == 0)
    {
        digitalWrite(ACTIVO, digitalRead(BOTON_REM));
        rem_blink();
        print_VectorCar(leds);
        while (digitalRead(BOTON_REM) == 0)
            ;
    }

    //Blink leds
    for (uint8_t i = 0; i < leds.size(); i++)
    {
        bool ind = leds[i].blinkear_p();
        if (ind)
            leds[i].reset();
    }
}

void add_blink()
{
    if (leds.size() >= 4)
        return;
    uint16_t tON = random(11) * 100;       //ms
    uint16_t tOFF = random(11) * 100;      //ms
    uint8_t rep = random(1, 6);            //veces
    uint8_t pin = pines_disp[leds.size()]; //pin de salida

    blink_class b(tON, tOFF, rep, pin);
    Serial.println("Nuevo");
    Serial.println("tON \ttOFF\trep \tpin");
    Serial.println(String(tON) + "\t\t" + String(tOFF) + "\t\t" + String(rep) + "\t\t" + String(pin));
    leds.push_back(b);
    leds[leds.size() - 1].begin();
}

void rem_blink()
{
    if (leds.size() == 0)
        return;
    leds.pop_back();
    digitalWrite(pines_disp[leds.size()], 0);
}

void print_VectorCar(vector<blink_class> numeros)
{
    Serial.println("**********Caracteristicas del vector**********");

    Serial.print("tamanio vector =\t\t");
    Serial.println(numeros.size());
    Serial.print("tamanio maximo=\t\t");
    Serial.println(numeros.max_size());
    Serial.print("vector vacio=\t\t");
    Serial.println((numeros.empty()) ? "true" : "false");

    Serial.println("**********************************************");
}