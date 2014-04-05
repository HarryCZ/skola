#include <stdio.h>
#include <stdlib.h>

int smim_prepsat(char *nazev_souboru) {

    FILE *soubor;
    int volba;
    int tmp;

    soubor = fopen(nazev_souboru, "r"); // Zkusime otevrit soubor pro cteni
    if (soubor != NULL) { // Zjistime, jestli se soubor otevrel - to znamena ze existuje

        fclose(soubor); // Soubor hned zavreme, nechceme s nim nic delat

        printf("Soubor '%s' existuje, prepsat? [A/N] ", nazev_souboru);
        volba = getchar(); // Nacteme znak, ktery uzivatel zadal

        tmp = volba; // Vyprazdnime vstupni buffer - precteme vsechny znaky az do konce radku
        while (tmp != EOF && tmp != '\n' && tmp != '\r') {
        tmp = getchar();
        }

        return volba == 'A' || volba == 'a'; // Vratime TRUE pokud zadal 'A' nebo 'a', jinak FALSE.

    } else { // Kdyz se soubor neotevrel, pravdepodobne neexistuje
        return 1; // Vratime TRUE, neexistujici soubor muzeme prepsat
    }
}

int main(int argc, char* argv[]) {

    FILE *vstup, *FB, *FA;
    int znak;
    int radek = 1;
    int n = 0;
    int m = 0;

    printf("zadej hodnotu n: ");

    scanf("%d", &n);

    getchar();

    printf("zadej hodnotu m: ");

    scanf("%d", &m);

    getchar();

    vstup = fopen("vstup.txt","r"); // Otevreme zdrojovy soubor
    if (vstup == NULL) {
        printf("Nelze otevrit vstup.txt soubor\n");
        return 1;
    }

    if (!smim_prepsat("FB.txt")) { // Pokud nemuzeme prepsat cilovy soubor, ukoncime program
        printf("Nelze prepsat FA soubor\n");
        fclose(vstup); // Zavreme zdrojovy soubor!!!
        return 1;
    }

    if (!smim_prepsat("FA.txt")) { // Pokud nemuzeme prepsat soubor s patymi znaky, ukoncime program
        printf("Nelze prepsat soubor pro FA znaky\n");
        fclose(vstup); // Zavreme zdrojovy soubor!!!
        return 1;
    }

    FB = fopen("FB.txt", "w"); // Otevreme cilovy soubor
    if (FB == NULL) {
        printf("Nelze otevrit FB soubor\n");
        fclose(vstup); // Zavreme zdrojovy soubor!!!
        return 1;
    }

    FA = fopen("FA.txt", "w"); // Otevreme soubor pro FA znaky
    if (FA == NULL) {
        printf("Nelze otevrit soubor pro FA znaky\n");
        fclose(FB); // Zavreme cilovy soubor!!!
        fclose(vstup); // Zavreme zdrojovy soubor!!!
        return 1;
    }

    znak = fgetc(vstup); // Nacteme prvni znak.
    while (znak != EOF) { // Pokud se zadny znak nenacetl, ukoncime cyklus
        // Zapiseme znak do FA souboru pouze pokud je mensi nebo rovno n
        if (radek <= n) {
            fputc(znak, FA);
        }
        // Zapiseme znak do FB souboru pouze pokud je vetsi nebo rovno m
        if(radek >= m){
            fputc(znak, FB);
        }
        // Pokud jsme narazili na konec radku, zvetsime cislo radku o 1
        if (znak == '\n') {
            radek++;
        }
        // Nacteme dalsi znak a opakujeme
        znak = fgetc(vstup);
    }

    fclose(FA); // Zavreme FA soubor
    fclose(FB); // Zavreme FB soubor
    fclose(vstup); // Zavreme zdrojovy soubor

    return 0;
}
