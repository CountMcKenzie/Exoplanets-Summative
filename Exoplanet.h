#ifndef EXOPLANET_H
#define EXOPLANET_H

typedef struct ExoplanetStruct Exoplanet;

/******************************************************************************

Function    : exoplanet_parse

Parameters  : const char *str - A constant character array that contains a line from
                                exoplanets.txt as its value

Returns     : *Exoplanet - A pointer to an Exoplanet structure that contains the line parsed
                           as a parameter as individual values within the structure

Description : takes a line parsed in from exoplanets.txt, seperates them via the comma delimiter
              and assigns them to their respective values within an Exoplanet structure

******************************************************************************/

Exoplanet *exoplanet_parse(const char *str);

/******************************************************************************

Function    : exoplanet_free

Parameters  : Exoplanet *planet - A pointer to an explanet structure

Returns     : void

Description : frees the memory allocated at the given address specified by the 
              parameter

******************************************************************************/

void exoplanet_free(Exoplanet *planet);


 /******************************************************************************

Function    : exoplanet_toString

Parameters  : Exoplanet *planet - A pointer to an explanet structure

Returns     : const char*, a pointer to read only allocated memory.

Description : given a pointer to a planet structure, return a string variable that
              is in the form of its line in exoplanets.txt

Notes       : static used as deemed more efficient for given use-case. overwritten
              in the data-segmant on subsequent calls of function

******************************************************************************/

const char* exoplanet_toString(const Exoplanet *planet);

/********************************************************************
 
Getter function definitions

 ********************************************************************/

const char* exoplanet_getName(const Exoplanet *planet);

const char* exoplanet_getSystem(const Exoplanet *planet);

const char* exoplanet_getMethod(const Exoplanet *planet);

int exoplanet_getYear(const Exoplanet *planet);

const char* exoplanet_getFacility(const Exoplanet *planet);

double exoplanet_getRadius(const Exoplanet *planet);

double exoplanet_getMass(const Exoplanet *planet);

int exoplanet_getTemperature(const Exoplanet *planet);

double exoplanet_getHabitability(const Exoplanet *planet);

/********************************************************************
 
Setter Function definition

 ********************************************************************/

void exoplanet_setHabitability(Exoplanet *planet, double habitability);

/********************************************************************
 
Function : exoplanet_descendingByHabitability

Parameters : a&, b& - 2 constant pointers to Exoplanet structures

Output : integer value, 
    > 1: if Exoplanet at &a should appear after Exoplanet at &b
    < 1: if Exoplanet at &b should appear after Exoplanet at &a
      0: if Exoplanet at &a and Exoplanet at &b have the same habitability

 ********************************************************************/

int exoplanet_descendingByHabitability(const Exoplanet *a, const Exoplanet *b);

#endif