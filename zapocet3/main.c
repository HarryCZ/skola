
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

/* Funkce zobrazi poslednich nekolik radku ze souboru.
 * Parametry:
 *  pocet_radku = pocet radku, ktere se maji zobrazit
 *  celkem_radku = celkovy pocet radku v souboru

void zobraz_posledni_radky(FILE *soubor, int pocet_radku, int celkem_radku) {
	int radek = 1; // Pocitadlo radku, prvni radek ma cislo 1
	int znak;

	for (znak = fgetc(soubor); znak != EOF; znak = fgetc(soubor)) {
		if (radek > celkem_radku - pocet_radku) { // Pokud aktualni radek patri mezi posledni radky, zobrazime znak
			putchar(znak);
		}
		if (znak == '\n') { // Pokud najdeme konec radku, zvysime pocitadlo radku o 1
			radek++;
		}
	}
}
*/
int zapis_radky_do_souboru(FILE *vystup,FILE *soubor, int pocet_radku, int celkem_radku) {
    int radek = 1; // Pocitadlo radku, prvni radek ma cislo 1
	int znak;

	for (znak = fgetc(soubor); znak != EOF; znak = fgetc(soubor)) {
		if (radek <= pocet_radku) { // Pokud aktualni radek patri mezi posledni radky, zobrazime znak
			fputc(znak,vystup);
		}
		if (znak == '\n') { // Pokud najdeme konec radku, zvysime pocitadlo radku o 1
			radek++;
		}
	}

	return 0;
}

int main() {
	char nazev_souboru[256];
	char nazev_souboru2[256];
	int celkem_radku, pocet_radku;
	int celkem_radku2, pocet_radku2;
	FILE *soubor,*soubor2,*vystup;

	// Nacteme nazev souboru a zkontrolujeme, ze uzivatel neco zadal
	printf("Zadej nazev souboru: ");
	if (scanf("%255s", nazev_souboru) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}
	printf("Zadej nazev 2. souboru: ");
	if (scanf("%255s", nazev_souboru2) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}

	// Nacteme pocet radku, ktere se maji zobrazit, a zkontrolujeme, ze uzivatel neco zadal
	printf("Zadej pocet radku: ");
	if (scanf("%d", &pocet_radku) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}

	printf("Zadej 2. pocet radku: ");
	if (scanf("%d", &pocet_radku2) != 1) {
		printf("Chyba zadani.\n");
		return 1;
	}

	// Zkusime otevrit soubor a zkontrolujeme vysledek
	soubor = fopen(nazev_souboru, "r");
	if (soubor == NULL) {
		printf("Soubor nelze otevrit.\n");
		return 1;
	}

	soubor2 = fopen(nazev_souboru2, "r");
	if (soubor2 == NULL) {
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
	celkem_radku2 = spocitej_radky(soubor2);

	// Overime, ze pocet radku, ktere se maji zobrazit, je v povolenem rozsahu
	if (pocet_radku < 1 || pocet_radku > celkem_radku) {
		printf("Pocet radku musi byt mezi %d a %d.\n", 1, celkem_radku);
		fclose(soubor); // Soubor je stale otevreni, pred skoncenim ho musime zavrit
		return 1;
	} else if (pocet_radku2 < 1 || pocet_radku2 > celkem_radku2) {
		printf("Pocet radku musi byt mezi %d a %d.\n", 1, celkem_radku2);
		fclose(soubor2); // Soubor je stale otevreni, pred skoncenim ho musime zavrit
		return 1;
	}

	// Presuneme se zase na zacatek souboru
	fseek(soubor, 0, SEEK_SET);
	fseek(soubor2, 0, SEEK_SET);

	// Zobrazime posledni radku
	//zobraz_posledni_radky(soubor, pocet_radku, celkem_radku);
    zapis_radky_do_souboru(vystup,soubor,pocet_radku,celkem_radku);
    zapis_radky_do_souboru(vystup,soubor2,pocet_radku2,celkem_radku2);

	// Zavreme soubor
	fclose(soubor);
	fclose(soubor2);
	fclose(vystup);

	return 0;
}
