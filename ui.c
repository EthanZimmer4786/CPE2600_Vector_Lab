/****************************************
* Filename: ui.c
* Brief: User interaction for vector program
* Author: Ethan Zimmer
* Created: 9/29/2026
****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ui.h"
#include "storage.h"
#include "vect_math.h"

#define MAX_INPUT 80
#define MAX_TOKENS 5

static void print_vect(const vect3 vect)
{
    printf("%f %f %f\n", vect.x, vect.y, vect.z);
}

static vect3 parse_operation(char a[MAX_NAME], char op, char b[MAX_NAME])
{
    vect3 vectA;
    vect3 vectB;
    double scalar;

    vect3 result = {.x=0.0f, .y=0.0f, .z=0.0f};

    switch (op)
    {
    case '+':
    case '-':
        // Get vectors by name
        if (!get_vect(a, &vectA))
        {
            printf("No vector found for %s\n", a);
            break;
        }
        if (!get_vect(b, &vectB))
        {
            printf("No vector found for %s\n", b);
            break;
        }

        if (op == '+')
        {
            result =  add(vectA, vectB);
            break;
        }
        if (op == '-')
        {
            result = sub(vectA, vectB);
            break;
        }

    case '*':
        if (!get_vect(a, &vectA))
        {
            printf("No vector found for %s\n", a);
            break;
        }

        scalar = atof(b);

        result = mul(vectA, scalar);
        break;

    case '=':
        char name[MAX_NAME];

        strcpy(name, a);

        if (!get_vect(b, &vectB))
        {
            printf("No vector found for %s\n", b);
            break;
        }

        add_vect(name, vectB);

        result = vectB;
        break;


    default:
        printf("Operator %c not recognized\n", op);
    }

    return result;
}

extern int parse_command()
{
    char command[MAX_INPUT] = {0};
    char *tokens[MAX_TOKENS];
    int n_tokens = 0;

    // Print prompt
    printf("> ");

    // Get command from console
    fgets(command, MAX_INPUT, stdin);

    // Replace new line with terminator
    command[strcspn(command, "\n")] = '\0';

    // Parse tokens
    char *token = strtok(command, " ");
    while (token != NULL && n_tokens < MAX_TOKENS) {
        tokens[n_tokens] = token;
        n_tokens++;

        token = strtok(NULL, " ");
    }

    switch (n_tokens)
    {
        case 1:
            if (strcmp(tokens[0], "quit") == 0)
            {
                clear_vect();
                return -1;
            }
            if (strcmp(tokens[0], "clear") == 0)
            {
                clear_vect();
                break;
            }
            if (strcmp(tokens[0], "list") == 0)
            {
                list_vect();
                break;
            }
            // Assume token is a vector name
            vect3 vect;

            if (get_vect(tokens[0], &vect))
            {
                print_vect(vect);
            } else
            {
                printf("No vector found for %s\n", tokens[0]);
            }

            break;

        case 2:
            if (strcmp(tokens[0], "save") == 0)
            {
                FILE* file = fopen(tokens[1], "w");
                if (vect_to_csv(file))
                {
                    printf("Failed to save file\n");
                }
                fclose(file);
                break;
            }

            if (strcmp(tokens[0], "load") == 0)
            {
                // Get last dot in file path
                char* dot_ptr = strrchr(tokens[1], '.');

                if (dot_ptr != NULL)
                {
                    // Copy the extension to a variable
                    char extension[3];
                    strcpy(extension, dot_ptr + 1);

                    // Check if extension is a csv
                    if (strcmp(extension, "csv") == 0)
                    {
                        FILE* file = fopen(tokens[1], "r");
                        if (file != NULL)
                        {
                            const int status = vect_from_csv(file);

                            fclose(file);

                            if (status >= 0) {
                                printf("Loaded %d vectors\n", status);
                                break;
                            }
                            printf("Failed loading vectors from %s\n", tokens[1]);
                            break;
                        }
                        printf("Could not open file %s\n", tokens[1]);
                        break;
                    }
                    printf("File %s must be a .csv\n", tokens[1]);
                    break;
                }
                printf("Could not locate file extension in %s\n", tokens[1]);
                break;
            }
            break;

        case 3:
            print_vect(parse_operation(tokens[0], tokens[1][0], tokens[2]));
            break;

        case 5:
            char name[MAX_NAME];
            vect3 result;

            strcpy(name, tokens[0]);

            char op = tokens[3][0];
            if (op == '+' || op == '-' || op == '*')
            {
                result = parse_operation(tokens[2], tokens[3][0], tokens[4]);
                print_vect(result);
            } else
            {
                result.x = atof(tokens[2]);
                result.y = atof(tokens[3]);
                result.z = atof(tokens[4]);
            }

            add_vect(name, result);
            break;

        default:
            printf("Unable to parse command\n");
    }
    return 0;
}