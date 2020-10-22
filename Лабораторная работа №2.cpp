#include <iostream>

class CelestialBody
{
public:
    double mass;// В килограммах
    double volume; // В кубических километрах
    
    CelestialBody()
    {
        mass = 0;
        volume = 0;
        printf("CelestialBody()\n");
    }

    CelestialBody(double mass, double volume)
    {
        this->mass = mass;
        this->volume = volume;
        printf("CelestialBody(double mass, double volume)\n");
    }

    CelestialBody(const CelestialBody &body)
    {
        mass = body.mass;
        volume = body.volume;
        printf("CelestialBody(const CelestialBody &body)");
    }

    ~CelestialBody()
    {
        printf("mass = %f, volume = %f\n", mass, volume);
        printf("~CelestialBody()\n");
    }
};

int main()
{
    
}
