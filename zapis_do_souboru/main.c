#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f;
    char str[255];
    f=fopen("soubor.txt", "w");
    if (f != NULL) {
        printf("Zadej slovo: ");
        scanf("%s", str);
        fprintf(f,"%s",str);
        fclose(f);
    }
    return 0;
}
