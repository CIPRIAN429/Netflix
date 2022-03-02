#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seriale.h"


void afis(void * element, FILE *g)
{
    AQ  Serial = (AQ) element;
    AQ  coada = (AQ) Serial->ic->info;
    serial * ser= (serial*) coada->ic->info;
    fprintf(g, "(%s, %0.1f)", ser->nume, ser->rating);
}

int cmp(void *e1, void *e2)
{
    AQ coada1 = (AQ) e1;
    AQ coada2 = (AQ) e2;
    AQ coada12 = (AQ) coada1->ic->info;
    AQ coada22 = (AQ) coada2->ic->info;
    serial * Serial1 = (serial *) coada12->ic->info;
    serial * Serial2 = (serial *) coada22->ic->info;

    if(Serial1->rating < Serial2->rating)
        return 1;

    if(Serial1->rating == Serial2->rating && strcmp(Serial1->nume, Serial2->nume) > 0)
        return 1;

    return -1;
    
}
int cmp_egalitate(void *e1, void *e2)
{
    AQ coada1 = (AQ) e1;
    AQ coada12 = (AQ) coada1->ic->info;
    serial * Serial1 = (serial *) coada12->ic->info;
    char * Nume = (char*) e2;
    
    if(strcmp(Serial1->nume, Nume) == 0)
        return 1;

    return 0;

}
int vizionareC(void *e1, int durata)
{
    AQ coada1 = (AQ) e1;
    AQ coada12 = (AQ) coada1->sc->info;
    serial * Serial1 = (serial *) coada12->sc->info;
    Serial1->total_minute -= durata;

    if(Serial1->total_minute <= 0)
        return 1;

    return 0;
}

void sezon(void *e1, void *e2)
{
    AQ coada1 = (AQ) e1;
    AQ coada2 = (AQ) e2;
    AQ coada12 = (AQ) coada1->sc->info;
    AQ coada22 = (AQ) coada2->sc->info;
    serial * Serial1 = (serial *) coada12->sc->info;
    serial * Serial2 = (serial *) coada22->sc->info;
    Serial2->total_minute += Serial1->total_minute;
    InsQnevida(coada1, coada2->sc->info); 
}

void sezonS(void *e1, void *e2)
{
    AQ coada1 = (AQ) e1;
    AQ coada2 = (AQ) e2;
    ACel a = coada1->ic;
    ACel b = coada2->ic;

    while(coada1->ic->urm != NULL)
        coada1->ic = coada1->ic->urm;

    while(coada2->ic->urm != NULL)
        coada2->ic = coada2->ic->urm;

    AQ coada12 = (AQ) coada1->ic->info;
    AQ coada22 = (AQ) coada2->ic->info;
    serial * Serial1 = (serial *) coada12->sc->info;
    serial * Serial2 = (serial *) coada22->sc->info;
    Serial2->total_minute += Serial1->total_minute;
    InsQnevida(coada12, coada22->sc->info);
    coada1->ic = a;
    coada2->ic = b;
}

char* Nume(void *e1)
{
    AQ coada1 = (AQ) e1;
    AQ coada12 = (AQ) coada1->ic->info;
    serial * Serial1 = (serial *) coada12->ic->info;

    return Serial1->nume;
}
int vizionareS(void *e1, int durata)
{
    AQ stiva1 = (AQ) e1;
    ACel a = stiva1->ic;

    while(stiva1->ic->urm != NULL)
        stiva1->ic = stiva1->ic->urm;

    AQ coada12 = (AQ) stiva1->ic->info;
    serial * Serial1 = (serial *) coada12->sc->info;
    Serial1->total_minute -= durata;
    stiva1->ic = a;

    if(Serial1->total_minute <= 0)
        return 1;

    return 0;
}

