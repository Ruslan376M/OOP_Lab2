#include <iostream>

class CelestialBody
{
public:
    double mass;// В килограммах
    double volume; // В кубических километрах
    double rotationPeriod; // В сутках
    
    CelestialBody()
    {
        mass = 0;
        volume = 0;
        rotationPeriod = 0;
        printf("CelestialBody()\n");
    }

    CelestialBody(double mass, double volume, double rotationPeriod)
    {
        this->mass = mass;
        this->volume = volume;
        this->rotationPeriod = rotationPeriod;
        printf("CelestialBody(double mass, double volume, double rotationPeriod)\n");
    }

    CelestialBody(const CelestialBody &body)
    {
        mass = body.mass;
        volume = body.volume;
        rotationPeriod = body.rotationPeriod;
        printf("CelestialBody(const CelestialBody &body)");
    }

    virtual ~CelestialBody()
    {
        printf("mass = %f, volume = %f, rotationPeriod = %f\n", mass, volume, rotationPeriod);
        printf("~CelestialBody()\n");
    }
};

class Galaxy 
{
protected: 
    std::string galaxyName;
public:
    std::string getGalaxyName()
    {
        return galaxyName;
    }
    void message()
    {
        printf("This body belongs to %s Galaxy\n", galaxyName);
    }
    Galaxy()
    {
        galaxyName = "";
        printf("Galaxy()\n");
    }
    Galaxy(const Galaxy& galaxy)
    {
        galaxyName = galaxy.galaxyName;
        printf("Galaxy(const Galaxy& galaxy)\n");
    }
    virtual ~Galaxy()
    {
        printf("%s\n", galaxyName);
        printf("~Galaxy()\n");
    }
};

class PlanetarySystem: public Galaxy
{
protected:
    std::string planetarySystemName;
public:
    std::string getPlanetarySystemName()
    {
        return planetarySystemName;
    }
    void message()
    {
        printf("This body belongs to %s System\n", planetarySystemName);
    }
    PlanetarySystem()
    {
        planetarySystemName = "";
        printf("PlanetarySystem()\n");
    }
    PlanetarySystem(const PlanetarySystem& planetarySystem)
    {
        planetarySystemName = planetarySystem.planetarySystemName;
        printf("PlanetarySystem(const PlanetarySystem& planetarySystem)\n");
    }
    virtual ~PlanetarySystem()
    {
        printf("%s\n", planetarySystemName);
        printf("~PlanetarySystem()\n");
    }
};

class Planet : public PlanetarySystem, public CelestialBody
{
private:
    int numberOfMoons = 0;
public:
    Moon* moons = new Moon[100];
    
    std::string planetName;
    bool canBeHabitable;// Пригодна ли для жизни

    Planet()
    {

    }
    
};

class Moon : CelestialBody
{

};

int main()
{
    
}
