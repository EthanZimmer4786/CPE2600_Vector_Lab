//
// Created by zimmere on 9/29/26.
//

#ifndef CPE2600_STORAGE_H
#define CPE2600_STORAGE_H

#include <stdio.h>
#include "vect.h"

#define VECTOR_CHUNK 4

extern int add_vect(char name[MAX_NAME], vect3 vect);

extern int get_vect(char name[MAX_NAME], vect3 *vect);

extern void list_vect();

extern void clear_vect();

extern int vect_from_csv(FILE* csv);

extern int vect_to_csv(FILE* csv);


#endif //CPE2600_STORAGE_H
