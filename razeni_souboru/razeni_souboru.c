#include <stdio.h>
#include <stdlib.h>

int serad_pole(int pole[100], int r) {
    int i,j,pom;
    for(i=0; i <= r-1; i++) {
        for(j=0; j <= r-1; j++) {
            if (pole[j] > pole[i]) {
                pom = pole[i];
                pole[i] = pole[j];
                pole[j] = pom;
            }
        }
    }
    return 0;
}

int uloz_do_souboru(int pole[100], int r, FILE *f) {
    int i;

    for (i=0; i<r; i++) {
        fputc(pole[i], f);
        fprintf(f, "\n");
    }
    return 0;
}

int main()
{
    FILE *soub, *serazeny;
    int znak;
    int radek = 0;
    int pole[100];


    soub=fopen("soubor.txt", "r");
    if (soub != NULL) {
        serazeny=fopen("serazeny.txt", "w");
        if (serazeny != NULL) {
            znak = fgetc(soub);
            while (znak != EOF) {
                if (isdigit(znak) && (znak % 2 == 0)) {
                    pole[radek]=znak;
                    radek++;
                }
                znak = fgetc(soub);
            }
            serad_pole(pole, radek);
            uloz_do_souboru(pole, radek, serazeny);

            fclose(serazeny);
        }

        fclose(soub);
    }



    system("PAUSE");
    return 0;
}
