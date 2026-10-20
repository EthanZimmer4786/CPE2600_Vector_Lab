//
// Created by zimmere on 9/29/26.
//

#ifndef CPE2600_VECT_H
#define CPE2600_VECT_H

#define MAX_NAME 16
#define MAX_CSV_BUFFER 32

typedef struct
{
    double x;
    double y;
    double z;
} vect3;

typedef struct linkedVect{
    vect3 vect;
    char name[MAX_NAME];
    struct linkedVect* next;
    struct linkedVect* prev;
} linkedVect;


#endif //CPE2600_VECT_H
