#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Exoplanet {
    char *name;
    char *system;
    int year;
    char *facility;
    double radius;
    char* method;
    double mass;
    int temperature;
    double habitability;


} Exoplanet;


Exoplanet *exoplanet_parse(const char *str) {

    // allocate memory in the heap that can accomodate an Exoplanet structure
    Exoplanet *planet = malloc(sizeof(Exoplanet));

    // temporary buffers on stack for strings
    char nameBuffer[50];
    char systemBuffer[50];
    char facilityBuffer[50];
    char methodBuffer[50];

    // variables for numeric values
    int year;
    int radius;
    double mass;
    int temperature;
    double habitability;

    // breaking the line from exoplanets.txt parameter into seprate values
    sscanf(str, "\"%49[^\"]\", \"%49[^\"]\", \"%49[^\"]\", %d, %49[^,], %f, %f, %d, %f", 
        nameBuffer,
        systemBuffer,
        methodBuffer,
        &year,
        facilityBuffer,
        &radius,
        &mass,
        &temperature,
        &habitability

    );

    // when assigning strings to new planet: allocating space needed with malloc using
    //                                       sizeof so null terminators included

    planet->name = malloc(sizeof(nameBuffer));
    strcpy(planet->name, nameBuffer);

    planet->system =malloc(sizeof(systemBuffer));
    strcpy(planet->system, systemBuffer);

    planet->year = year;

    planet->facility = malloc(sizeof(facilityBuffer));
    strcpy(planet->facility, facilityBuffer);

    planet->radius = radius;

    planet->method = malloc(sizeof(methodBuffer));
    strcpy(planet->method, methodBuffer);

    planet->mass = mass;

    planet->temperature = temperature;

    planet->habitability = habitability;

    return planet;

}


void exoplanet_free(Exoplanet *planet) {
    free(planet);
}


const char* exoplanet_toString(const Exoplanet *planet) {
    static char toStringBuffer[450];
    snprintf(toStringBuffer, sizeof(toStringBuffer), "\"%s\", \"%s\", \"%s\", %d, \"%s\", %f, %f, %d, %f", 
        planet->name,
        planet->system,
        planet->method,
        planet->year,
        planet->facility,
        planet->radius,
        planet->mass,
        planet->temperature,
        planet->habitability
    );
    printf("%s",toStringBuffer); //! remove - this is for troubleshooting / testing
    return toStringBuffer;
}


const char* exoplanet_getName(const Exoplanet *planet) {
    return planet->name;
}

const char* exoplanet_getSystem(const Exoplanet *planet) {
    return planet->system;
}

const char* exoplanet_getMethod(const Exoplanet *planet) {
    return planet->method;
}

int exoplanet_getYear(const Exoplanet *planet) {
    return planet->year;
}

const char* exoplanet_getFacility(const Exoplanet *planet) {
    return planet->facility;
}

double exoplanet_getRadius(const Exoplanet *planet) {
    return planet->radius;
}

double exoplanet_getMass(const Exoplanet *planet) {
    return planet->mass;
}

int exoplanet_getTemperature(const Exoplanet *planet) {
    return planet->temperature;
}

double exoplanet_getHabitability(const Exoplanet *planet) {
    return planet->habitability;
}

void exoplanet_setHabitability(Exoplanet *planet, double habitability) {
    planet->habitability = habitability;
}

int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b) {
    double difference = a->habitability - b->habitability;
    if (difference < 0) {
        return 1;
    } else if (difference > 0) {
        return -1;
    } else {
        return 0;
    }


}
