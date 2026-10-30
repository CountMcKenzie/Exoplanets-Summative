/******************************************************************************

File        : ExoplanetTest.c

Description : Tests that the Exoplanet ADT keeps its information intact:
              information parsed from a line of exoplanets.txt, and
              information changed afterwards using exoplanet_setHabitability.

Build       : gcc -Wall -o exoplanetTest ExoplanetTest.c Exoplanet.c -lm

Run         : ./exoplanetTest
              (run it from the folder that contains exoplanets.txt)

******************************************************************************/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Exoplanet.h"

// two doubles closer together than this are treated as equal

#define TOLERANCE (1e-9)

// lines in the same format as exoplanets.txt, used as test data

#define LINE_HABITABLE       "\"WASP-148 b\", \"WASP-148\", \"Transit\", 2020, \"SuperWASP-North\", 8.093, 92.489, 940, 0.8776"

#define LINE_UNHABITABLE     "\"WASP-148 b\", \"WASP-148\", \"Transit\", 2020, \"SuperWASP-North\", 8.093, 92.489, 940, 0.0000"

// the last number (the habitability) is missing

#define LINE_NO_HABITABILITY "\"WASP-148 b\", \"WASP-148\", \"Transit\", 2020, \"SuperWASP-North\", 8.093, 92.489, 940"

/******************************************************************************

Function    : check

Parameters  : bool condition, const char *errorMessage - condition is whats being checked. if its false
              then output errorMessage

Returns     : int - 1 if it failed, 0 if it was successful. as 1 can easily be added to a fail counter

Description : A wrapper in a sense that provides uniform error evaluation syntax accross all tests given a condition
              and an error message

******************************************************************************/

int check(bool condition, char *errorMessage)
{
   if (!condition)
   {
      printf("%s\n\n", errorMessage);

      return 1;
   }

   return 0;
}

bool nearlyEqual(double a, double b)
{
   return fabs(a - b) < TOLERANCE;
}

/******************************************************************************

The tests - each returns the number of checks that failed (0 means passed)

******************************************************************************/



int testingParsingValidPlanet(void)
{
   int validParseFails = 0;

   Exoplanet *planet = exoplanet_parse(LINE_HABITABLE);

   // reading from a NULL planet would crash the program
   if (planet == NULL)
   {
      validParseFails += check(false, "a valid line should not be NULL ");
   }

   validParseFails += check(strcmp(exoplanet_getName(planet), "WASP-148 b") == 0,
                     "planet name parsed into program deviated from value in file!");

   validParseFails += check(strcmp(exoplanet_getSystem(planet), "WASP-148") == 0,
                     "planet system parsed into program deviated from value in file!");

   validParseFails += check(strcmp(exoplanet_getMethod(planet), "Transit") == 0,
                     "planet method parsed into program deviated from value in file!");

   validParseFails += check(exoplanet_getYear(planet) == 2020,
                     "planet year parsed into program deviated from value in file!");

   validParseFails += check(strcmp(exoplanet_getFacility(planet), "SuperWASP-North") == 0,
                     "planet facility parsed into program deviated from value in file!");

   validParseFails += check(nearlyEqual(exoplanet_getRadius(planet), 8.093),
                     "planet name radius into program deviated from value in file!");

   validParseFails += check(nearlyEqual(exoplanet_getMass(planet), 92.489),
                     "planet mass parsed into program deviated from value in file!");

   validParseFails += check(exoplanet_getTemperature(planet) == 940,
                     "planet temperature parsed into program deviated from value in file!");

   validParseFails += check(nearlyEqual(exoplanet_getHabitability(planet), 0.8776),
                     "planet habitability parsed into program deviated from value in file!");

   exoplanet_free(planet);

   return validParseFails;
}


int testingParsingInvalidPlanet(void)
{
   int invalidParseFails = 0;

   invalidParseFails += check(exoplanet_parse("") == NULL,
                     "parsed line containing empty string and received non-NULL value!");

   invalidParseFails += check(exoplanet_parse("Sample string that is clearly not an Exoplanet or in correct format") == NULL,
                     "parsed line of incorrect format and received non-NULL value!");

   invalidParseFails += check(exoplanet_parse(LINE_NO_HABITABILITY) == NULL,
                     "parsed line with missing habitability and received non-NULL value!");

   invalidParseFails += check(exoplanet_parse("\"WASP-148 b\", \"WASP-148\", \"Transit\", \"twenty-twenty\", \"SuperWASP-North\", 8.093, 92.489, 940, 0.8776") == NULL,
                     "parsed line containing non integer date and received non-NULL value!");

   return invalidParseFails;
}


