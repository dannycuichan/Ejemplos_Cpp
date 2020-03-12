//3 Estructuras Basicas

#define BOTON 0
#define ACTIVO 2

struct blink
{
    uint16_t tiempoON;    //ms
    uint16_t tiempoOFF;   //ms
    uint8_t repeticiones; //veces
    uint8_t pin;          //veces
};

struct blink blink1
{
    1000, 1000, 5, 5
};

struct blink blink2
{
    500, 500, 10, 4
};

struct blink blink3
{
    1000, 500, 7, 1
};

void setup()
{
    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    pinMode(blink1.pin, OUTPUT);
    pinMode(blink2.pin, OUTPUT);
    pinMode(blink3.pin, OUTPUT);
}

void loop()
{
    digitalWrite(ACTIVO, digitalRead(BOTON));
    if (digitalRead(BOTON) == 0)
    {
        digitalWrite(ACTIVO,digitalRead(BOTON));
        for (uint8_t i = 0; i < blink1.repeticiones; i++)
        {
            digitalWrite(blink1.pin, 1);
            delay(blink1.tiempoON);
            digitalWrite(blink1.pin, 0);
            delay(blink1.tiempoOFF);
        }
        for (uint8_t i = 0; i < blink2.repeticiones; i++)
        {
            digitalWrite(blink2.pin, 1);
            delay(blink2.tiempoON);
            digitalWrite(blink2.pin, 0);
            delay(blink2.tiempoOFF);
        }
        for (uint8_t i = 0; i < blink3.repeticiones; i++)
        {
            digitalWrite(blink3.pin, 1);
            delay(blink3.tiempoON);
            digitalWrite(blink3.pin, 0);
            delay(blink3.tiempoOFF);
        }
    }
}

