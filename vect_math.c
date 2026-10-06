/****************************************
* Filename: vect_math.c
* Brief: Provide basic vector math operations
* Author: Ethan Zimmer
* Created: 9/29/2026
****************************************/

#include "vect_math.h"
#include "vect.h"

extern vect3 add(const vect3 a, const vect3 b)
{
    vect3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

extern vect3 sub(const vect3 a, const vect3 b)
{
    vect3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

extern vect3 mul(const vect3 vect, const double scalar)
{
    vect3 result;
    result.x = vect.x * scalar;
    result.y = vect.y * scalar;
    result.z = vect.z * scalar;
    return result;
}