int testSetHabitability(void)
{
   int habitibilityFails = 0;

   Exoplanet *planet = exoplanet_parse(LINE_UNHABITABLE);

   if (planet == NULL)
   {
      habitibilityFails += check(false, "a valid line should return a non-NULL value");
   }

   exoplanet_setHabitability(planet, 0.123456);

   habitibilityFails += check(nearlyEqual(exoplanet_getHabitability(planet), 0.123456),
                     "set habitibility value has deviated from given input of 0.123456");

   // nothing else should have changed

   habitibilityFails += check(strcmp(exoplanet_getName(planet), "WASP-148 b") == 0,
                     "name of planet has deviated despite only setting habitibility");

   habitibilityFails += check(nearlyEqual(exoplanet_getRadius(planet), 8.093),
                     "radius of planet has deviated despite only setting habitibility");

   habitibilityFails += check(nearlyEqual(exoplanet_getMass(planet), 92.489),
                     "mass of planet has deviated despite only setting habitibility");

   habitibilityFails += check(exoplanet_getTemperature(planet) == 940,
                     "temperature of planet has deviated despite only setting habitibility");

   exoplanet_free(planet);

   return habitibilityFails;
}


int testToString(void)
{
   int toStringFails = 0;

   Exoplanet *planet = exoplanet_parse(LINE_UNHABITABLE);

   if (planet == NULL)
   {
      return check(false, "a valid line should return a non-NULL value");
   }

   toStringFails += check(strcmp(exoplanet_toString(planet), LINE_UNHABITABLE) == 0,
                     "given planet has deviated from text file representation after invoking toString");

   exoplanet_setHabitability(planet, 0.8776);

   toStringFails += check(strcmp(exoplanet_toString(planet), LINE_HABITABLE) == 0,
                     "given planet has deviated from text file representation after invoking toString and setting habitability");

   exoplanet_free(planet);

   return toStringFails;
}

// Every line of exoplanets.txt must parse, and toString must give back
// exactly the same line.  Stops at the first line that fails, so one mistake
// does not print hundreds of messages.

int testDataFile(void)
{
   FILE *fd = fopen("exoplanets.txt", "r");

   if (fd == NULL)
   {
      return check(false, "failed to open exoplanets.txt");
   }

   char line[450];

   int lineNumber = 0;
   int datasetFails   = 0;

   while (datasetFails == 0 && fgets(line, sizeof(line), fd) != NULL)
   {
      lineNumber++;

      Exoplanet *planet = exoplanet_parse(line);

      if (planet == NULL)
      {
         printf("line %d of exoplanets.txt did not parse\n", lineNumber);

         datasetFails++;
      }
      else
      {
         // strcspn gives the position of the first CR or LF in the line, and
         // writing '\0' there cuts them off so the line can be compared

         line[strcspn(line, "\r\n")] = '\0';

         const char *text = exoplanet_toString(planet);

         if (strcmp(text, line) != 0)
         {
            printf("line %d, toString does not match the line\n", lineNumber);
            printf("expected: %s\n", line);
            printf("actual  : %s\n\n", text);

            datasetFails++;
         }

         exoplanet_free(planet);
      }
   }

   fclose(fd);

   datasetFails += check(lineNumber > 0, "exoplanets.txt should not be empty");

   return datasetFails;
}

/******************************************************************************

Function    : main

Parameters  : void

Returns     : int - Macro indicating success factor

Description : Run all the tests, then say weather everything passed.

******************************************************************************/

int main(void)
{
   int totalFails = 0;

   totalFails += testingParsingValidPlanet();
   totalFails += testingParsingInvalidPlanet();
   totalFails += testSetHabitability();
   totalFails += testToString();
   totalFails += testDataFile();

   if (totalFails == 0)
   {
      printf("All tests passed\n");

      return EXIT_SUCCESS;
   }

   printf("%d check(s) failed!\n", totalFails);

   return EXIT_FAILURE;
}

/*****************************************************************************/