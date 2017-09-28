#include "baza.h"

/////////////////////////
void podstgat()
{
    gatunki = malloc(10 * sizeof(char*)); //gatunki[i] musza byc wpisywane do tablicy!!!


    gatunki[0] = malloc((strlen("RPG")+1)*sizeof(char));
    gatunki[1] = malloc((strlen("FPS")+1)*sizeof(char));
    gatunki[2] = malloc((strlen("Platformowka")+1)*sizeof(char));
    gatunki[3] = malloc((strlen("RTS")+1)*sizeof(char));
    gatunki[4] = malloc((strlen("MMORPG")+1)*sizeof(char));
    gatunki[5] = NULL;

    strcpy(gatunki[0], "RPG");
    strcpy(gatunki[1], "FPS");
    strcpy(gatunki[2], "Platformowka");
    strcpy(gatunki[3], "RTS");
    strcpy(gatunki[4], "MMORPG");
    lgat = 5;
    maxgat = 10;
}
/////////////////////////
char* wczytajs()
{
    char* enter;
    char* nowa = 0;
    if(fgets(bufor, 64, stdin))
    {
        enter = strchr(bufor, '\n');
        if(enter)
        {
            *enter = 0;
            if(bufor[0] == 0)
            {
                return 0;
            }

        }
        else
            clrbuf();


        if((nowa = malloc(strlen(bufor)+1)))
           {
               strcpy(nowa, bufor);
           }
    }
    return nowa;
}
//////////////////////////////n
void static wczytajgat(char*** gatunek) //namieszana funkcja (*gatunek)[i] lolz
{
    char klawisz;
    int max = 4;
    int i = 0, j = 0;
    *gatunek = calloc(max, sizeof(char*));
    _Bool edytowano = 1;

    while(i < max) //to mozna zedytowac chyba
    {
        if(edytowano)
        {
            int y = 8;
            clrs();
            wyswietlliste();
            gotoxy(87,2);
            printf("DODAWANIE REKORDU %d.", lwez+1); gotoxy(87,3);
            fputs("Dodaj gatunki z listy",stdout); gotoxy(87,4);
            fputs("n - nowy gatunek",stdout); gotoxy(87,5);
            fputs("q - koniec",stdout); gotoxy(87,6);
            for(j = 0; j<lgat; j++, y++) //wypisanie mozliwych gatunkow
            {
                gotoxy(87,y);
                printf("%d.%s",j+1, gatunki[j]);
            }
            gotoxy(87, y+1);
            y = y+2;
            fputs("Twoje gatunki: ", stdout);
            for(i = 0;(*gatunek)[i] != 0; i++, y++) //wyswietlanie wszystkich gatunkow w jednej lini
            {
                gotoxy(87, y);
                printf("%s, ", (*gatunek)[i]);
            }
            gotoxy(0,nastrone+4);
            edytowano = 0;
        }

        jedenznak(&klawisz);
        switch(klawisz)
        {



            case'q':
            {
                return;
            }
            case'n':
            {
                int wybor;
                fputs("podaj numer: \n",stdout);
                scanf("%d", &wybor);
                clrbuf();
                wybor = wybor - 1;
                if(wybor >= 0 && wybor <= lgat-1)
                {
                    if(czygatbyl(*gatunek, wybor))
                    {
                        puts("taki gatunek juz jest, podaj inny");
                        break;
                    }

                    (*gatunek)[i] = (char*) malloc(strlen(gatunki[wybor])+1);
                    strcpy((*gatunek)[i], gatunki[wybor]);
                    edytowano = 1;
                    i++;
                    if(i == max) //powiekszenie tablicy jesli zaczyna brakowac miejsca, czyli gdy ostatnie pole zostalo zapisane
                    {
                        max = max * 2;
                        void *temp;
                        if(!(temp = realloc(*gatunek, max * sizeof(char*))))
                        {
                            puts("nie mozna znalezc miejsca na kolejne gatunki");
                            return;
                        }
                        else
                        {

                            *gatunek = temp;
                        }
                    }
                    (*gatunek)[i] = 0; //nadanie nastepnemu wskaznikowi wartosci 0 aby wiedziec kiedy koncza sie gatunki
                    break;

                }
                else
                {
                    puts("niepoprawny numer gatunku");
                    sleep(1);
                }
            }
        }
    }
}
//////////////////////////////////
rekord* wczytajrek(rekord* gra)
{
    fputs("Podaj Tytul(pusty tytul nie stworzy rekordu): ",stdout); //uzylem fputs aby nie pojawial sie enter
    if((gra->tytul = wczytajs()) == 0) //jesli w tytule wpiszemy enter to potencjalna struktura zostanie usunieta i wpisywanie zostanie zakonczone
        return 0;
    fputs("Podaj Producenta: ",stdout);
    gra->producent = wczytajs();


    fputs("Podaj Nosnik: ",stdout);
    gra->nosnik = wczytajs();
    fputs("Podaj Platforme: ", stdout);
    gra->platforma = wczytajs();
    fputs("Podaj Cene: ",stdout);

    while(scanf("%lf", &(gra->cena)) != 1)
    {
        clrbuf();
        puts("niepoprawna cena podaj jeszcze raz");
        sleep(1);
        linijka(28);
    }
        clrbuf();

    wczytajgat(&(gra->gatunek));
    return gra;

}
//////////////////////////////////////
void dodajgre()
{
    linkz akt;
    akt = (linkz) malloc(sizeof(Wezel));
    if(!(wczytajrek(&(akt->gra))))
    {
        free(akt);
        return;
    }

    if(first == NULL)
    {
        first = akt;
        last = akt;
        first->next = 0;
    }
    else
    {
        last->next = akt;
        last = akt;
        last->next = NULL;
    }
    lwez++;
    lstron = sufit((double) lwez/nastrone);
}
////////////////////////////////////////
int usunwezel(linkz wezel) //do poprawienia jeszcze trzeba zrobic podpinanie - to sie da i trzeba! i sprawdzanie usuwania o ile sie da?
{
    linkz akt;
    linkz poprz;
    usunzaw(wezel);
    lwez--;
    if(first == wezel) //okreslanie polozenia usuwanego wezla a nastepnie dokonanie odpowiedniego przestawienia
    {
        first = wezel->next;
        free(wezel);
        return 0;
    }

    akt = first;
    while(akt != wezel)
    {
        poprz = akt;
        akt = akt->next;

    }
    if(last == wezel)
    {
        last = poprz;
        last->next = 0;
        free(wezel);

    }
    else
    {
        poprz->next = akt->next;
        free(wezel);
    }
    lstron = sufit((double) lwez/nastrone);
    if(strona > lstron) strona = lstron;
    return 0;
}
///////////////////////////////////
linkz adresnumeru(int n) //podaje adres wybranego numeru, numer liczony od 1
{
    int i;
    linkz akt = first;
    for(i = 1; i < n; i++)
    {
        akt = akt->next;
    }
    return akt;
}
//////////////////////////////////
void edytujrekord(int n)
{
    char klawisz;
    rekord *gra = &(adresnumeru(n)->gra);



    _Bool edytowane = 1;

    while(1)
    {

        if(edytowane) //aby nie wyswietlalo sie wielokrotnie przy wciskaniu entera i blednych danych
        {
            clrs();
            gotoxy(0,0);
            puts("EDYTOWANY:");
            wyswietlsz(n);
            gotoxy(87,2);
            printf("EDYCJA REKORDU %d.",n); gotoxy(87,3);
            fputs("wyberz pole do edycji:",stdout); gotoxy(87,4);
            fputs("|t - tytul",stdout); gotoxy(87,5);
            fputs("|p - producent",stdout); gotoxy(87,6);
            fputs("|g - gatunek",stdout); gotoxy(87,7);
            fputs("|n - nosnik",stdout); gotoxy(87,8);
            fputs("|c - cena",stdout); gotoxy(87,9);
            fputs("|o - platforma",stdout); gotoxy(87,10);
            fputs("|q - wyjscie",stdout); gotoxy(87,11);



            gotoxy(0, nastrone+4);
            edytowane = 0;
        }

        jedenznak(&klawisz);
        switch(klawisz)
        {
            case'q':
            {
                return;
            }


            case't':
            {
                fputs("Podaj nowy tytul: ",stdout);
                free(gra->tytul);
                gra->tytul = wczytajs();
                edytowane = 1;
                break;
            }
            case'p':
            {
                fputs("Podaj nowego producenta:",stdout);
                free(gra->producent);
                gra->producent = wczytajs();
                edytowane = 1;
                break;
            }
            case'g': //przy dodawaniu nowego gatunku jesli usunalem wczesniej gatunek to nadal reallocuje tablice na nowo jesli sie powiekszy
            {
                _Bool koniec = 0;
                int y;
                while(!koniec)
                {
                    czyscrog();
                    gotoxy(87,2);
                    fputs("EDYCJA REKORDU - gatunku",stdout); gotoxy(87,3);
                    fputs("|d - dodaj nowy gatunek",stdout); gotoxy(87,4);
                    fputs("|e - edytuj gatunek",stdout); gotoxy(87,5);
                    fputs("|u - usun",stdout); gotoxy(87,6);
                    fputs("|q - wroc do menu edycji",stdout); gotoxy(87,8);
                    linijka(nastrone+4);
                    jedenznak(&klawisz);
                    switch(klawisz)
                    {
                        case'd':
                        {
                            koniec = 1;
                            edytowane = 1;
                            int ost = 0, max = 4;
                            while(gra->gatunek[ost] != 0) //funkcja liczaca ostatni element tablicy i obliczajaca rozmiar tablicy
                            {
                                if(ost == max-1)
                                {
                                    max = max*2;
                                }
                                ost++;
                            }
                            int j;
                            int wybor;
                            czyscrog(); gotoxy(87, 2);
                            printf("EDYCJA REKORDU %d. - dodawanie gatunku", n); gotoxy(87,4);
                            fputs("wybierz numer gatunku:",stdout);
                            for(j = 0, y = 5; j<lgat; j++,y++) //wypisanie mozliwych gatunkow
                            {
                                gotoxy(87,y); printf("%d.%s\n",j+1, gatunki[j]);
                            }
                            linijka(nastrone+4);
                            scanf("%d", &wybor);
                            clrbuf();
                            linijka(nastrone+4);
                            wybor = wybor - 1;
                            if(wybor >= 0 && wybor <= lgat-1)
                            {
                                if(czygatbyl(gra->gatunek, wybor))
                                {
                                    puts("taki gatunek juz jest, podaj inny");
                                    sleep(1);
                                    break;
                                }

                                gra->gatunek[ost] = (char*) malloc(strlen(gatunki[wybor])+1);
                                strcpy(gra->gatunek[ost], gatunki[wybor]);
                                if(ost+1 == max) //powiekszenie tablicy jesli zaczyna brakowac miejsca, czyli gdy ostatnie pole zostalo zapisane
                                {
                                    max = max * 2;
                                    void* temp;
                                    if(!(temp = realloc(gra->gatunek, max * sizeof(char*))))
                                    {
                                        puts("nie mozna znalezc miejsca na kolejne gatunki");
                                        return;
                                    }
                                    else
                                    {
                                        gra->gatunek = temp;
                                    }
                                }

                                gra->gatunek[ost+1] = 0; //nadanie nastepnemu wskaznikowi wartosci 0 aby wiedziec kiedy koncza sie gatunki
                            }


                            edytowane = 1;
                            break;

                        }
                        case'e':
                        {
                            koniec = 1;
                            edytowane = 1;
                            int edytowany;
                            int j;
                            czyscrog(); gotoxy(87, 2);
                            printf("EDYCJA REKORDU %d. - edycja gatunku", n); gotoxy(87,4);
                            fputs("wybierz numer gatunku:",stdout);
                            for(j = 0, y = 5; gra->gatunek[j]; j++, y++) //wypisanie mozliwych gatunkow
                            {
                                gotoxy(87,y); printf("%d.%s\n",j+1, gra->gatunek[j]);
                            }
                            linijka(nastrone+4);
                            scanf("%d", &edytowany);
                            clrbuf();
                            linijka(nastrone+4);;
                            edytowany = edytowany-1;
                            if(edytowany >= 0 && edytowany <= j)
                            {
                                while(1)
                                {
                                    int j;
                                    czyscrog();
                                    gotoxy(87,2);
                                    printf("EDYCJA REKORDU %d. - edycja gatunku", n); gotoxy(87,4);
                                    fputs("wybierz numer gatunku do zamiany:",stdout);
                                    for(j = 0, y = 5; j < lgat; j++, y++) //wypisanie mozliwych gatunkow
                                    {
                                        gotoxy(87,y); printf("%d.%s\n",j+1, gatunki[j]);
                                    }
                                    int wybor;
                                    linijka(nastrone+4);
                                    scanf("%d", &wybor);
                                    clrbuf();
                                    wybor = wybor - 1;
                                    if(wybor >= 0 && wybor <= lgat-1)
                                    {
                                        if(czygatbyl(gra->gatunek, wybor))
                                        {
                                            puts("taki gatunek juz jest, podaj inny");
                                            break;
                                        }

                                        gra->gatunek[edytowany] = (char*) malloc(strlen(gatunki[wybor])+1);
                                        strcpy(gra->gatunek[edytowany], gatunki[wybor]);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                puts("nie ma takiego pola");
                                sleep(1);
                            }
                                czyscdol();
                            break;
                        }
                        case'u': //mozna zrobic pomniejszanie tablicy aby nie reallocowac bez sensu przy edytowaniu i potem ponownym dodawaniu
                        {
                            koniec = 1;
                            edytowane = 1;
                            int edytowany,j = 0;
                            czyscrog();
                            gotoxy(87,2);
                            printf("EDYCJA REKORDU %d. - usuwanie gatunku", n); gotoxy(87,4);
                            fputs("wybierz numer gatunku do usuniecia:",stdout);
                            for(j = 0, y = 5; gra->gatunek[j]; j++, y++) //wypisanie mozliwych gatunkow
                            {
                                gotoxy(87,y); printf("%d.%s\n",j+1, gra->gatunek[j]);
                            }
                            gotoxy(0,nastrone+4);
                            scanf("%d", &edytowany);
                            clrbuf();
                            edytowany = edytowany-1;
                            if(edytowany >= 0 && edytowany <= j-1)
                            {
                                free(gra->gatunek[edytowany]);
                                while(gra->gatunek[edytowany] != 0) //petla przesuwajaca pozostale gatunki
                                {
                                    gra->gatunek[edytowany] = gra->gatunek[edytowany+1];
                                    edytowany++;
                                }
                            }

                            break;
                        }

                        case'q':
                        {
                            koniec = 1;
                            break;
                        }

                    }

                }
                break;
            }
            case'n':
            {
                fputs("Podaj nowy nosnik: ",stdout);
                free(gra->nosnik);
                gra->nosnik = wczytajs();
                edytowane = 1;
                break;
            }
            case'c':
            {
                fputs("Podaj nowa cene: ",stdout);
                while(scanf("%lf", &(gra->cena)) != 1)
                {
                    clrbuf();
                    puts("niepoprawna cena podaj jeszcze raz");
                    sleep(1);
                    linijka(nastrone+4);
                }
                clrbuf();
                edytowane = 1;
                break;
            }
            case'o':
            {
                fputs("Podaj nowa platforme: ", stdout);
                free(gra->platforma);
                gra->platforma = wczytajs();
                edytowane = 1;
                break;
            }

        wyswietl(gra);
        }
    }
}
///////////////////////////////////////
void usunzaw(linkz wezel)
{
    int i;
    free(wezel->gra.tytul);
    free(wezel->gra.producent);
    for(i = 0; (wezel->gra.gatunek)[i] != 0; i++) //usuwanie wszystkich gatunkow
        free(wezel->gra.gatunek[i]);
    free(wezel->gra.gatunek);
    free(wezel->gra.nosnik);
    free(wezel->gra.platforma);
}
/////////////////////////////////////
void czyscbaze() //usuwanie tablicy gatunkow!!!CO TO ZA FUNKCJA?!!!czemu free?
{
    linkz nast;
    int i;
    while(first != 0)
    {
        nast = first->next;
        usunzaw(first);
        free(first);
        first = nast;
    }
    lwez = 0;

    for(i = 0;i < lgat; i++)
    {
        free(gatunki[i]);
    }
    free(gatunki);
}
///////////////////////////////////////
_Bool czygatbyl(char** gatunek, int wybor)
{
    int i = 0;

    while(gatunek[i] != 0)
    {
        if(strcmp(gatunki[wybor], gatunek[i]) == 0)
            return 1;
        i++;

    }
    return 0;
}
////////////////////////////////////////
void dodajsgat()
{

    if(lgat == maxgat)
    {
        maxgat = maxgat * 2;
        void* temp;
        if(!(temp = realloc(gatunki, maxgat * sizeof(char*))))
            puts("blad nie powiekszylem tablicy gatunkow");
        else
        {
            gatunki = temp;
        }
    }

    fputs("Podaj nazwe gatunku: ", stdout);

    if((gatunki[lgat] = wczytajs()) == 0)
        return;

        lgat++;
        return;


}
////////////////////////////////////////
void edytujsgat()
{
    int wybor;
    int i = 0, y = 0;
    char klawisz;
    _Bool koniec = 0, edytowane = 1;

        while(!koniec)
        {

            if(edytowane)
            {
                czyscrog();
                gotoxy(87,2);
                fputs("EDYCJA LISTY GATUNKOW",stdout);gotoxy(87,3);
                fputs("|d - dodaj",stdout); gotoxy(87,4);
                fputs("|e - edytuj gatunek",stdout); gotoxy(87,5);
                fputs("|u - usun gatunek",stdout); gotoxy(87,6);
                fputs("|q - wyjdz",stdout); gotoxy(87,7);

                for(y = 10, i = 0;i < lgat; i++, y++)
                {
                    gotoxy(87,y);
                    printf("%d.%s\n",i+1, gatunki[i]);
                }
                y = 9; //zmienna przechowujaca aktualna linijke
                gotoxy(0,nastrone+4);
                edytowane = 0;
            }
            jedenznak(&klawisz);
            czyscdol();
            switch(klawisz)
            {
            case'd':
                {
                    dodajsgat();
                    czysclinijke(nastrone+4);
                    edytowane = 1;
                    break;
                }

            case'e':
                {
                    edytowane = 1;
                    gotoxy(87,8);
                    fputs("wybierz gatunek:",stdout);
//                    for(j = 0; j<lgat; j++, y++) //wypisanie mozliwych gatunkow
//                    {
//
//                        gotoxy(87,y);
//                        printf("%d.%s\n",j+1, gatunki[j]);
//                    }
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    linijka(nastrone+4);
                    wybor = wybor-1;
                    if(wybor >= 0 && wybor <= lgat-1)
                    {

                        fputs("Podaj nowa nazwe gatunku: ", stdout);
                        free(gatunki[wybor]);
                        gatunki[wybor] = wczytajs();

                    }
                    else
                    {
                        fputs("bledny numer",stdout);
                        sleep(1);
                    }
                    linijka(nastrone+4);
                    break;
                }
            case'u':
                {
                    edytowane = 1;
                    gotoxy(87,8);
                    fputs("wybierz gatunek",stdout);
//                    for(j = 0; j<lgat; j++, y++) //wypisanie mozliwych gatunkow
//                    {
//
//                        gotoxy(87,y);
//                        printf("%d.%s\n",j+1, gatunki[j]);
//                    }
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    wybor = wybor-1;
                    if(wybor >= 0 && wybor <= lgat-1)
                    {
                        free(gatunki[wybor]);
                        while(wybor < lgat-1) //petla przesuwajaca pozostale gatunki
                        {
                            gatunki[wybor] = gatunki[wybor+1];
                            wybor++;
                        }
                        lgat--;
                    }
                    else
                    {
                        fputs("bledny numer",stdout);
                        sleep(1);
                    }
                    break;

                }
            case'q':
                {
                    koniec = 1;
                    break;
                }
            }
        }
}

