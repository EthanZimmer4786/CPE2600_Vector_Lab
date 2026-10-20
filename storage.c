/****************************************
* Filename: storage.c
* Brief: Provides functions to manage the vector storage
* Author: Ethan Zimmer
* Created: 9/29/2026
****************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "vect.h"

static linkedVect* root;
static linkedVect* link_ptr;

static linkedVect* next()
{
    link_ptr = link_ptr->next;
    return link_ptr;
}

static int allocate_vect(linkedVect** vect)
{
    linkedVect* ptr = malloc(sizeof(linkedVect));

    if (ptr != NULL)
    {
        ptr->next = NULL;
        ptr->prev = NULL;
        *vect = ptr;
        return 1;
    }

    return 0;
}


extern int add_vect(char name[MAX_NAME], const vect3 vect)
{
    // Create the first node if the list is empty
    if (root == NULL)
    {
        if (!allocate_vect(&root))
        {
            printf("Failed to allocate memory\n");
            return 0;
        }

        root->vect = vect;
        strcpy(root->name, name);
        return 1;
    }

    // Search for an existing node or the end of the list
    linkedVect* ptr = root;

    while (ptr != NULL)
    {
        // Update an existing vector if its name matches
        if (strcmp(ptr->name, name) == 0)
        {
            ptr->vect = vect;
            return 1;
        }

        // Stop at the last node
        if (ptr->next == NULL)
        {
            break;
        }

        ptr = ptr->next;
    }

    // Append a new node
    if (!allocate_vect(&ptr->next))
    {
        printf("Failed to allocate memory for a new vector\n");
        return 0;
    }

    ptr->next->vect = vect;
    strcpy(ptr->next->name, name);
    ptr->next->prev = ptr;

    return 1;
}

extern void list_vect()
{
    link_ptr = root;
    while (link_ptr != NULL)
    {
        vect3 vect = link_ptr->vect;
        printf("%s: %lf %lf %lf\n", link_ptr->name, vect.x, vect.y, vect.z);
        next();
    }
}

extern int get_vect(char name[MAX_NAME], vect3* vect)
{
    link_ptr = root;
    while (link_ptr != NULL)
    {
        if (strcmp(link_ptr->name, name) == 0)
        {
            *vect = link_ptr->vect;
            break;
        }
        next();
    }
    return link_ptr != NULL;
}

extern void clear_vect()
{
    link_ptr = root;
    while (link_ptr != NULL)
    {
        linkedVect* next = link_ptr->next;
        free(link_ptr);
        link_ptr = next;
    }
    root = NULL;
}

extern int vect_from_csv(FILE* csv)
{
    int added = 0;
    char buffer[MAX_CSV_BUFFER] = {0};

    // Read until end of file
    while (fgets(buffer, sizeof(buffer), csv))
    {
        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        char name_tok[MAX_NAME];
        strcpy(name_tok, strtok(buffer, ","));
        const float x = atof(strtok(NULL, ","));
        const float y = atof(strtok(NULL, ","));
        const float z = atof(strtok(NULL, ","));

        // Create vector
        vect3 vect = {.x = x, .y = y, .z = z};

        // Add vector
        add_vect(name_tok, vect);

        added++;
    }

    return added;
}

extern int vect_to_csv(FILE* csv)
{
    link_ptr = root;
    while (link_ptr != NULL)
    {
        const vect3 vect = link_ptr->vect;
        fprintf(csv, "%s,%f,%f,%f\n", link_ptr->name, vect.x, vect.y, vect.z);

        next();
    }

    return 0;
}