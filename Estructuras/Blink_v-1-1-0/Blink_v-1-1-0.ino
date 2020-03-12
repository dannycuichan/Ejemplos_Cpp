//Funciones con punteros Estructuras

#define BOTON 0
#define ACTIVO 2

struct blink
{
    uint16_t tiempoON;    //ms
    uint16_t tiempoOFF;   //ms
    uint8_t repeticiones; //veces
    uint8_t pin;          //pin de salida
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
        blinkear(&blink1);
        blinkear(&blink2);
        blinkear(&blink3);
    }
}

void blinkear(struct blink * b){
   for (uint8_t i = 0; i < b->repeticiones; i++)
        {
            digitalWrite(b->pin, 1);
            delay(b->tiempoON);
            digitalWrite(b->pin, 0);
            delay(b->tiempoOFF);
        } 
}