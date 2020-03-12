//Poling y estructuras

#define BOTON 0
#define ACTIVO 2

struct blink
{
    const uint16_t tiempoON;    //ms
    const uint16_t tiempoOFF;   //ms
    const uint8_t repeticiones; //veces
    const uint8_t pin;          //pin de salida

    uint16_t tiempo;
    uint16_t contador;
};

struct blink blink1
{
    1000, 1000, 5, 5, 0, 0
};

struct blink blink2
{
    500, 500, 10, 4, 0, 0
};

struct blink blink3
{
    1000, 500, 7, 1, 0, 0
};

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    pinMode(blink1.pin, OUTPUT);
    pinMode(blink2.pin, OUTPUT);
    pinMode(blink3.pin, OUTPUT);

    digitalWrite(ACTIVO, 0);
}

void loop()
{
    if (digitalRead(ACTIVO) == 0)
    {
        blink1.contador = 0;
        blink2.contador = 0;
        blink3.contador = 0;
        blink1.tiempo = millis();
        blink2.tiempo = millis();
        blink3.tiempo = millis();
        if (digitalRead(BOTON) == 0)
        {
            digitalWrite(ACTIVO, 1);
        }
    }
    else
    {

        bool ind1 = blinkear_p(&blink1);
        bool ind2 = blinkear_p(&blink2);
        bool ind3 = blinkear_p(&blink3);
        digitalWrite(ACTIVO, !(ind1 && ind2 && ind3));
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