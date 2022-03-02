#ifndef _STACK_
#define _STACK_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "seriale.h"


typedef struct celst {
	struct celst *urm; /* adr.urmatoarei celule */
	void* info; /* adresa informatie */
} TCelSt, *ACelSt;
typedef struct stiva {
	int dime; /* dim.element */
	ACelSt vf; /* adresa celulei din varf */
} TStiva, *ASt;

#define VF(a) (((ASt)(a))->vf)
#define DIMES(a) (((ASt)(a))->dime)

void* InitS(int d);
int Push(void* s, void* ae);
int Pop(void* s, void* ae);
void AfisareS(void * a, FILE *g); /* afiseaza stiva */
int Rastoarna (void *ad, void *as);
void ResetS(void* s);
void DistrS(void** s);

#endif