/*
 * obrazek.c
 * program vypisujici obrazek skladajici se z:
 *  - diagonaly ze spodniho leveho rohu vykreslene znakem "X"
 *  - tri radku znaku "-" koncici dva radky od konce
 *  - vsechna zbyla pole jsou vyplnena znakem "."
 * velikost pole zadava uzivatel z klavesnice
 */

//deklarace hlavicek preprocesoru
#include <stdio.h>
#include <stdlib.h>

//hlavni funkce kazdeho programu v C
int main()
{
    int r, s; //Promenne ktere ponesou cislo aktualniho radku (int r) a sloupce (int s)
    int max_r, max_s; // Promenne pro pocet radku (int max_r) a sloupcu (int max_s).

    printf("Zadej pocet radku: "); //Vytiskne text: "Zadej pocet radku: "
    scanf("%d", &max_r); // Nechame uzivatele aby zadal pocet radku. "%d" znamena ze cteme cele cislo, ulozime ho do promenne max_r. &max_r znamena adresu promenne max_r.
    printf("Zadej pocet sloupcu: ");//Vytiskne text: "Zadej pocet sloupcu: "
    scanf("%d", &max_s); // Pocet sloupcu; zatim neresime, co se stane, kdyz uzivatel zada neco jineho nez cislo, nezkousejte to, naucime se pozdeji.

    for (r = 1; r <= max_r; r++) {//Prvni for cyklus vzdy reprezentuje postup po radcich
        for (s = 1; s <= max_s; s++) {//Druchy for cyklus vzdy reprezentuje postup po sloupcich
            /* Vykresleni diagonaly od leveho spodniho do praveho horniho rohu
             * Podminka se pta zda soucet je cisla aktualniho radku a sloupce roven celkovemu poctu radku
             * napr. rozmery r=7 s=5
             * tzn. podminka je splnena pro 7+1=8; 6+2=8 atd.
             * zaroven mame zaruceno ze pri obdelnikovem tvaru bude diagonala stale vykreslovana od spodniho radku
             * dukaz: 1+6=7; 2+5=7
             * obrazek by pak vypadal takto:
             *     |     |
             *     |     |
             *     |    X|
             *     |   X |
             *     |  X  |
             *     | X   |
             *     |X    |
             */
            if (r+s == max_r+1) {
                printf("X");//vypise X
            /* else if
             * prikaz ktery je vyvolan v pripade nesplneni podminky (else) a vyvolava dalsi podminku (if)
             * podminka se pta zda je aktualni radek vice nez 5 a mene nez 2 radky od konce
             * prakticky to znamena ze znak O vypisujem na ve vsech sloupcich radku 3,4 a 5.
             * Mimo sloupcu ktere jsme zaplnili predchozi podminkou
             * obrazek by tedy v tuto chvili vypadal takto:
             *     |     |
             *     |     |
             *     |----X|
             *     |---X-|
             *     |--X--|
             *     | X   |
             *     |X    |
             */
            } else if ((r > (max_r-5)) && (r < (max_r-1))) {
                 printf("-");//vypise -
            /* no a v pripade ze nebyla splnena ani jedna podminka vypiseme "."
             * tip vyplnime vsechny zbyla pole
             * vysledny obrazek tedy vypada takto
             *     |.....|
             *     |.....|
             *     |----X|
             *     |---X-|
             *     |--X--|
             *     |.X...|
             *     |X....|
             */
            } else {
                printf(".");//vypise .
            }
        }
        printf("\n");//ukonceni radku pred prechodem vypisu na dalsi
    }
    return 0;//ukonceni funkce
}
