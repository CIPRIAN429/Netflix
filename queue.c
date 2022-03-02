#include "queue.h"

int InsQvida(void* c, void* ae)
{
//coada vida
    ACel aux;
    aux = (ACel) malloc(sizeof(TCel));
    aux->info = ae; //ae e alocata per element
    aux->urm = NULL;
    IC(c) = aux; SC(c) = aux;
    return 1;
}

int InsQnevida(void* c, void* ae)
{
//coada nevida
    ACel aux;
    aux = (ACel) malloc(sizeof(TCel));
    aux->info = ae; //ae e alocata per element
    aux->urm = NULL;
    SC(c)->urm = aux;
    SC(c) = aux;
    return 1;
}

void AfisareC(void * c, FILE *g)
{
    ACel b;
    b = IC(c);

    while(IC(c) != SC(c))
    {
        AQ  Serial = (AQ) c;
        AQ  coada = (AQ) Serial->ic->info;
        AQ  coada2 = (AQ) coada->ic->info;
        serial * ser= (serial*) coada2->ic->info;
        fprintf(g, "(%s, %0.1f), ", ser->nume, ser->rating);
        IC(c) = IC(c)->urm;
    }

    AQ  Serial = (AQ) c;
    AQ  coada = (AQ) Serial->ic->info;
    AQ  coada2 = (AQ) coada->ic->info;
    serial * ser= (serial*) coada2->ic->info;
    fprintf(g, "(%s, %0.1f)", ser->nume, ser->rating);
    IC(c) = b; 
}

void Ins_sezonC(void * c, AQ coada, void *ae, TFCmp f)
{

    ACel b;
    b = IC(c);

    while(IC(c) != SC(c))
    {
        AQ  Serial = (AQ) c;
        AQ  coada2 = (AQ) Serial->ic->info;

        if(f(coada2, ae) == 1)
        {
            AQ  coada3 = (AQ) coada2->sc->info;
            serial * ser= (serial*) coada3->sc->info;
            AQ  coada4 = (AQ) coada->sc->info;
            serial * ser2= (serial*) coada4->sc->info;
            ser2->total_minute += ser->total_minute;
            InsQnevida(coada2, coada->sc->info);
        }

        IC(c) = IC(c)->urm;
    }

    AQ  Serial = (AQ) c;
    AQ  coada2 = (AQ) Serial->ic->info;

    if(f(coada2, ae) == 1)
    {
        AQ  coada3 = (AQ) coada2->sc->info;
        serial * ser= (serial*) coada3->sc->info;
        AQ  coada4 = (AQ) coada->sc->info;
        serial * ser2= (serial*) coada4->sc->info;
        ser2->total_minute += ser->total_minute;
        InsQnevida(coada2, coada->sc->info);
    }

    IC(c) = b;
}

void Extragere(void* a, void* ae)
{
    ACel aux = IC(a);
    aux = IC(a);
    IC(a) = aux->urm;
    memcpy(ae, aux->info, DIMEC(a)); 
    free(aux);
    free(aux->info);
    if(IC(a) == NULL)
        SC(a) = NULL;
}

void ConcatQ(void *d, void *s)
{
    IC(d) = IC(s);
    SC(d) = SC(s);
}

void ResetC(void* c)
{
    ACel aux, p;
    aux = IC(c);

    while (aux)
    {
        p = aux;
        aux = aux->urm;
        free(p->info);
        free(p);
    }

    IC(c) = NULL;
}

void DistrC(void** c)
{
    ResetC(*c);
    free(*c);
    *c = NULL;
}