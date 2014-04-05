
#include <stdio.h>

/* Funkce spocita kolik radku v souboru je. */
int spocitej_radky(FILE *soubor) {
	int pocet_radku = 0; // Pocet radku, zacina 0
	int znak;

	for (znak = fgetc(soubor); znak != EOF; znak = fgetc(soubor)) {
		if (znak == '\n') { // Vzdycky kdyz najdeme konec radku, zvysime pocet radku o 1
			pocet_radku++;
		}
	}
	return pocet_radku;
}

int nejmensi_pocet_znaku(FILE *soubor) {
    int radek = 1;
    int znak;
    int nejkratsi=99999;
    int aktualni_delka = 0;

    for (znak = fgetc(soubor); znak != EOF; znak = fgetc(soubor)) {
        aktualni_delka++;
        if (znak == '\n') { // Pokud najdeme konec radku, zvysime pocitadlo radku o 1
			radek++;
			if (aktualni_delka < nejkratsi) {
                nejkratsi = aktualni_delka;
			}
			aktualni_delka=0;
		}
    }
    return nejkratsi-2;
}

int zapis_radky_do_souboru(FILE *vystup,FILE *soubor, int pocet_radku, int celkem_radku, int nejkratsi) {
    int radek = 1; // Pocitadlo radku, prvni radek ma cislo 1
	int znak;
	int aktualni_delka=0;

	for (znak = fgetc(soubor); znak != EOF; znak = fgetc(soubor)) {
		if ((radek <= pocet_radku)&&(aktualni_delka<=nejkratsi)) { // Pokud aktualni radek patri mezi posledni radky, zobrazime znak
			fputc(znak,vystup);
			aktualni_delka++;
		}
		if (znak == '\n') { // Pokud najdeme konec radku, zvysime pocitadlo radku o 1
			radek++;
			aktualni_delka=0;
			fputc('\n',vystup);
		}
	}

	return 0;
}

int main() {
	char nazev_souboru[256];
	int celkem_radku, pocet_radku, nejkratsi;
	FILE *soubor,*vystup;

	// Nacteme nazev souboru a zkontrolujeme, ze uzivatel neco zadal
	printf("Zadej nazev souboru: ");
	if (scanf("%255s", nazev_souboru) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}

	// Nacteme pocet radku, ktere se maji zobrazit, a zkontrolujeme, ze uzivatel neco zadal
	printf("Zadej pocet radku: ");
	if (scanf("%d", &pocet_radku) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}

	// Zkusime otevrit soubor a zkontrolujeme vysledek
	soubor = fopen(nazev_souboru, "r");
	if (soubor == NULL) {
		printf("Soubor nelze otevrit.\n");
		return 1;
	}

    vystup = fopen("vystup.txt", "w");
	if (vystup == NULL) {
		printf("Soubor nelze vytvorit.\n");
		return 1;
	}


	// Zjistime pocet radku v souboru
	celkem_radku = spocitej_radky(soubor);

	// Overime, ze pocet radku, ktere se maji zobrazit, je v povolenem rozsahu
	if (pocet_radku < 1 || pocet_radku > celkem_radku) {
		printf("Pocet radku musi byt mezi %d a %d.\n", 1, celkem_radku);
		fclose(soubor); // Soubor je stale otevreni, pred skoncenim ho musime zavrit
		return 1;
	}

	// Presuneme se zase na zacatek souboru
	fseek(soubor, 0, SEEK_SET);

    nejkratsi = nejmensi_pocet_znaku(soubor);

    fseek(soubor, 0, SEEK_SET);

	// Zobrazime posledni radku
	//zobraz_posledni_radky(soubor, pocet_radku, celkem_radku);
    zapis_radky_do_souboru(vystup,soubor,pocet_radku,celkem_radku,nejkratsi);

	// Zavreme soubor
	fclose(soubor);
	fclose(vystup);

	return 0;
}
