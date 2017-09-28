#include "baza.h"
int tytulcomp(const void* a,const void* b)
{
    const linkz *l1 = a,*l2 = b;
    if((*l1)->gra.tytul == 0 && (*l2)->gra.tytul == 0) return 0;
    else if ((*l1)->gra.tytul == 0) return 1;
    else if ((*l2)->gra.tytul == 0) return -1;
    else
        return(strcmp((*l1)->gra.tytul, (*l2)->gra.tytul));
}
/////////////////////////////
void tytulsort(int dir)
{
    linkz* tab;
    int i = 0;
    if(first == NULL) return;
    linkz akt = first;
    tab = malloc(lwez * sizeof(linkz));
    while(akt != 0)
    {
        tab[i] = akt;
        akt = akt->next;
        i++;
    }
    qsort(tab, lwez, sizeof(linkz),  tytulcomp);
    sortuj(tab, dir);
    free(tab);
    wyswietlliste();
}
///////////////////////////
void sortuj(linkz* tab, int dir) //nie jestem pewien czy dobrze szczegolnie ten for
{
    int i;
    linkz akt;

     if(dir >= 0)
        {
        first = tab[0];
        akt = first;
        for(i = 1; i < lwez; i++)
        {
            akt->next = tab[i];
            akt = akt->next;
        }
        last = akt;
        last->next = 0;
    }
    else
    {
        first = tab[lwez-1];
        akt = first;
        for(i = 1; i < lwez; i++)
        {
            akt->next = tab[lwez-i-1];
            akt = akt->next;
        }
        last = akt;
        last->next = 0;
    }
}
/////////////////////////////
int prodcomp(const void* a,const void* b)
{
    const linkz *l1 = a,*l2 = b;
    if((*l1)->gra.producent == 0 && (*l2)->gra.producent == 0) return 0;
    else if ((*l1)->gra.producent == 0) return 1;
    else if ((*l2)->gra.producent == 0) return -1;
    else
        return(strcmp((*l1)->gra.producent, (*l2)->gra.producent));
}
/////////////////////////////
void prodsort(int dir)
{
    linkz* tab;
    int i = 0;
    if(first == NULL) return;
    linkz akt = first;
    tab = malloc(lwez * sizeof(linkz));
    while(akt != 0)
    {
        tab[i] = akt;
        akt = akt->next;
        i++;
    }
    qsort(tab, lwez, sizeof(linkz),  prodcomp);
    sortuj(tab, dir);
    free(tab);
    wyswietlliste();
}
/////////////////////////////
int noscomp(const void* a,const void* b)
{
    const linkz *l1 = a,*l2 = b;
    if((*l1)->gra.nosnik == 0 && (*l2)->gra.nosnik == 0) return 0;
    else if ((*l1)->gra.nosnik == 0) return 1;
    else if ((*l2)->gra.nosnik == 0) return -1;
    else
        return(strcmp((*l1)->gra.nosnik, (*l2)->gra.nosnik));
}
/////////////////////////////
void nossort(int dir)
{
    linkz* tab;
    int i = 0;
    if(first == NULL) return;
    linkz akt = first;
    tab = malloc(lwez * sizeof(linkz));
    while(akt != 0)
    {
        tab[i] = akt;
        akt = akt->next;
        i++;
    }
    qsort(tab, lwez, sizeof(linkz),  noscomp);
    sortuj(tab, dir);
    free(tab);
    wyswietlliste();
}
/////////////////////////////
int platcomp(const void* a,const void* b)
{
    const linkz *l1 = a,*l2 = b;
    if((*l1)->gra.platforma == 0 && (*l2)->gra.platforma == 0) return 0;
    else if ((*l1)->gra.platforma == 0) return 1;
    else if ((*l2)->gra.platforma == 0) return -1;
    else
        return(strcmp((*l1)->gra.platforma, (*l2)->gra.platforma));
}
/////////////////////////////
void platsort(int dir)
{
    linkz* tab;
    int i = 0;
    if(first == NULL) return;
    linkz akt = first;
    tab = malloc(lwez * sizeof(linkz));
    while(akt != 0)
    {
        tab[i] = akt;
        akt = akt->next;
        i++;
    }
    qsort(tab, lwez, sizeof(linkz),  platcomp);
    sortuj(tab, dir);
    free(tab);
    wyswietlliste();
}
/////////////////////////////
int cenacomp(const void* a,const void* b)
{
    const linkz *l1 = a,*l2 = b;
    return ((*l1)->gra.cena - (*l2)->gra.cena);
}
/////////////////////////////
void cenasort(int dir)
{
    linkz* tab;
    int i = 0;
    if(first == NULL) return;
    linkz akt = first;
    tab = malloc(lwez * sizeof(linkz));
    while(akt != 0)
    {
        tab[i] = akt;
        akt = akt->next;
        i++;
    }
    qsort(tab, lwez, sizeof(linkz),  cenacomp);
    sortuj(tab, dir);
    free(tab);
    wyswietlliste();
}
///////////////////////////
