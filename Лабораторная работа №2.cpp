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
        printf("This body belongs to %s Galaxy\n", galaxyName.c_str());
    }

    Galaxy()
    {
        galaxyName = "";
        printf("Galaxy()\n");
    }

    Galaxy(std::string galaxyName)
    {
        this->galaxyName = galaxyName;
        printf("Galaxy(std::string galaxyName)\n");
    }

    Galaxy(const Galaxy& galaxy)
    {
        galaxyName = galaxy.galaxyName;
        printf("Galaxy(const Galaxy& galaxy)\n");
    }

    virtual ~Galaxy()
    {
        printf("%s\n", galaxyName.c_str());
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
        printf("This body belongs to %s System\n", planetarySystemName.c_str());
    }

    PlanetarySystem()
    {
        planetarySystemName = "";
        printf("PlanetarySystem()\n");
    }

    PlanetarySystem(std::string galaxyName, std::string planetarySystemName)
        :Galaxy(galaxyName)
    {
        this->planetarySystemName = planetarySystemName;
        printf("PlanetarySystem(std::string galaxyName, std::string planetarySystemName)\n");
    }

    PlanetarySystem(const PlanetarySystem& planetarySystem)
        :Galaxy(planetarySystem.galaxyName)
    {
        planetarySystemName = planetarySystem.planetarySystemName;
        printf("PlanetarySystem(const PlanetarySystem& planetarySystem)\n");
    }

    virtual ~PlanetarySystem()
    {
        printf("%s\n", planetarySystemName.c_str());
        printf("~PlanetarySystem()\n");
    }
};

class Moon : public CelestialBody
{
public:
    std::string moonName;

    Moon()
    {
        moonName = "";
        printf("Moon()\n");
    }

    void message()
    {
        printf("This body is а moon called %s\n", moonName.c_str());
    }

    Moon(double mass, double volume, double rotationPeriod, std::string moonName)
        :CelestialBody(mass, volume, rotationPeriod)
    {
        this->moonName = moonName;
        printf("Moon(double mass, double volume, double rotationPeriod, std::string moonName)\n");
    }

    Moon(const Moon& moon)
        :CelestialBody(moon.mass, moon.volume, moon.rotationPeriod)
    {
        moonName = moon.moonName;
        printf("Moon(const Moon& moon)\n");
    }

    virtual ~Moon()
    {
        printf("%s\n", moonName.c_str());
        printf("~Moon()\n");
    }
};

class Planet : public PlanetarySystem, public CelestialBody
{
private:
    int numberOfMoons = 0;
public:
    Moon** moon = new Moon*[63];
    
    std::string planetName;
    bool canBeHabitable;// Пригодна ли для жизни

    void message()
    {
        printf("This is а planet called %s\n", planetName.c_str());
    }

    Planet()
    {
        planetName = "";
        canBeHabitable = false;
        printf("Planet()");
    }

    Planet(double mass, double volume, double rotationPeriod, std::string galaxyName, std::string planetarySystemName, std::string planetName, bool canBeHabitable) 
        :CelestialBody(mass, volume, rotationPeriod), PlanetarySystem(galaxyName, planetarySystemName)
    {
        this->planetName = planetName;
        this->canBeHabitable = canBeHabitable;
        printf("Planet(double mass, double volume, double rotationPeriod, std::string galaxyName, std::string planetarySystemName, std::string planetName, bool canBeHabitable)\n");
    }

    Planet(const Planet& planet)
        :CelestialBody(planet.mass, planet.volume, planet.rotationPeriod), PlanetarySystem(planet.galaxyName, planet.planetarySystemName)
    {
        this->planetName = planet.planetName;
        this->canBeHabitable;
        for (int i = 0; i < numberOfMoons; i++)
        {
            moon[i] = new Moon(*planet.moon[i]);
        }
        printf("\nPlanet(const Planet& planet)");
    }

    virtual ~Planet()
    {
        for (int i = 0; i < numberOfMoons; i++)
        {
            delete moon[i];
        }
        delete moon;
        printf("%s\n", planetName.c_str());
        printf("~Planet()\n");
    }
    
};



int main()
{
    
}
