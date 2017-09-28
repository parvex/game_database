#include "baza.h"
///////////////////////////
void gotoxy(int x,int y)
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__) //w zaleznosci od systemu operacyjnego nalezy uzyc innej komendy do czyszczenia konsoli
        printf("%c[%d;%df",0x1B,y,x);
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        COORD cord;
        cord.X = x;
        cord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
    #endif
}
///////////////////////////////////////
void clrbuf()
{
    while(getchar() != '\n')
        continue;
}
////////////////////////////
void jedenznak(char *klawisz)
{
    while(1)
    {
        gotoxy(0,nastrone+4);
        if((*klawisz = getchar()) == '\n')
        {
            czysclinijke(nastrone+4);
            continue;
        }

        if(getchar() != '\n')
        {
            czysclinijke(nastrone+4);
            clrbuf();
            continue;
        }
        czysclinijke(nastrone+4);
        gotoxy(0,nastrone+4);
        break; //petla zakonczy sie tylko jesli wczytalismy jeden znak
    }
}

//////////////////////////
void linijka(int y)
{
    czysclinijke(y);
    gotoxy(0, y);
}
//////////////////////////
void czysclinijke(int y)
{
    gotoxy(0,y);
    fputs("                                                                                   ",stdout);
}
//////////////////////////
void czyscrog()
{
    int y;
    for(y = 2; y < 30; y++)
    {
        gotoxy(87, y);
        fputs("                               ",stdout);
    }
}
////////////////////////////
void czyscdol()
{
    int y, i;
    for(y = nastrone+4, i = 0; i < 15; i++);
        czysclinijke(y);

    gotoxy(0,nastrone+4);
}
////////////////////////////
void clrs()
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__) //w zaleznosci od systemu operacyjnego nalezy uzyc innej komendy do czyszczenia konsoli
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
//////////////////////////////////////////
void wypiszstrony()
{
    gotoxy(87, 1);
    printf("strona:%-2d/%2d po:%d Rekordow:%d", strona, lstron,nastrone, lwez);
}
/////////////////////////////////////////
int sufit(double liczba)
{
    int calkowita = (int) liczba;

    if((double) calkowita == liczba)
        return liczba;
    else
        return liczba+1;
}
//////////////////////////////
void wyswietlsz(int n)
{
    rekord* gra = &((adresnumeru(n))->gra);
    int i;
    clrs();
    printf("\n"
           "REKORD: %d\n"
           "Tytul:     %s\n"
           "Producent: %s\n"
           "Gatunek:   " ,n, gra->tytul, gra->producent);

    for(i = 0;gra->gatunek[i] != 0; i++) //wyswietlanie wszystkich gatunkow w jednej lini
        printf("%s, ", (gra->gatunek)[i]);
        putchar('\n');

    printf("Nosnik:    %s\n"
           "Cena:      %.2lf zl\n"
           "Platforma: %s\n"
           "-----------------------------------------\n", gra->nosnik, gra->cena, gra->platforma);
}
/////////////////////////////////////////
void wyswietlliste()
{
    int i, j;
    linkz akt = first;
    for(i = 0; i < nastrone*(strona-1); i++)//przewiniecie do wybranej strony
    {
        akt = akt->next;
    }

    puts("   Tytul         |Producent     |Nosnik        |Platforma     |Gatunek       |Cena");
    puts("-----------------------------------------------------------------------------------");
    for(j = 0; akt != 0 && j < nastrone; i++, j++)
    {

        printf("%2d.", i+1);
        wyswietl(&(akt->gra));
        akt = akt->next;
    }
    wypiszstrony();
}
////////////////////////////////////////////////////////
void wyswietl(const rekord *gra) //jak to z tym gatunkiem?
{
//    if(gra->tytul) fputs(gra->tytul, stdout);
//    if(gra->producent) fputs(gra->producent, stdout);
//    if(gra->nosnik) fputs(gra->nosnik, stdout);
//    if(gra->platforma]) fputs(gra->platforma, stdout);
//    if(gra->gatunek[0]) fputs(gra->, stdout);
    printf("%-15.14s%-15.14s%-15.14s%-15.14s%-15.14s%.2lf\n", gra->tytul, gra->producent, gra->nosnik, gra->platforma, gra->gatunek[0], gra->cena);
}

