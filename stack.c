#include "stack.h"

void* InitS(int d)
{
    ASt s;
    s = (ASt)malloc(sizeof(TStiva));

    if(!s)
        return NULL;

    s->dime = d;
    s->vf = NULL;

    return (void*)s;
}

int Push(void* s, void* ae)
{
    ACelSt aux;
    aux = (ACelSt)malloc(sizeof(TCelSt));

    if(!aux)
         return 0;

    aux->info = ae; 
    aux->urm = ((ASt)s)->vf; 
    ((ASt)s)->vf = aux;

    return 1;
}

int Pop(void* s, void* ae)
{
    ACelSt aux = VF(s); //varful stivei

    if(aux == NULL) 
        return 0;

    memcpy(ae, aux->info, DIMES(s));
    VF(s) = aux->urm;
    free(aux);
    free(aux->info);

    return 1;
}

void AfisareS(void * s, FILE *g)
{
    ACelSt b;
    b = VF(s);

    while(VF(s)->urm != NULL)
    {
        ASt  Serial = (ASt) s;
        ASt  stiva = (ASt) Serial->vf->info;
        ASt  stiva2 = (ASt) stiva->vf->info;
        serial * ser= (serial*) stiva2->vf->info;
        fprintf(g, "(%s, %0.1f), ", ser->nume, ser->rating);
        VF(s) = VF(s)->urm;
    }

    ASt  Serial = (ASt) s;
    ASt  stiva = (ASt) Serial->vf->info;
    ASt  stiva2 = (ASt) stiva->vf->info;
    serial * ser= (serial*) stiva2->vf->info;
    fprintf(g, "(%s, %0.1f)", ser->nume, ser->rating);
    VF(s) = b;
}

int Rastoarna (void *d, void *s)
{
    ACelSt p, u;
    p = VF(s);

    while(p)
    {
        u = p->urm;
        p->urm = VF(d);
        VF(d) = p;
        p = u;
    }

    VF(s) = NULL;
    return 1;
}

void ResetS(void* s)
{
    ACelSt aux, p;
    aux = VF(s);

    while (aux)
    {
        p = aux;
        aux = aux->urm;
        free(p->info);
        free(p);
    }

VF(s) = NULL;
}

void DistrS(void** s)
{
    ResetS(*s);
    free(*s);
    *s = NULL;
}