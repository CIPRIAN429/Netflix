#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "tlg.h"
#include "seriale.h"

int Ins_sezonS(ASt s, AQ c, void * ae, TFCmp f)
{
    ACelSt b;
    b = VF(s);

    while(VF(s)->urm != NULL)
    {
        if(f(s->vf->info, ae) == 1)
            sezonS(s->vf->info, c);

        VF(s) = VF(s)->urm;
    }

    if(f(s->vf->info, ae) == 1)
        sezonS(s->vf->info, c);
    
    VF(s) = b;

    return 1;
}

int main(int argc, char **argv) {

FILE *f = fopen(argv[1], "r");
FILE *g = fopen(argv[2], "w");
TLG tendinte = NULL;
TLG documentare = NULL;
TLG tutoriale_C = NULL;
TLG top10 = NULL;
AQ watch_later = malloc(sizeof(TCoada));

if(!watch_later)
    return 0;

watch_later->ic = NULL;
watch_later->sc = NULL;
watch_later->dime = sizeof(TCoada);
ASt currently_watching = InitS(sizeof(TStiva));

if(!currently_watching)
    printf("\nEROARE ALOCARE!!!\n");

ASt history = InitS(sizeof(TStiva));

if(!currently_watching)
    printf("\nEROARE ALOCARE!!!\n");

int poz_watch_later = 0;
char * line = NULL;
size_t len = 0;
int i, j;

while (getline(&line, &len, f) != -1)
{
    char * comanda = strtok(line, " ");

    if(strcmp(comanda, "add") == 0)
        {
            char * id = strtok(NULL, " ");
            char * nume = strtok(NULL, " ");
            char * rating = strtok(NULL, " ");
            char * sezoane = strtok(NULL, " ");

            int Id = atoi(id);
            int s = atoi(sezoane);
            AQ sez = malloc(sizeof(TCoada));

            if(!sez)
                printf("\nEROARE ALOCARE!!!\n");

            serial * Serial = malloc(sizeof(serial));

            if(!Serial)
                printf("\nEROARE ALOCARE!!!\n");

            int total = 0;

            for(i = 1; i <= s; i++)
            {
                char * episoade = strtok(NULL, " ");
                int e = atoi(episoade);
                AQ episodes = malloc(sizeof(TCoada));

                if(!episodes)
                    printf("\nEROARE ALOCARE!!!\n");

                for(j = 1; j <= e; j++)
                {
                    char * durata = strtok(NULL, " ");

                    if (durata[strlen(durata) - 1] == '\n')
			            durata[strlen(durata) - 1] = '\0';

		            if (durata[strlen(durata) - 1] == '\r')
			            durata[strlen(durata) - 1] = '\0';
                    
                    Serial->ID = atoi(id);
                    Serial->nume = malloc(32 * sizeof(char));

                    if(!Serial->nume)
                        printf("\nEROARE ALOCARE!!!\n");
                
                    
                    strcpy(Serial->nume, nume);
                    Serial->rating = atof(rating);
                    total += atoi(durata);
        
                    if(j == e && i == s)
                        Serial->total_minute = total;

                    if(j == 1)
                        InsQvida(episodes, Serial);
                    else
                        InsQnevida(episodes, Serial);
                }
            
                if(i == 1)
                    InsQvida(sez, episodes);
                else
                    InsQnevida(sez, episodes);
            }
            if(Id == 1)
            {
                int pozitie = InsLG(&tendinte, sez, cmp);
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", nume, pozitie);
            }
           
            if(Id == 2)
            {
                int pozitie = InsLG(&documentare, sez, cmp);
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", nume, pozitie);
            }
           
            if(Id == 3)
            {
                int pozitie = InsLG(&tutoriale_C, sez, cmp);
                fprintf(g, "Serialul %s a fost adaugat la pozitia %d.\n", nume, pozitie);
            }
        }

    if(strcmp(comanda, "show") == 0)
    {
        char * categorie = strtok(NULL, " ");

        if (categorie[strlen(categorie) - 1] == '\n')
			categorie[strlen(categorie) - 1] = '\0';

		if (categorie[strlen(categorie) - 1] == '\r')
			categorie[strlen(categorie) - 1] = '\0';

        if(strcmp(categorie, "1") == 0)
        {
            fprintf(g, "Categoria 1: [");
            Afisare(&tendinte, afis, g);
            fprintf(g, "].\n");
        }
       
        if(strcmp(categorie, "2") == 0)
        {
            fprintf(g, "Categoria 2: [");
            Afisare(&documentare, afis, g);
            fprintf(g, "].\n");
        }
        if(strcmp(categorie, "3") == 0)
        {
            fprintf(g, "Categoria 3: [");
            Afisare(&tutoriale_C, afis, g);
            fprintf(g, "].\n");
        }

        if(strcmp(categorie, "top10") == 0)
        {
            fprintf(g, "Categoria top10: [");
            Afisare(&top10, afis, g);
            fprintf(g, "].\n");
        }

        if(strcmp(categorie, "later") == 0)
        {
            fprintf(g, "Categoria later: [");
            if(watch_later->ic != NULL)
                AfisareC(watch_later, g);
            fprintf(g, "].\n");

        }

        if(strcmp(categorie, "watching") == 0)
        {
            fprintf(g, "Categoria watching: [");
            if(currently_watching->vf != NULL)
                AfisareS(currently_watching, g);
            fprintf(g, "].\n");
        }

        if(strcmp(categorie, "history") == 0)
        {
            fprintf(g, "Categoria history: [");
            if(history->vf != NULL)
                AfisareS(history, g);
            fprintf(g, "].\n");
        } 
    }

    if(strcmp(comanda, "later") == 0)
    {
        char * nume = strtok(NULL, " ");

        if (nume[strlen(nume) - 1] == '\n')
			nume[strlen(nume) - 1] = '\0';

		if (nume[strlen(nume) - 1] == '\r')
			nume[strlen(nume) - 1] = '\0';
            
        MutaC(&tendinte, nume, cmp_egalitate, watch_later, &poz_watch_later);
        MutaC(&documentare, nume, cmp_egalitate, watch_later, &poz_watch_later);
        MutaC(&tutoriale_C, nume, cmp_egalitate, watch_later, &poz_watch_later);
        MutaC(&top10, nume, cmp_egalitate, watch_later, &poz_watch_later);
        fprintf(g, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", nume, poz_watch_later);

    }

    if(strcmp(comanda, "add_top") == 0)
    {
        char * poz = strtok(NULL, " ");
        char * nume = strtok(NULL, " ");
        char * rating = strtok(NULL, " ");
        char * sezoane = strtok(NULL, " ");

        int Poz = atoi(poz);
        int s = atoi(sezoane);
        AQ sez = malloc(sizeof(TCoada));

        if(!sez)
            printf("\nEROARE ALOCARE!!!\n");

        serial * Serial = malloc(sizeof(serial));

        if(!Serial)
            printf("\nEROARE ALOCARE!!!\n");

        int total = 0;

        for(i = 1; i <= s; i++)
        {
            char * episoade = strtok(NULL, " ");
            int e = atoi(episoade);
            AQ episodes = malloc(sizeof(TCoada));

            if(!episodes)
                printf("\nEROARE ALOCARE!!!\n");
            
            for(j = 1; j <= e; j++)
            {
                char * durata = strtok(NULL, " ");

                Serial->nume = malloc(35 * sizeof(char));

                if(!Serial->nume)
                    printf("\nEROARE ALOCARE!!!\n");

                strcpy(Serial->nume, nume);
                Serial->rating = atof(rating);
                total += atoi(durata);
                Serial->total_minute = 0;
                
                if(j == e && i == s)
                    Serial->total_minute = total;
                if(j == 1)
                    InsQvida(episodes, Serial);
                else
                    InsQnevida(episodes, Serial);
            }

            if(i == 1)
                InsQvida(sez, episodes);
            else
                InsQnevida(sez, episodes);

            }
        Ins_top10(&top10, sez, Poz);
        fprintf(g, "Categoria top10: [");
        Afisare(&top10, afis,  g);
        fprintf(g, "].\n");
    }

    if(strcmp(comanda, "add_sez") == 0)
    {
        char * nume = strtok(NULL, " ");
        char * episoade = strtok(NULL, " ");
        int ep = atoi(episoade);
        AQ sezon = malloc(sizeof(TCoada));

        if(!sezon)
            printf("\nEROARE ALOCARE!!!\n");

        AQ episodes = malloc(sizeof(TCoada));

        if(!episodes)
            printf("\nEROARE ALOCARE!!!\n");

        int total = 0;
        serial * Serial = malloc(sizeof(serial));

         if(!Serial)
            printf("\nEROARE ALOCARE!!!\n");

        for(i = 1; i <= ep; i++)
        {
            char * durata = strtok(NULL, " ");

            if (durata[strlen(durata) - 1] == '\n')
			    durata[strlen(durata) - 1] = '\0';

		    if (durata[strlen(durata) - 1] == '\r')
			    durata[strlen(durata) - 1] = '\0';

            
            Serial->nume = malloc(35 * sizeof(char));

            if(!Serial->nume)
                printf("\nEROARE ALOCARE!!!\n");

            strcpy(Serial->nume, nume);
            total += atoi(durata);

            if(i == ep)
                Serial->total_minute = total;

            if(i == 1)    
                InsQvida(episodes, Serial);
            else
                InsQnevida(episodes, Serial);

        }

        InsQvida(sezon, episodes);
        Ins_sezonL(&tendinte, sezon, nume, cmp_egalitate);
        Ins_sezonL(&documentare, sezon, nume, cmp_egalitate);
        Ins_sezonL(&tutoriale_C, sezon, nume, cmp_egalitate);
        Ins_sezonL(&top10, sezon, nume, cmp_egalitate);

        if(watch_later->ic != NULL)
            Ins_sezonC(watch_later, sezon, nume, cmp_egalitate);

        if(currently_watching->vf != NULL)
            Ins_sezonS(currently_watching, sezon, nume, cmp_egalitate);
    
        fprintf(g, "Serialul %s are un sezon nou.\n", nume);
    }

    if(strcmp(comanda, "watch") == 0)
    {
        char * nume = strtok(NULL, " ");
        char * durata = strtok(NULL, " ");

        if (durata[strlen(durata) - 1] == '\n')
			durata[strlen(durata) - 1] = '\0';

		if (durata[strlen(durata) - 1] == '\r')
			durata[strlen(durata) - 1] = '\0';

        int Durata = atoi(durata), l = 0;
        l += MutaS(&tendinte, nume, cmp_egalitate,  currently_watching, history, Durata, g);
        l += MutaS(&documentare, nume, cmp_egalitate,  currently_watching, history, Durata, g);
        l += MutaS(&tutoriale_C, nume, cmp_egalitate,  currently_watching, history, Durata, g);
        l += MutaS(&top10, nume, cmp_egalitate,  currently_watching, history, Durata, g);
       
        if (l == 0 )
        {   
            AQ aux = malloc(sizeof(TCoada));

            if(!aux)
                printf("\nEROARE ALOCARE!!!\n");

            aux->ic = NULL;
            
            while(watch_later->ic != NULL)
            { 
                void * c = malloc(sizeof(TCoada));

                if(!c)
                    printf("\nEROARE ALOCARE!!!\n");

                Extragere(watch_later, c);

                if(cmp_egalitate(c, nume) == 1)
                {  
                    if(vizionareC(c, Durata) == 0)
                    {
                        Push(currently_watching, c);
                    }
                    else
                    {
                        Push(history, c);
                        fprintf(g, "Serialul %s a fost vizionat integral.\n", Nume(c));
                    }

                    l = 1;
                }
                else
                    if(aux->ic == NULL)
                        InsQvida(aux, c);
                    else
                        InsQnevida(aux, c);
            }

            if(l == 1)
                poz_watch_later--;

            if(aux->ic != NULL)
                ConcatQ(watch_later, aux);  
        }
       
        if(l == 0)
        {
            ASt aux = InitS(sizeof(TStiva));

            if(!aux)
                printf("\nEROARE ALOCARE!!!\n");

            ASt adresa;

            while(currently_watching->vf != NULL)
            { 
                void * s = malloc(100*sizeof(TStiva));

                if(!s)
                    printf("\nEROARE ALOCARE!!!\n");

                Pop(currently_watching, s);
                if(cmp_egalitate(s, nume) == 1)
                {   
                    if(vizionareS(s, Durata) == 0)
                    {
                        adresa = s;
                        l = 1;
                    } 
                    else
                    {
                        Push(history, s);
                        fprintf(g, "Serialul %s a fost vizionat integral.\n", Nume(s));
                    }
                }
                else
                { 
                    Push(aux, s);
                }
            }
            
            Rastoarna(currently_watching, aux);

            if(l == 1)
                Push(currently_watching, adresa);
           
        }
    }
}

fclose(f);
fclose(g);

return 0;
}