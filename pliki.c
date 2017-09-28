#include "baza.h"
int zapisz(char* nazwa) //dodaj zapisywanie mozliwych do wpisania gatunkow do pliku tez
{
    FILE* plik;
    linkz akt = first;
    int i = 0;
    if((plik = fopen(nazwa, "wb")) == 0)
    {
        puts("nie udalo sie utworzyc pliku"); return -1;
    }

    fputs("7zciiu4hjasd211dx7s8a9wd",plik); fputc('\n', plik);

    for(i = 0;i < lgat; i++) //blad przy nowych gatunkach
    {
        printf("zapisuje: %s\n", gatunki[i]);
        fputs(gatunki[i], plik); putc('\0', plik);
    }
    putc('\n', plik);

    while(akt != 0)
    {
       if(akt->gra.tytul) fputs(akt->gra.tytul, plik); putc('\0', plik);
       if(akt->gra.producent) fputs(akt->gra.producent, plik); putc('\0', plik);
       if(akt->gra.nosnik) fputs(akt->gra.nosnik, plik); putc('\0', plik);
       if(akt->gra.platforma) fputs(akt->gra.platforma, plik); putc('\0', plik);
        fprintf(plik, "%lf", akt->gra.cena); putc('\0', plik);
        for(i = 0;akt->gra.gatunek[i] != 0; i++)
        {
            fputs(akt->gra.gatunek[i], plik); putc('\0', plik);

        }

        putc('\n', plik);
        akt = akt->next;
    }
    fclose(plik);

return 0;
}
//////////////////////////////////////////////
int wczytaj(char* nazwa)
{
   FILE* plik = 0;
    int il = 0;
    if((plik = fopen(nazwa, "rb")) == 0)
    {
//        puts("nie udalo sie otworzyc pliku");
        return -1;
    }

    sdobuf(bufor, 256, plik);
    if(bufor[0] != 0)
        if(strcmp(bufor, "7zciiu4hjasd211dx7s8a9wd") != 0) return -1; //sprawdzanie hasla

    char a;
    while((a = getc(plik)) != '\n') //licze ilosc gatunkow podstawowych
    {
        if(a == 0)
            il++;
    }
    rewind(plik);
    sdobuf(bufor, 256,plik); //przewijanie hasla
    gatunki = malloc((il+5) * sizeof(char*));
    lgat = 0;
    do
    {
        lgat++;
        gatunki[lgat-1] = fwczytajs(plik);
    }while(gatunki[lgat-1] != NULL);
    lgat--;

    linkz prev = 0;
    do
    {
        if(first == 0)
        {
            first = (linkz) malloc(sizeof(Wezel));
            first->next = 0;
            last = first;
            lwez++;
            continue;
        }

        last->next = (linkz) malloc(sizeof(Wezel));
        prev = last;
        last = last->next;
        last->next = 0; //to dodalem przy zabawie ale chyba nie pomoglo na wywalane przy kilku
        lwez++;
    }while(fwczytajrek(&(last->gra), plik));
    free(last);
    lwez--;
    last = prev;
    lstron = sufit((double) lwez/nastrone);
    if(last != 0) //jesli cos wpisalismy
        last->next = 0;
    else //czy to jest potrzebne?
    {
        puts("nic nie wpisales? ;c");
        first = 0;
    }

    fclose(plik);


    return 0;
}
/////////////////////////////////////////////
char* fwczytajs(FILE* plik)
{
    char* nowa = 0;
    sdobuf(bufor, 64, plik); //nie powinny sie zapisywac znaki dlusze niz 64 bo nie moga sie wpisac tez znaki dluzsze niz 64 wiec chyba nie musze zmmieniac
    if(bufor[0] != 0)
        if((nowa = malloc(strlen(bufor)+1)))
            strcpy(nowa, bufor);

    return nowa;
}
/////////////////////////////////////////////
void sdobuf(char* bufor,int max, FILE* plik) //funkcja wczytuje az do napotkania znaku NULL albo znaku nowej lini, znak nowej lini jest zamieniany na NULL
{
    int i;
    for(i = 0;((bufor[i] = getc(plik)) != 0) && i != max-1; i++)
    {
        if(bufor[i] == '\n' || bufor[i] == EOF)
        {
            bufor[i] = 0;
            break;
        }
    }
    if(i == max-1)
        bufor[i] = 0;
}
///////////////////////////////////////////
int fwczytajrek(rekord* gra, FILE* plik)
{
    char a;

    if((gra->tytul = fwczytajs(plik)) == 0)
        return 0;
    gra->producent = fwczytajs(plik);
    gra->nosnik = fwczytajs(plik);
    gra->platforma = fwczytajs(plik);
    fscanf(plik, "%lf", &(gra->cena));
    a = getc(plik); //wczytanie nulla rozdzielajacego
    int il = 0; //gatunki troche zabawy...
    long poz = ftell(plik);
    if((a = getc(plik)) != '\n') // jesli pierwszy znak nie jest enterem to wtedy istnieja gatunki, wiec mozna je zliczyc
        while((a = getc(plik)) != '\n') //zliczanie ilosci wpisanych gatunkow
        {
            if(a == 0)
                il++;
        }
    fseek(plik, poz, SEEK_SET);
    int max = 4;
    while(il >= max) //okreslenie rozmiaru tablicy na gatunki
    {
        max = max*2;
    }

    gra->gatunek = malloc(max*sizeof(char*));
    int i;
    for(i = 0; i < il; i++)
    {
        gra->gatunek[i] = fwczytajs(plik);
    }
    gra->gatunek[il] = 0;
    if(getc(plik) == '\n')
        return 1;
    else
        return 2;
}
