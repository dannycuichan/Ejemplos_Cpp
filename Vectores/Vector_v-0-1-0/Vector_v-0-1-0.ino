#include <vector>
using namespace std;
//eliminar los ultimos datos con un boton

//? Mas informacion sobre vectores en https://www.geeksforgeeks.org/vector-in-cpp-stl/

#define BOTON 0
#define ACTIVO 2

vector<uint8_t> num = {1, 2, 6, 7, 2, 3, 7, 5, 6, 5, 6, 1, 2, 4, 2, 6, 2, 3, 7, 0, 7, 3, 2, 7, 8, 4, 5, 6, 2, 3, 7, 4, 6, 2, 8, 4};

void setup()
{
    Serial.begin(115200);

    pinMode(BOTON, INPUT);
    pinMode(ACTIVO, OUTPUT);
    print_VectorCar(num);
    Serial.print("numeros =\t");
    print_Vector(num);
}

void loop()
{
    digitalWrite(ACTIVO, digitalRead(BOTON));
    if (digitalRead(BOTON) == 0)
    {
        digitalWrite(ACTIVO, digitalRead(BOTON));
        num.pop_back(); //! No utilizar si el tamanio del vector es 0
        print_VectorCar(num);
        Serial.print("numeros =\t");
        print_Vector(num);
        while (digitalRead(BOTON) == 0)
            ;
    }
}

void print_Vector(vector<uint8_t> numeros)
{
    Serial.print("[");

    for (uint8_t i = 0; i < numeros.size(); i++)
    {
        Serial.print(numeros[i]);
        Serial.print(",\t");
    }
    Serial.println("]");
}

void print_VectorCar(vector<uint8_t> numeros)
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