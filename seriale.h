#ifndef _SERIAL_
#define _SERIAL_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "queue.h"
#include "stack.h"



typedef struct serial {
    int ID;
    char *nume;
    float rating;
    int total_minute;
} serial;



void afis(void * , FILE *);
int cmp(void *, void *);
int cmp_egalitate(void *, void *);
char* Nume(void *e1);
int vizionareC(void *, int); /* vizioneaza x minute din coada */
int vizionareS(void *, int); /* vizioneaza x minute din stiva */
void sezon(void *e1, void *e2); /* insereaza sezon in lista */
void sezonS(void *e1, void *e2); /* insereaza sezon in stiva */

#endif