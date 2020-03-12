#include <vector>
#define BOTON_ADD 0
#define BOTON_REM 3
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

vector<blink> leds;

void setup()
{
    Serial.begin(115200);
    pinMode(BOTON_ADD, INPUT);
    pinMode(BOTON_REM, INPUT);
    pinMode(ACTIVO, OUTPUT);

    for (uint8_t i = 0; i < 4; i++)
    {
        pinMode(pines_disp[i], OUTPUT);
    }

    digitalWrite(ACTIVO, 0);
    print_VectorCar(leds);
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
        bool ind = blinkear_p(&leds[i]);
        if (ind)
        {
            
            leds[i].contador = 0;
            leds[i].tiempo = millis();
        }
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

    struct blink b
    {
        tON, tOFF, rep, pin, 0, 0
    };

    Serial.println("Nuevo");
    Serial.println("tON \ttOFF\trep \tpin");
    Serial.println(String(tON) +"\t\t"+String(tOFF)+"\t\t"+String(rep)+"\t\t"+String(pin));
    leds.push_back(b);
}

void rem_blink()
{
    if (leds.size() == 0)
        return;
    leds.pop_back();
    digitalWrite(pines_disp[leds.size()],0);
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

void print_VectorCar(vector<blink> numeros)
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