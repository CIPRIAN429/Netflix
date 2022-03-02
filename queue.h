#ifndef _QUEUE_
#define _QUEUE_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "seriale.h"


typedef struct cel {  /* dimensiune variabila */
    struct cel * urm;
    void* info;
} TCel, *ACel;

typedef struct coada {
    int dime; /* dim.element */
    ACel ic, sc; /* adr.prima, ultima celula */
} TCoada, *AQ;

#define IC(a) (((AQ)(a))->ic)
#define SC(a) (((AQ)(a))->sc)
#define DIMEC(a) (((AQ)(a))->dime)

typedef int (*TFCmp)(void*, void*);

void AfisareC(void *, FILE *);
int InsQvida(void* c, void* ae);
int InsQnevida(void* c, void* ae);
void Ins_sezonC(void * c, AQ coada, void *ae, TFCmp f);
void Extragere(void* a, void* ae);
void ConcatQ(void *d, void *s);
void ResetC(void* c);
void DistrC(void** c);

#endif