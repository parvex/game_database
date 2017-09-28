#include "baza.h"
int main()
{


    char klawisz;

    nastrone = 15; //ustawienia domyslne sortowania i wyswietlania rekordow na strone
    int dir = 1;
    void (*sort_wsk)(int dir) = tytulsort;

    while(1)
    {


        _Bool wybrano = 0;
       while(!wybrano)
        {
            clrs();
            gotoxy(0,0);
            puts("Witaj w katalogu gier, wybierz opcje:     |Dla poprawnego dzialania programu:\n\n"
                 "n - nowa baza                              -powieksz odpowiednio okno\n"
                 "w - wczytaj baze z pliku                   -nie wpisuj polskich znakow \n"
                 "q - wyjdz\n\n\n\n"
                 "                                        Notatki:\n"
                 "                                        -(null) oznacza brak wpisanej wartosci\n"
                 "                                        -nie wpisanie tytulu spowoduje\n"
                 "                                         anulowanie tworzenia rekordu\n");


            if((klawisz = getchar()) == '\n')
            {
                continue;
            }

            if(getchar() != '\n')
            {
                continue;
            }

            switch(klawisz)
            {
            case'n':
                {
                    clrs();
                    podstgat();
                    wybrano = 1;
                    break;
                }
            case'w': //wywala przy kilku rekordach
                {
                    char* enter = NULL;
                    clrs();
                    gotoxy(0,0);
                    puts("Podaj nazwe pliku: ");
                    gotoxy(0,nastrone+4);
                    if(fgets(bufor, 256, stdin))
                    {
                        enter = strchr(bufor, '\n');
                        if(enter)
                        {
                            *enter = 0;
                        }
                    }
                   if(wczytaj(bufor) != -1)
                    wybrano = 1;
                   else
                    {
                        puts("nie udalo sie wczytac pliku");
                        sleep(1);
                    }
                    break;
                }
            case'q':
                {
                    return 0;
                }
            }
        }
        if(lwez) strona = 1;
        wybrano = 0;
        while(!wybrano) //menu glowne bazy
        {
            if(lwez == 1) strona = 1;
            sort_wsk(dir);
            clrs();
            gotoxy(0,0);
            wyswietlliste();
            gotoxy(87, 2);
            if(!first)
            {
                fputs("MENU GLOWNE",stdout); gotoxy(87,3);
                fputs("|d - dodaj",stdout); gotoxy(87, 4);
                fputs("|l - edytuj liste gatunkow", stdout); gotoxy(87,5);
                fputs("|q - wyjdz",stdout);
            }
            else
            {
                fputs("MENU GLOWNE",stdout); gotoxy(87,3);
                fputs("|d - dodaj",stdout); gotoxy(87,4);
                fputs("|e - edytuj rekord",stdout); gotoxy(87,5);
                fputs("|u - usun rekord",stdout); gotoxy(87,6);
                fputs("|l - edytuj liste gatunkow",stdout); gotoxy(87,7);
                fputs("|s - sortowanie",stdout); gotoxy(87,8);
                fputs("|y - pokaz szczegoly",stdout); gotoxy(87,9);
                fputs("|p - strona",stdout); gotoxy(87,10);
                fputs("|i - ilosc rekordow na strone",stdout); gotoxy(87,11);
                fputs("|z - zapisz do pliku",stdout); gotoxy(87,12);
                fputs("|q - zamknij baze",stdout); //gotoxy(87,13);
            }
            gotoxy(0, nastrone+4);
            jedenznak(&klawisz);
            switch(klawisz)
            {
            case'd':
                {
                    czyscrog();
                    gotoxy(87,2);
                    printf("DODAWANIE REKORDU %d.", lwez+1); gotoxy(87,3);
                    linijka(nastrone+4);
                    dodajgre();
                    break;
                }
            case'l':
                {
                    edytujsgat();
                    break;
                }
            case'p':
                {
                    //wyswietlanie stron
                    int wybor = 0;
                    gotoxy(87, 14);
                    fputs("podaj numer strony:", stdout); gotoxy(0,nastrone+4);
                    scanf("%d", &wybor);
                    if(wybor >= 1 && wybor <= lstron) strona = wybor;
                    else
                    {
                        fputs("bledny numer strony",stdout); sleep(1);
                    }
                    break;
                }
            case'q':
                {
                    czyscbaze();
                    wybrano = 1;
                    break;
                }
            case'i':
                {
                    int wybor = 0;
                    czyscrog();
                    gotoxy(87, 2);
                    fputs("ILOSC REKORDOW NA STRONE",stdout); gotoxy(87,3);
                    fputs("wybierz ilosc rekordow",stdout); gotoxy(87,4);
                    fputs("na strone(max 25):",stdout);
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    linijka(nastrone+4);
                    if(wybor >= 1 && wybor <= 25)
                    {
                        nastrone = wybor;
                        lstron = sufit((double) lwez/nastrone);
                        if(strona > lstron) strona = lstron;
                    }
                    break;
                }
            case'e':
                {
                    int wybor = 0;
                    czyscrog();
                    gotoxy(87, 2);
                    fputs("EDYCJA REKORDU",stdout); gotoxy(87,3);
                    fputs("wybierz numer rekordu:",stdout);
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    linijka(nastrone+4);
                    if(wybor >= 1 && wybor <= lwez)
                    {
                        edytujrekord(wybor);
                    }
                    break;
                }
            case'u': //lwez jest zle po usuwaniu albo mi sie wydawalo
                {
                    int wybor = 0;
                    czyscrog();
                    gotoxy(87, 2);
                    fputs("USUWANIE REKORDU",stdout); gotoxy(87,3);
                    fputs("wybierz numer rekordu:",stdout);
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    linijka(nastrone+4);
                    if(wybor >= 1 && wybor <= lwez)
                        usunwezel(adresnumeru(wybor));

                    break;
                }
            case'z': //wywala przy kilku rekordach wczytywanie
                {
                    char* enter = NULL;
                    clrs();
                    puts("Podaj nazwe pliku: ");
                    if(fgets(bufor, 256, stdin))
                    {
                        enter = strchr(bufor, '\n');
                        if(enter)
                        {
                            *enter = 0;
                        }
                    }
                    zapisz(bufor);
                    break;
                }
            case'y':
                {
                    int wybor = 0;
                    czyscrog();
                    gotoxy(87, 2);
                    fputs("POKAZ SZCZEGOLY",stdout); gotoxy(87,3);
                    fputs("wybierz numer rekordu:",stdout);
                    linijka(nastrone+4);
                    scanf("%d", &wybor);
                    clrbuf();
                    clrs();
                    if(wybor >= 1 && wybor <= lwez)
                    {
                        wyswietlsz(wybor);
                    }
                    linijka(nastrone+4);
                    puts("wpisz cokolwiek aby kontynuowac:");
                    getchar();
                    clrbuf();
                    break;
                }
            case's':
                {
                    czyscrog();
                    gotoxy(87,2);
                    fputs("MENU SORTOWANIA",stdout); gotoxy(87,3);
                    fputs("|t - sortuj po tytule",stdout); gotoxy(87,4);
                    fputs("|p - sortuj po producencie",stdout); gotoxy(87,5);
                    fputs("|n - sortuj po nosniku",stdout); gotoxy(87,6);
                    fputs("|o - sortuj po platformie",stdout); gotoxy(87,7);
                    fputs("|c - sortuj po cenie",stdout); gotoxy(87,8);
                    fputs("|q - wyjscie",stdout); //gotoxy(87,9);
                    _Bool sortkoniec = 0;
                    _Bool sortwybrano = 0;
                    while(!sortwybrano)
                    {

                        jedenznak(&klawisz);
                        switch(klawisz)
                        {
                        case't':
                            {
                                sort_wsk = tytulsort;
                                sortwybrano = 1;
                                break;
                            }
                        case'p':
                            {
                                sort_wsk = prodsort;
                                sortwybrano = 1;
                                break;
                            }
                        case'n':
                            {
                                sort_wsk = nossort;
                                sortwybrano = 1;
                                break;
                            }
                        case'o':
                            {
                                sort_wsk = platsort;
                                sortwybrano = 1;
                                break;
                            }
                         case'c':
                            {
                                sort_wsk = cenasort;
                                sortwybrano = 1;
                                break;
                            }
                         case'q':
                            {
                                sortwybrano = 1;
                                sortkoniec = 1;
                                break;
                            }


                        }
                        if(sortkoniec) break;
                        gotoxy(87,10);
                        fputs("podaj kierunek sortowania",stdout); gotoxy(87,11);
                        fputs("|r - rosnaco",stdout); gotoxy(87,12);
                        fputs("|m - malejaco",stdout); gotoxy(87,13);
                        fputs("|domyslnie - malejaco",stdout); linijka(nastrone+4);
                        jedenznak(&klawisz);
                        switch(klawisz)
                        {
                        case'r':
                            {
                                dir = 1;
                                break;
                            }

                        case'm':
                            {
                                dir = -1;
                                break;
                            }
                        default:
                            {
                                dir = -1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}



















