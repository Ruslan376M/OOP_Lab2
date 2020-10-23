#include <iostream>
#include <locale.h>

class CelestialBody
{
public:
    double mass;// В килограммах
    double volume; // В кубических километрах
    double rotationPeriod; // В сутках
    
    virtual void message()
    {
        printf("This is a body\n");
    }

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

    virtual void message()
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

    virtual void message()
    {
        printf("This is а planet called %s\n", planetName.c_str());
    }

    void addMoon(const Moon& moon)
    {
        this->moon[numberOfMoons] = new Moon(moon);
        numberOfMoons++;
        printf("Added moon called %s\n", moon.moonName.c_str());
    }

    Planet()
    {
        planetName = "";
        canBeHabitable = false;
        printf("Planet()\n");
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
            numberOfMoons++;
        }
        printf("\nPlanet(const Planet& planet)\n");
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
    setlocale(LC_ALL, "Russian");
    {
        printf("Статическое создание и использование и удаление объектов\n\n");
        Planet Earth;
        Earth.planetName = "Earth";
        Earth.message();
    }
    {
        printf("\nДинамическое создание, использование и удаление объектов\n\n");
        Planet* Earth = new Planet(5.9726e24, 10.8321e11, 0.99726968, "MilkyWay", "SolarSystem", "Earth", true);
        Earth->message();
        Planet* Jupiter = new Planet(1.8986e27, 1.43128e15, 0.41, "MilkyWay", "SolarSystem", "Jupiter", false);
        Jupiter->message();
        Moon* theMoon = new Moon(7.3477e22, 2.1958, Earth->rotationPeriod, "Moon");
        Earth->addMoon(*theMoon);

        delete Earth;
        delete Jupiter;
        delete theMoon;
    }
    {
        printf("\nСоздание и использование объектов с помощью различных конструкторов\n");
        Planet* Mars = new Planet();
        printf("\n\n");
        Planet* Earth = new Planet(5.9726e24, 10.8321e11, 0.99726968, "MilkyWay", "SolarSystem", "Earth", true);
        printf("\n\n");
        Planet* Earth2 = new Planet(*Earth);

        delete Mars;
        delete Earth;
        delete Earth2;
    }
    {
        printf("\nПомещение объектов в переменные различных типов\n");
        CelestialBody* Body = new CelestialBody(5000000, 17250000, 2.783);
        CelestialBody* Earth = new Planet(5.9726e24, 10.8321e11, 0.99726968, "MilkyWay", "SolarSystem", "Earth", true);
        CelestialBody* Jupiter = new Planet(1.8986e27, 1.43128e15, 0.41, "MilkyWay", "SolarSystem", "Jupiter", false);
        CelestialBody* theMoon = new Moon(7.3477e22, 2.1958, Earth->rotationPeriod, "Moon");

        Body->message();
        Earth->message();
        Jupiter->message();
        theMoon->message();
        
        printf("\ndelete Body\n");
        delete Body;
        printf("\ndelete Earth\n");
        delete Earth;
        printf("\ndelete Jupiter\n");
        delete Jupiter;
        printf("\ndelete theMoon\n");
        delete theMoon;
    }
    {
        printf("\nКомпозиция объектов\n");
        Planet* Earth = new Planet(5.9726e24, 10.8321e11, 0.99726968, "MilkyWay", "SolarSystem", "Earth", true);
        Moon* theMoon = new Moon(7.3477e22, 2.1958, Earth->rotationPeriod, "Moon");
        Earth->addMoon(*theMoon);

        delete Earth;
        delete theMoon;
    }
}
