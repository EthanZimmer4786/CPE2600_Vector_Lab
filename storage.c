/****************************************
* Filename: storage.c
* Brief: Provides functions to manage the vector storage
* Author: Ethan Zimmer
* Created: 9/29/2026
****************************************/

#include <string.h>
#include <stdio.h>
#include "storage.h"
#include "vect.h"

static vect3 vectors[MAX_VECTORS] = {0};
static char names[MAX_VECTORS][MAX_NAME + 1] = {0};

extern void add_vect(char name[MAX_NAME], const vect3 vect)
{
    // Iterate over vectors
    int i;
    for (i = 0; i < MAX_VECTORS; i++)
    {
        // If no name defined at this index then set name and vector
        if (names[i][0] == '\0')
        {
            strcpy(names[i], name);
            vectors[i] = vect;
            break;
        }
        // If name already stored then overwrite vector
        if (strcmp(names[i], name) == 0)
        {
            vectors[i] = vect;
            break;
        }
    }

    if (i == MAX_VECTORS)
    {
        printf("Already storing the maximum number of vectors: %d\n", MAX_VECTORS);
    }
}

extern void list_vect()
{
    for (int i = 0; i < MAX_VECTORS; i++)
    {
        printf("%s: %lf %lf %lf\n", names[i], vectors[i].x, vectors[i].y, vectors[i].z);
    }
}

extern int get_vect(char name[MAX_NAME], vect3 *vect)
{
    bool found = false;
    for (int i = 0; i < MAX_VECTORS; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            *vect = vectors[i];
            found = true;
            break;
        }
    }

    return found;
}