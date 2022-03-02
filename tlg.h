#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "queue.h"
#include "stack.h"
#include "seriale.h"



typedef struct celulag
{
  void *info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG; /* tipurile Celula, Lista  */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*, FILE*);     /* functie afisare/eliberare un element */
typedef void (*TG)(void*);

/* functii lista generica */
int InsLG(TLG*, void*, TFCmp);  /*- inserare la inceput reusita sau nu*/
int Ins_top10(TLG *aL, void *ae, int poz_inserare); /* insereaza in top 10 */
int MutaC(TLG*, void*, TFCmp, AQ, int*); /* muta un serial in watch_later */
int MutaS(TLG *al, void *ae, TFCmp, ASt, ASt, int, FILE *g); /* muta un serial in una din cele 2 stive */
int Ins_sezonL(TLG *al, AQ c, void * ae, TFCmp f); /* insereaza sezon in lista */
void Distruge(TLG* aL, TG); /* distruge lista */
/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(TLG*, TF, FILE *);

#endif
