class blink_class
{
//protected:
public:
    uint16_t tiempoON = 1000;  //ms
    uint16_t tiempoOFF = 1000; //ms
    uint8_t repeticiones = 5;  //veces
    uint8_t pin = 16;          //pin de salida
    uint16_t tiempo = 0;
    uint16_t contador = 0;

public:
    blink_class(uint16_t tON, uint16_t tOFF, uint8_t rep, uint8_t out);
    blink_class();
    void begin();
    void blinkear();
    bool blinkear_p();
    void reset();

};

blink_class::blink_class(uint16_t tON, uint16_t tOFF, uint8_t rep, uint8_t out)
{
    tiempoON = tON;     //ms
    tiempoOFF = tOFF;   //ms
    repeticiones = rep; //veces
    pin = out;          //pin de salida
}

blink_class::blink_class()
{
}

void blink_class::begin()
{
    tiempo = millis();
    pinMode(pin, OUTPUT);
}

void blink_class::blinkear()
{
    for (uint8_t i = 0; i < repeticiones; i++)
    {
        digitalWrite(pin, 1);
        delay(tiempoON);
        digitalWrite(pin, 0);
        delay(tiempoOFF);
    }
}

bool blink_class::blinkear_p()
{
    Serial.println(repeticiones);
    if (contador == repeticiones)
        return true; //Acabo el blink

    uint16_t dt = millis() - (tiempo);

    if (digitalRead(pin) == 1)
    {
        if (dt >= tiempoON)
        {
            tiempo = millis();
            digitalWrite(pin, 0);
            contador++;
        }
    }
    else
    {
        if (dt >= tiempoOFF)
        {
            tiempo = millis();
            digitalWrite(pin, 1);
        }
    }
    return false;
}

void blink_class::reset()
{
    contador = 0;
    tiempo = millis();
}