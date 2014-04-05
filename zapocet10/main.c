// test2test.cpp Kvintus František, priklad 10 - tohle si predelejte

#include <stdio.h>
#include <stdlib.h>

//Funkce pro vypocet poctu radku a prumerne delky radku

int pocetr_prumer(FILE *soubor,int volba) {

    int pocetr = 0;
    int prumer = 0;
    int znak;
    int mezisoucet = 0;

    znak = fgetc(soubor);

    while (znak != EOF) {

        if (znak == '\n') {
            pocetr++;
            mezisoucet = mezisoucet+prumer;
            prumer = 0;
        }

        else prumer++;

    znak = fgetc(soubor);
    }
    mezisoucet = mezisoucet+prumer;

    if (volba == 0 ) return pocetr+1;
    else return (mezisoucet/(pocetr+1))+(1/2);
}

//Hlavni funkce main

int main() {

    FILE *soubor,*vystup1,*vystup2;
    int n;
    char nazev[260];
    int pocetr, prumer;


    //Otevreni souboru libovolneho nazvu

    printf("Zadej nazev souboru: \n");
    scanf("%259s",nazev);
    getchar();


    //Nacteni radku a prumeru. Tady zbytecne oteviram soubor dvakrat, slo by to i jednou, na rychlost programu si tu nehrajem, tak co
    //Musim ho vzdy po projeti zavrit a pak zase otevrit

    soubor = fopen(nazev, "r");
    if (soubor == NULL) {
        printf("Soubor %s neexistuje.\n", nazev);
        return 0;
    }

    pocetr = pocetr_prumer(soubor,0);
    fclose(soubor);

    soubor = fopen(nazev, "r");
    if (soubor == NULL) {
        printf("Soubor %s neexistuje.\n", nazev);
        return 0;
    }

    prumer = pocetr_prumer(soubor,1);
    fclose(soubor);

    //Uzivatel zada N a osetrim vstup

    do {
        printf("Zadej N: ");
        if (scanf("%d",&n) != 1) {printf("Neplatny vstup.\n"); return 0;}
        if (n > pocetr) printf("Neplatny vstup. Zadej N znovu.\n");
    } while (n > pocetr);


    //Funkce ze zadani

    soubor = fopen(nazev, "r");
    if (soubor == NULL) {
    printf("Soubor %s neexistuje.\n", nazev);
    return 0;
    }
    vystup1 = fopen("vystup1.txt", "w");
    if (vystup1 == NULL) {
    printf("Soubor vystup1.txt neexistuje.\n", nazev);
    return 0;
    }
    vystup2 = fopen("vystup2.txt", "w");
    if (vystup2 == NULL) {
    printf("Soubor vystup2.txt neexistuje.\n", nazev);
    return 0;
    }

    //Kontrola

    printf("pocet radku je: %d a prumer je: %d\n",pocetr,prumer);


    //Podminky pro vypis

    int znak;
    int pocitadlor = 1;
    int pocitadloz = 0;

    znak = fgetc(soubor);
    while (znak != EOF && pocitadlor <= n) {

    //Pokud je to mensi jak prumer, zapisuju do vstupu jedna 'x'

            if (pocitadloz < prumer) {
                if (znak == '\n') {
                pocitadlor++;
                fputc('\n',vystup2);
                fputc('\n',vystup1);
                pocitadloz=0;
                } else {
                fputc('x',vystup1);
                pocitadloz++;
                }
        }

    //Pokud je to vetsi jak prumer, zapisuju do vstupu dva prebytecny znaky

            else {
                if (znak == '\n') {
                pocitadlor ++;
                fputc('\n',vystup2);
                fputc('\n',vystup1);
                pocitadloz=0;
                } else {
                fputc(znak,vystup2);
                pocitadloz++;
                }
            }


    znak = fgetc(soubor);

    }

    //Nakonci nezapomenu zavrit soubory

    fclose(soubor);
	fclose(vystup1);
	fclose(vystup2);


	return 0;
}
