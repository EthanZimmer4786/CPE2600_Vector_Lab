//
// Created by zimmere on 9/29/26.
//

#ifndef CPE2600_STORAGE_H
#define CPE2600_STORAGE_H

#include "vect.h"

#define MAX_VECTORS 10
#define MAX_NAME 8

extern void add_vect(char name[MAX_NAME], vect3 vect);

extern int get_vect(char name[MAX_NAME], vect3 *vect);

extern void list_vect();


#endif //CPE2600_STORAGE_H
