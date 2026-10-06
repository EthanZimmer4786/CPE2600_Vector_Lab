/****************************************
* Filename: main.c
* Brief: Main file for vector program
* Author: Ethan Zimmer
* Created: 9/29/2026
* Compile: make
****************************************/

#include <stdio.h>
#include <string.h>

#include "ui.h"

int main(int argc, char* argv[])
{
    printf("===== Vector Calculator =====\n\n");

    if (argc > 1  && strcmp(argv[1], "-h") == 0)
    {
        printf("Vectors can be assigned using: name = x y z\n\n"
               "Operations can be applied to vectors using: vect1 + vect2\n"
               "(supported operators are +, -, *, =)\n\n"
               "The result of operations can be assigned to new vectors: newVect = vect1 + vect2\n\n"
               "A maximum of 10 vectors can be defined at any time\n");

        return 0;
    }

    while (1)
    {
        if (parse_command() == -1)
        {
            return 0;
        }
    }
}
