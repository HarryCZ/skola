#include <stdio.h>
#include <stdlib.h>

int main()
{
int radek;
int sloupec;
char a,b,c;
int x,y;

printf("zadej pocet radku: ");
scanf("%d", &radek);
getchar();

printf("zadej pocet sloupcu: ");
scanf("%d", &sloupec);
getchar();

printf("zadej prvni znak: ");
scanf("%c", &a);
getchar();

printf("zadej druhej zn. etak: ");
scanf("%c", &b);
getchar();

printf("zadej treti znak: ");
scanf("%c", &c);
getchar();

    for(x=1; x<=radek; x++)
    {
      for(y=1; y<=sloupec; y++)
      {

            if(x+y==(sloupec+radek)-3)
            printf("%c", b);

            else if(x+y==(sloupec+radek)-4)
            printf("%c", b);


          else if(x==radek-5)
            printf("%c", a);

          else if(x==radek-4)
            printf("%c", a);



          else
            printf("%c",c);
      }
      printf("\n");
    }
}
