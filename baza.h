#ifndef BAZA_H_INCLUDED
#define BAZA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif
/*******************TYPY********************/
typedef struct rekord{
    char* tytul;
    char* producent;
    char** gatunek; //jeden czy kilka?
    char* nosnik;
    double cena;
    char* platforma;
}rekord;


typedef struct Wezel{
    rekord gra;
    struct Wezel* next;
}Wezel;
typedef Wezel* linkz;
/*****************ZMIENNE GLOBALNE**********/
char bufor[256];
char** gatunki; //wskaznik do tablicy wskaznikow ktore pokazuja na stringi gatunkow
int lgat;
int maxgat;
int lwez;
int strona;
int lstron;
int nastrone;
linkz first;
linkz last;
/****************FUNKCJE**********************/
///baza.c///

void podstgat();

char* wczytajs();

rekord* wczytajrek(rekord* gra);

void nowabaza();

void usunzaw(linkz wezel);

int usunwezel(linkz wezel);

linkz adresnumeru(int n); //zwraca adres wybranego numeru

void edytujrekord(int n);

void czyscbaze();

void dodajsgat();

void edytujsgat();

_Bool czygatbyl(char** gatunek, int wybor);


void dodajgre();

///sortowanie.c///

void sortuj(linkz* tab, int dir);

int tytulcomp(const void* a,const void* b);

int prodcomp(const void* a,const void* b);

int noscomp(const void* a,const void* b);

int platcomp(const void* a,const void* b);

int cenacomp(const void* a,const void* b);

void tytulsort(int dir);

void prodsort(int dir);

void nossort(int dir);

void platsort(int dir);

void cenasort(int dir);

///konsola.c///

void gotoxy(int x,int y);

void jedenznak(char* klawisz);

void linijka(int y); //czysci jedna linijke i zaczyna pisanie od niej

void clrbuf();

void czysclinijke(int y);

void wyswietlsz(int n);

void czyscrog();

void czyscdol();

void clrs();

void wypiszstrony();

void wyswietlliste();

void wyswietl(const rekord* gra); //przez wsk aby nie kopiowalo struktury

int sufit(double);

///pliki.c///

int zapisz(char* nazwa);

int wczytaj(char* nazwa);

char* fwczytajs(FILE* plik);

void sdobuf(char* bufor,int max, FILE* plik);

int fwczytajrek(rekord* gra, FILE* plik);

#endif // BAZA_H_INCLUDED
