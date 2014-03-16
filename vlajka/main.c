#include <stdio.h>
#include <stdlib.h>

int main()
{
    int r, s;
    int max_r, max_s; // Promenne pro pocet radku a sloupcu.

    printf("Zadej pocet radku: ");
    scanf("%d", &max_r); // Nechame uzivatele aby zadal pocet radku. "%d" znamena ze cteme cele cislo, ulozime ho do promenne max_r. &max_r znamena adresu promenne max_r.
    printf("Zadej pocet sloupcu: ");
    scanf("%d", &max_s); // Pocet sloupcu; zatim neresime, co se stane, kdyz uzivatel zada neco jineho nez cislo, nezkousejte to, naucime se pozdeji.

    for (r = 1; r <= max_r; r++) {
        for (s = 1; s <= max_s; s++) {
            if (r >= s && r + s <= max_r+1) {
                printf(".");
            } else if(r>(max_r/2)) {
                printf("X");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
    return 0;
}
