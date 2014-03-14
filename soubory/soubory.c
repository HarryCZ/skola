/*
 * soubory.c
 * program ktery nacte soubor "soubor.txt" vezme prvnich r radku a zapise:
 * - liche radky do souboru "liche.txt"
 * - sude radky do souboru "sude.txt"
 * pocet radku r zada uzivatel z klavesnice
 */

//deklarace hlavicek preprocesoru
#include <stdio.h>
#include <stdlib.h>

//hlavni funkce kazdeho programu v C
int main()
{
	FILE *vstup, *lichy, *sudy; //deklarace ukazatelu na soubory
	int znak; //promenna nesouci aktualni znak
	int radek = 1; //promena nesouci cislo aktualniho radku
	int r=0; // promena nesouci pocet radku ke zpracovani zadany uzivatelem

	// Otevreme zdrojovy soubor pro cteni ("r") pri rezimu read je nutne aby soubor existoval na dane ceste
	vstup = fopen("soubor.txt", "r"); // priradi soubor "soubor.txt" ukazateli vstup
 	if (vstup != NULL) {// pokud se podari soubor otevrit program pokracuje

		// Otevreme cilovy soubor lichy pro zapis
		lichy = fopen("liche.txt", "w"); // priradi soubor "liche.txt" ukazateli lichy
		if (lichy != NULL) {// pokud se podari soubor otevrit program pokracuje

			// Otevreme cilovy soubor sudy pro zapis
			sudy = fopen("sude.txt", "w"); // priradi soubor "sude.txt" ukazateli sudy
			if (sudy != NULL) {// pokud se podari soubor otevrit program pokracuje

                printf("Zadej pocet radku: "); // Vypise na obrazovku "Zadej pocet radku: "
                scanf("%d", &r); // Nechame uzivatele aby zadal pocet radku. "%d" znamena ze cteme cele cislo, ulozime ho do promenne r. &r znamena adresu promenne r.


				// Nacteme prvni znak
				znak = fgetc(vstup);

				// Dokud nejsme na konci souboru a zaroven jsme nedosli na konec prohledavani zadanny uzivatelem
				while ((znak != EOF)&&(radek <= r)) {

					/*
					 * Podle cisla radku zapiseme znak do licheho nebo sudeho souboru
					 * % (cti modulo) je operator pro deleni se zbytkem vysledkem je hodnota zbytku
					 * tzn. 4%2=0; 8%2=0; 3%2=1; 5%2=1 atd..
					 */
					if (radek % 2 == 1) { // pokud je radek lichy 1%2=1; 3%2=1; 9%2=1 atd.
						fputc(znak, lichy); // fputc (File-PUT-Character) zapise znak ("znak") do souboru ("lichy")
					} else { // pokud neni radek lichy je logisky sudy :)
						fputc(znak, sudy); // fputc (File-PUT-Character) zapise znak ("znak") do souboru ("sudy")
					}

					// Pokud jsme narazili na konec radku, zvetsime cislo radku o 1
					if (znak == '\n') { // '\n' je znak oznacujici konec radku je to znak ktery v souboru vzdy je ackoliv ho editory nezobrazuji
						radek++; // ++ (inkrementace) jenda se v podstate o zkraceni zapisu naviseni promenne o jeden dilek tzn. radek++ je to same jako radek=radek+1
					}

					// Nacteme dalsi znak a opakujeme
					znak = fgetc(vstup);
				}

				// Zavreme sudy cilovy soubor
				fclose(sudy);
			}

			// Zavreme lichy cilovy soubor
			fclose(lichy);
		}

		// Zavreme zdrojovy soubor
		fclose(vstup);
	}

    /*
     * system("PAUSE")
     * pozastavi beh programu a umozni uzivateli precist si vysledky
     * v praxi to znamena ze na obrazovku se vypise hlaska:
     * "Press any key to continue . . ."
     * a program ceka nez uzivatel stiskne klavesu, pote dokonci zbyle prikazy
     */
	system("PAUSE");

	// ukonceni funkce
	return 0;
}
