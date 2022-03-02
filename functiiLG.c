#include "tlg.h"

int InsLG(TLG *aL, void* ae, TFCmp f)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	int pozitie = 1;
	TLG p, ant;
	aux->info = ae;
	
	for(ant = NULL, p = *aL; p != NULL; ant = p, p = p->urm)
	{
		if(f(p->info, ae) > 0)
			break;
		pozitie++;
	}
	aux->urm = p;
	if(ant == NULL)
		*aL = aux;
	else
		ant->urm = aux;

	return pozitie;
}

int Ins_top10(TLG *aL, void *ae, int poz_inserare)
{
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;
	int pozitie = 1;
	TLG p, ant;
	aux->info = ae;
	
	for(ant = NULL, p = *aL; p != NULL; ant = p, p = p->urm)
	{
		if(poz_inserare == pozitie)
			break;
		pozitie++;
	}
	aux->urm = p;
	if(ant == NULL)
		*aL = aux;
	else
		ant->urm = aux;
	int pozitie10 = pozitie;
	
	for(; p != NULL; ant = p, p = p->urm)
	{
		pozitie10++;

		if(pozitie10 == 11)
			break;
	}
	if(pozitie10 == 11 && poz_inserare != 10)
		ant->urm = NULL; 

	if(pozitie10 == 11 && poz_inserare == 10)
		ant->urm->urm = NULL;

	return pozitie;
}

int MutaC(TLG *al, void *ae, TFCmp f, AQ c, int *poz)
{
	TLG el, ant;
	for(el = *al, ant = NULL; el != NULL; ant = el, el = el->urm)
	{
		if(f(el->info, ae) == 1)
		{	
			
			TLG aux = el;

			if(ant == NULL)
				*al = el->urm;
			else
				ant->urm = el->urm;

			(*poz)++;

			if(c->ic == NULL)
				InsQvida(c, el->info);
			else
				InsQnevida(c, el->info);
				
			free(aux);

			return 1;
		}
	}
	return 0;
}

int MutaS(TLG *al, void *ae, TFCmp f, ASt watch, ASt history, int durata, FILE *g)
{
	TLG el, ant;

	for(el = *al, ant = NULL; el != NULL; ant = el, el = el->urm)
	{
		if(f(el->info, ae) == 1)
			{	
				TLG aux = el;

				if(ant == NULL)
					*al = el->urm;
				else
					ant->urm = el->urm;

				int v;
				v = vizionareC(el->info, durata);

				if(v == 1)
				{
					Push(history, el->info);
					fprintf(g, "Serialul %s a fost vizionat integral.\n", (char *) ae);
				}
				else
					Push(watch, el->info);

				free(aux);

				return 1;
			}
	}
	return 0;
}

int Ins_sezonL(TLG *al, AQ c, void * ae, TFCmp f)
{
	TLG el;

	for(el = *al; el != NULL; el = el->urm)
	{
		if(f(el->info, ae) == 1)
		{		
			sezon(el->info, c);

			return 1;
		}
	}

	return 0;
}

void Distruge(TLG* aL, TG free_elem) /* distruge lista */
{
	while(*aL != NULL)
    {
        TLG aux = *aL;    
        if (!aux)
            return;

        free_elem(aux->info);  
        *aL = aux->urm;    
        free(aux);   
		
    }
}

void Afisare(TLG* aL, TF afiEL, FILE *g)
{
	if(!*aL) 
    	return;

	for(; *aL; aL = &(*aL)->urm) {
		afiEL((*aL)->info, g);

		if((*aL)->urm)
			fprintf(g, ", ");

    }
}
