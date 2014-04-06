

#include <stdio.h>
#include <stdlib.h>

int zjisti_prumerny_radek(FILE *soubor) {// tato funkce zjisti nejkratsi neprazdny radek a vrati pocet znaku v radku
    int znak;
    int pocet_znaku_v_radku = -1;
    int prumer = 0;
    int radek = 0;

    while (znak != EOF) {//cyklus se opakuje dokud neni konec souboru
        if (znak != '\n') {//tato podminka zamezuje zapocitani zalomeni radku
            pocet_znaku_v_radku++;
        }else{
           radek++;
           prumer = prumer + pocet_znaku_v_radku;
           pocet_znaku_v_radku = 0;//pocet znaku musime vynulovat, protoze budeme pocitat dalsi radek
        }
        znak = fgetc(soubor);//nacteme dalsi znak
    }

    prumer = prumer / radek;

    return prumer;//vracime pocet znaku v minimalnim radku
}

int smim_prepsat(char *nazev_souboru) {// tato funkce je zkopirovana z moodlu, je tam i okomentovan
	FILE *soubor;
	int volba;
	int tmp;

	soubor = fopen(nazev_souboru, "r");
	if (soubor != NULL) {

		fclose(soubor);

		printf("Soubor '%s' existuje, prepsat? [A/N] ", nazev_souboru);
		volba = getchar();

		tmp = volba;
		while (tmp != EOF && tmp != '\n' && tmp != '\r') {
			tmp = getchar();
		}

		return volba == 'A' || volba == 'a';

	} else {
		return 1;
	}
}

int delka_vstupu(char *nazev_souboru) {//tato funkce spocita pocet radku v souboru a vrati pocet, v teto funkci pocitany soubor otevrem i zavrem, abychom se souborem mohli pracovat dale od zacatku
    FILE *soubor;
    int nacti_znak = 0;
    int pocet_radku = 1;

    soubor = fopen(nazev_souboru, "r");//otevreme soubor
    if (soubor != NULL) {//zjistime zda soubor existuje
        while (nacti_znak != EOF) {//opakujem dokud neni konec souboru
            if (nacti_znak == '\n') {// kdz se znak rovna \n zapocitame radek
                pocet_radku++;
            }
            nacti_znak = fgetc(soubor);//nacteme dalsi soubor
        }
        return pocet_radku;//vracime pocet radku
    } else {
        return 0;//vracime nulu pokud soubor neexistuje
    }
    fclose(soubor);//zavreme soubor
}

int existuje_soubor(char *nazev_souboru) {// jednoducha funkce pro zjisteni zda existuje zadany soubor pokud existuje vraci 1 jako true pokud neexistuje vracime 0
    FILE *soubor;

    soubor = fopen(nazev_souboru, "r");//otevreme soubor
    if (soubor == NULL) {//kdyz se soubor rovna null tak neexistuje, proto vracime 0
        return 0;
    } else {
        return 1;
    }
    fclose(soubor);//zavreme soubor
}

int main()
{
    char nazev_souboru[300];
    int n;
    FILE *vstup;
    FILE *vystup1;
    FILE *vystup2;

    printf("Zadej nazev vstupu:\n");
    scanf("%299s", nazev_souboru);
    getchar();
    while (!existuje_soubor(nazev_souboru)) {//tento cyklus se opakuje dokud uzivatel nezada nazev existujiciho souboru, ktomu nam poslouzi vyse popsana funkce
        printf("Soubor %s neexistuje. Zadejte nazev souboru:\n", nazev_souboru);
        scanf("%299s", nazev_souboru);
        getchar();
    }
    printf("Zadej N:\n");
    scanf("%d", &n);
    getchar();
    while (n >= delka_vstupu(nazev_souboru)) {//tento cyklus se opakuje dokud uzivatel nezada cislo n mensi nez pocet radku ve vstupnim souboru, k tomu nam poslouzi funkce pro spocitani radku
        printf("N musi byt menci nez %d, zadali jste %d. Zadej N:\n", delka_vstupu(nazev_souboru), n);
        scanf("%d", &n);
        getchar();
    }
    printf("Pocet radku v souboru je: %d\n", delka_vstupu(nazev_souboru));//zde vypiseme pocet radku ve vstupnim souboru

    vstup = fopen(nazev_souboru, "r");//na techto trech radcich zjistujeme nejkratsi radek pomoci vyse uvedene funkce a hodnotu ulozime do promene r se kterou budeme pracovat
    int r = zjisti_prumerny_radek(vstup);
    printf("Prumerny radek ma: %d znaku\n", r);
    fclose(vstup);//soubor musime zavrit, abychom mohli pracovat znovu od zacatku souboru

    vstup = fopen(nazev_souboru, "r");//otevreme soubor
    if (smim_prepsat("vystup1.txt") && smim_prepsat("vystup2.txt")) {//zjistime zda muzeme vystupni soubory prepsat
        vystup1 = fopen("vystup1.txt", "w");
        vystup2 = fopen("vystup2.txt", "w");
        int znak;
        int pocet_znaku = 0;
        int pocet_radku = 1;
        if (vstup != NULL) {//zjistime, jestli vstupni soubor existuje
            znak = fgetc(vstup);//nacteme znak
            while (znak != EOF && pocet_radku <= n) {//opakujem dokud neni konec souboru a dokud je pocet radku mensi rovno nez zadane n
                pocet_znaku++;//pocet znaku zvisime o jedna
                if (pocet_znaku <= r) {
                    fputc(znak, vystup1);
                }else{
                    fputc(znak, vystup2);
                }
                if (znak == '\n') {//kdyz je znak \n vynulujem pocet znaku, abychom mohli pocitat novy radek a zapocitame dalsi radek
                    if (pocet_znaku > r) {
                        fputc('\n', vystup1);
                    }else{
                        fputc('\n', vystup2);
                    }
                    pocet_znaku = 0;
                    pocet_radku++;
                }
                znak = fgetc(vstup);//nacteme dalsi znak
            }
        }
        fclose(vystup1);
        fclose(vystup2);
    }
    fclose(vstup);

    return 0;
}
