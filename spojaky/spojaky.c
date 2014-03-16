/*
 * spoaky.c
 * program ktery pomoci spooveho seznamu pracuje se zaznamy o cloveku a umi:
 *      - nacist do seznamu data ze souboru
 *      - ulozit data seznamu do souboru
 *      - pridat zaznam do seznamu
 *      - odebrat zaznam ze souboru
 *
 * program je konstruovan tak, ze hlavni funkce main() obsauje:
 *      - vypis vsech zaznamu v seznamu, pokud tedy nejake jsou :)
 *      - menu pro vyvolani jednotlivych fukcionalit programu
 *
 * deklarace funkce main() musi byt az na konci po deklaraci vsech ostatnich funkci
 */

//deklarace hlavicek preprocesoru
#include <stdio.h>
#include <stdlib.h>

/*
 * Toto je hotovy program - vsechny ukoly ze cviceni jsou vyresene.
 */

/*
 * definice noveho datoreho typu pro strukturu "CLOVEK" naseho spojoveho seznamu a vytvoreni promenne "clovek" typu "CLOVEK"
 * struktura bude obsahovat:
 *      - jmeno - char [20] znaci ze se jesna o pole znaku o delce 20 tzn. promenna muze nest textovy retezec o max delce 20 znaku
 *      - prijmeni - dtto
 *      - vyska - cele cislo
 *      - vaha - dtto
 *      - clovek - ukazatel dalsi na typ CLOVEK, bude pouzit pro neseni informace jaky zaznam je v seznamu dalsi
 */
typedef struct clovek {
    char jmeno[20];
    char prijmeni[20];
    int vyska;
    int vaha;
    struct clovek *dalsi;
} CLOVEK;

// Zde je zacatek spojoveho seznamu
CLOVEK *prvni = NULL;

/*
 * Tato funkce vlozi noveho cloveka na zacatek seznamu
 * CLOVEK *cl, znamena ze funkce pri svem volani potrebuje parametr typu ukazatel na CLOVEK
 * ten se priradi do lokalniho pointru cl
 */
void vloz_na_zacatek(CLOVEK *cl) {
    cl->dalsi = prvni; //do polozky dalsi zaznamu poslaneho pri volani funkce se ulozi ukazatel na prvni polozku seznamu
    prvni = cl; // do ukazatele na prvnipolozku seznamu ulozi zaznam zaslany pri volani funkce
}

/*
 * Tato funkce vlozi noveho cloveka za jineho cloveka
 * tato funkce potrebuje pri volani dva parametry:
 *      - cl - zaznam ktery chceme vlozit
 *      - predchozi - zaznam predchazejici zaznamu za ktery jej chceme vlozit
 */
void vloz_za_cloveka(CLOVEK *predchozi, CLOVEK *cl) {
    cl->dalsi = predchozi->dalsi; // zkopiruje do polozky dalsi vkladaneho zaznamu obsah polozky dalsi zaznamu za ktery vkladame
    predchozi->dalsi = cl; // priradi do polozky dalsi zaznamu predchozi vkladany zaznam
}

/* Tato funkce odebere prvniho cloveka ze seznamu */
void odeber_ze_zacatku() {
    CLOVEK *odebrany; // vytvoreni promenne pro docasne drzeni zaznamu ktery odebirame, abychom ho predcasne neztratili

    if (prvni != NULL) { // pokud existuje prvni zaznam
        odebrany = prvni; // zkopirujeme si do promenne "odebrany" prvni zaznam
        prvni = odebrany->dalsi; //do ukazatele na prvni polozku zaznamu priradime aktualne druhy zaznam
        free(odebrany); // Uvolnime pamet! tzn. smazeme puvodni prvni zaznam
    }
}

/*
 * Tato funkce odebere cloveka nasledujiciho za zadanym clovekem!!!
 * potrebuje pri volani parametr obsahujici ukazatel na zaznam predchazejici odebiranemu zaznamu
 */
void odeber_za_clovekem(CLOVEK *predchozi) {
    CLOVEK *odebrany; // vytvoreni promenne pro docasne drzeni zaznamu ktery odebirame, abychom ho predcasne neztratili

    if (predchozi->dalsi != NULL) { // pokud existuje predchazejici zaznam
        odebrany = predchozi->dalsi; // zkopirujeme si do promenne "odebrany" zaznam ktery chceme odebrat
        predchozi->dalsi = odebrany->dalsi; // do ukazatele dalsi zaznamu predchazejiciho odebiranemu priradime ukazatel na zaznam nasledujici po odebiranem
        free(odebrany); // Uvolnime pamet tzn. smazeme pozadovany zaznam
    }
}

/*
 * Tato funkce nacte jednoho cloveka ze souboru a vrati ukazatel na tohoto cloveka
 * jako parametr pri volani ocekava ukazatel na sobor ze ktereho budeme cist
 */
CLOVEK *nacti_cloveka(FILE *f) {
    CLOVEK *cl; //vytvoreni promenne pro drzeni aktualniho nacteneho zaznamu
    int nactene_hodnoty; //promenna ktera nam bude drzet informaci kolik hodnot jsme nacetli

    /*
     * Alokujeme pamet
     * maloc(x) znamena ze alokujeme pametovy blok o velikosti x
     * sizeof(jmeno_promenne nebo nazev_datoveho_typu) vrati velikost pametoveho bloku kterou zabira dana promenna nebo dadovy typ
     * kombinace malloc(sizeof(CLOVEK)) tedy alokje pametovy blok o velikosti potrebne k ulozeni naseho zaznamu CLOVEK
     * tato nove misto priradime promenne cl promenna se bude jmenovat cl a bude typu ukazatel na datovy typ CLOVEK
     */
    cl = (CLOVEK *) malloc(sizeof(CLOVEK));
    if (cl == NULL) {//pokud se pamet nepodari alokovat
        printf("Neni dost pameti pro dalsiho cloveka.\n");//vypise na obrazovku "Neni dost pameti pro dalsiho cloveka."
        return NULL;//funkce se ukonci a vrati nulovy pointer
    }

    nactene_hodnoty = fscanf(f, "%19s %19s %d %d", cl->jmeno, cl->prijmeni, &cl->vyska, &cl->vaha); // Nacteme cloveka; u jmena a prijmeni neni &, protoze jsou to pole a ty se chovaji jako pointry
    if (nactene_hodnoty != 4) { // Potrebujeme 4 hodnoty, pokud je nemame, cloveka jsme nenacetli
        if (nactene_hodnoty != EOF) { // Pokud nejsme na konci souboru, byla v souboru chyba (pokud jsme na konci, chyba to neni a chybovou hlasku nevypiseme)
            printf("Nepodarilo se nacist cloveka, chyba vstupniho souboru.\n");//vypise na obrazovku "Nepodarilo se nacist cloveka, chyba vstupniho souboru."
        }
        free(cl); // Nacteni se nepovedlo, ale pamet je alokovana... uvolnime pamet
        return NULL;//funkce se ukonci a vrati nulovy pointer
    }

    cl->dalsi = NULL; // Vynulujeme ukazatel na dalsiho

    return cl; // Vratime cloveka
}

/*
 * Tato funkce nacte vsechny lidi ze souboru a kazdeho nacteneho5 vlozi na konec.
 * jako parametr pri volani ocekava ukazatel na sobor ze ktereho budeme cist
 */
void nacti_vsechny_lidi(FILE *f) {
    CLOVEK *cl;//vytvoreni promenne pro drzeni aktualniho nacteneho zaznamu
    CLOVEK *posledni = NULL; // Ukazatel na posledniho pridaneho cloveka - zatim je NULL, protoze jsme jeste nikoho nepridali

    cl = nacti_cloveka(f); // zavola funkci nacti_cloveka() a jeji vysledek ulozi do pomenne cl
    while (cl != NULL) { // dokud existuje dalsi clovek v souboru
        if (posledni == NULL) { // Pokud jsme jeste nikoho nepridali, dame cloveka na zacatek, jinak za posledniho cloveka
            vloz_na_zacatek(cl); // zavola funkci vloz_na_zacatek()
        } else { // pokud uz v seznamu existuje nejaky zaznam pridavame na konec
            vloz_za_cloveka(posledni, cl); // zavola funkci vloz_za_cloveka() s parametry "posledni" - ukazatel na posledni zaznam a "cl" - ukazatel na aktualni zaznam
        }
        posledni = cl; // Zapamatujeme si, ze pridany clovek je zatim posledni
        cl = nacti_cloveka(f); // nacteme dalsiho cloveka ze souboru
    }
}

/* Tato funkce ulozi vsechny lidi do souboru.
 * jako parametr pri volani ocekava ukazatel na sobor do ktereho chceme ukladat
 */
void uloz_vsechny_lidi(FILE *f) {
    CLOVEK *cl; //vytvoreni promenne pro drzeni aktualniho nacteneho zaznamu

    cl = prvni; // nacteme prvni zaznam seznamu jako aktualni
    while (cl != NULL) { // dokud existuje zaznam v seznamu
        fprintf(f, "%s %s %d %d\n", cl->jmeno, cl->prijmeni, cl->vyska, cl->vaha); // vlozi do sounoru radek ze zaznamem ve formatu "Jmeno Prijmeni Vyska Vaha"
        cl = cl->dalsi; // nacte do ukazatele na aktualniho cloveka ukazatel na dalsi zaznam v seznamu
    }
}

/*
 * Tato funkce vypise vsechny lidi.
 * Podle vzorce pro vypocet BMI (VAHA deleno (VYSKA V METRECH na druhou))
 * Podle BMI zobrazi text "moc hubeny" (pro BMI < 20), "moc tlusty" (pro BMI > 25) nebo "akorat".
 * Pred kazdym clovekem vypise jeho poradove cislo (od 1).
 */

void vypis_vsechny_lidi() {
    CLOVEK *cl; //vytvoreni promenne pro drzeni aktualniho nacteneho zaznamu
    float bmi = 0; // vytvoreni promenne pro drzeni hodnoty bmi aktualne nacteneho cloveka
    int poradi = 1; // vytvoreni promenne pro drzeni poradoveho cisla aktualne nacteneho cloveka

    printf("Cislo Jmeno               Prijmeni            Vyska  Vaha   BMI\n"); // vypis hlavicky seznamu na obrazovku
    printf("---------------------------------------------------------------\n"); // oddelovac. Ciste proto aby to bylo na obrazovce hezke :)

    cl = prvni; // jako aktualni zaznam nacteme prvni zaznam seznamu
    while (cl != NULL) {// dokud existuje zaznam v seznamu
        bmi = (float) cl->vaha / ((float) cl->vyska * cl->vyska / 10000); // vypocteme BMI; int musime prevest na float; 10000 = 100 * 100 (protoze vysku v cm delime 100)
        printf("%5d %-19s %-19s %5d %5d %5.1f", poradi, cl->jmeno, cl->prijmeni, cl->vyska, cl->vaha, bmi); // vypiseme poradi polozky zaznamu a hodnotu bmi
        if (bmi < 20) { // podminka pro vyhodnoceni bmi
            printf(" moc hubeny"); // vypis textu
        } else if (bmi > 25) {
            printf(" moc tlusty");
        } else {
            printf(" akorat");
        }
        printf("\n"); // ukonceni  radku
        poradi++; // zvysime poradi o 1
        cl = cl->dalsi; // nacte do ukazatele na aktualniho cloveka ukazatel na dalsi zaznam v seznamu
    }
}

/* Tato funkce provede cele nacteni lidi ze souboru. */
void nacti() {
    char nazev_souboru[261]; // promenna typu pole znaku o delce 261 - to v praxi znamena ze so nej muzeme ulozit informaci o maximalni delce 261 znaku
    FILE *soubor; // promenna pro ukazatel na soubor ze ktereho chceme nacitat

    // Uzivatel zada nazev souboru
    printf("Zadej nazev souboru: "); // vypis na obrazovku
    if (scanf("%260s", nazev_souboru) != 1) { // pokud se nepodari nacist zadany text
        printf("Chyba zadani.\n"); // vypiseme chybu
        return; //ukoncime funkci
    }
    getchar();// odmazeme enter ktery nam zbyl v pameti

    soubor = fopen(nazev_souboru, "r"); // Otevreme soubor v rezimu pro cteni a ulozime pointr na nej do promenne soubor
    if (soubor == NULL) { // pokud se otevreni nezdarilo
        printf("Soubor %s nelze otevrit.\n", nazev_souboru); // vypiseme chybu
        return; // ukoncime funkci
    }

    // Nacteme lidi
    nacti_vsechny_lidi(soubor);

    // Zavreme soubor
    fclose(soubor);

    printf("Lidi byli nacteni.\n");
}

/* Tato funkce provede cele ulozeni do souboru. */
void uloz() {
    char nazev_souboru[261];
    char odpoved;
    FILE *soubor;

    // Uzivatel zada nazev souboru
    printf("Zadej nazev souboru: ");
    if (scanf("%260s", nazev_souboru) != 1) {
        printf("Chyba zadani.\n");
        return;
    }
    getchar();

    // Zkontrolujeme, zda soubor existuje
    soubor = fopen(nazev_souboru, "r");
    if (soubor != NULL) {
        fclose(soubor);
        printf("Soubor %s existuje. Prepsat? [A/N] ", nazev_souboru);
        odpoved = getchar();
        getchar();
        if (odpoved != 'A' && odpoved != 'a') {
            return;
        }
    }

    // Otevreme soubor
    soubor = fopen(nazev_souboru, "w");
    if (soubor == NULL) {
        printf("Soubor %s nelze otevrit pro zapis.\n", nazev_souboru);
        return;
    }

    // Ulozime lidi
    uloz_vsechny_lidi(soubor);

    // Zavreme soubor
    fclose(soubor);

    printf("Lidi byli ulozeni.\n");
}

/* Tato funkce prida do seznamu noveho cloveka, udaje zada uzivatel.

   UKOL: Napiste tuto funkci.
         Vyberte si, jestli pridate cloveka na zacatek nebo na konec (pouzijte hotove funkce vloz_na_zacatek nebo vloz_za_cloveka).
         Dejte pozor, abyste uvolnili pamet, pokud se nepodari nacist hodnoty. */
void pridej() {
    CLOVEK *novy;
    CLOVEK *posledni; // Potrebujeme jen pokud budeme pridavat na konec

    // Alokujeme pamet a pak nacitame hodnoty do alokovaneho cloveka.
    // Pokud se nacteni nepovede, musime pamet uvolnit funkci free().

    // Alternativne bychom mohli nejdriv nacist hodnoty do zvlastnich promennych, pak alokovat pamet a hodnoty zkopirovat.
    // ...nemuseli bychom volat funkci free()
    // ...ovsem potrebovali bychom extra promenne, ktere bychom pak museli kopirovat
    // ...a kdyby nebylo dost pameti, stejne by uzivatel musel vsechno vyplnit a pak teprve by se dozvedel o chybe

    novy = (CLOVEK *) malloc(sizeof(CLOVEK));
    if (novy == NULL) {
        printf("Neni dost pameti pro dalsiho cloveka.\n");
        return;
    }

    printf("Krestni jmeno: ");
    if (scanf("%19s", novy->jmeno) != 1) {
        printf("Chyba zadani.\n");
        free(novy);
        return;
    }
    getchar();

    printf("Prijmeni: ");
    if (scanf("%19s", novy->prijmeni) != 1) {
        printf("Chyba zadani.\n");
        free(novy);
        return;
    }
    getchar();

    printf("Vyska: ");
    if (scanf("%d", &novy->vyska) != 1) {
        printf("Chyba zadani.\n");
        free(novy);
        return;
    }
    getchar();

    printf("Vaha: ");
    if (scanf("%d", &novy->vaha) != 1) {
        printf("Chyba zadani.\n");
        free(novy);
        return;
    }
    getchar();

    novy->dalsi = NULL;

    // Varianta A: Pridani na zacatek
    //vloz_na_zacatek(novy);

    // Varianta B: Pridani na konec
    if (prvni == NULL) {
        // Pokud je seznam prazdny, vlozime na zacatek (zadny konec jeste neni)
        vloz_na_zacatek(novy);
    } else {
        // Jinak najdeme posledniho cloveka a pridame za nej
        // Posledniho cloveka pozname podle toho, ze jeho ukazatel na dalsiho je NULL
        posledni = prvni;
        while (posledni->dalsi != NULL) {
            posledni = posledni->dalsi;
        }
        // Pridame za posledniho
        vloz_za_cloveka(posledni, novy);
    }

    printf("Novy clovek byl pridan.\n");
}

/* Tato funkce odebere cloveka ze seznamu, poradove cislo cloveka zada uzivatel.

   UKOL: Napiste tuto funkci (vyuzijte hotove funkce odeber_ze_zacatku a odeber_za_clovekem).
         Dejte pozor, zda clovek se zadanym poradovym cislem skutecne existuje. */
void odeber() {
    int cislo;
    CLOVEK *cl, *predchozi = NULL;

    if (prvni == NULL) {
        printf("Seznam je prazdny, nelze nikoho odebrat.\n");
        return;
    }

    // Uzivatel zada cislo cloveka k odebrani
    printf("Zadej cislo cloveka k odebrani: ");
    if (scanf("%d", &cislo) != 1) {
        printf("Chyba zadani.\n");
        return;
    }
    getchar();

    if (cislo < 1) {
        printf("Cislo nesmi byt mensi nez 1.\n");
        return;
    }

    // Projdeme seznam a najdeme n-teho cloveka
    // Musime si ovsem vzdycky pamatovat, ktery byl pred nim, abychom mohli odebirat
    cl = prvni;
    predchozi = NULL;
    while (cislo > 1 && cl != NULL) { // Opakujeme, dokud je cislo > 1
        predchozi = cl;
        cl = cl->dalsi;
        cislo--; // A po kazdem cloveku cislo snizime
    }

    // Pokud bylo cislo moc velke, prosli jsme cely seznam a nenasli jsme nic
    if (cl == NULL) {
        printf("Toto cislo neni v seznamu.\n");
        return;
    }

    if (predchozi == NULL) {
        // Pokud neni zadny predchozi clovek, znamena to, ze odstranujeme ze zacatku (tzn. cislo bylo 1)
        odeber_ze_zacatku();
    } else {
        // Pokud mame predchoziho cloveka, odstranime toho za nim (to je nas clovek k odstraneni)
        odeber_za_clovekem(predchozi);
    }

    printf("Clovek byl odebran.\n");
}

int main() {
    int volba;

    do {
        // Zobrazime lidi
        printf("\nSeznam lidi\n-----------\n");
        vypis_vsechny_lidi();

        // Zobrazime menu
        printf("\n\nMenu:\n-----\n");
        printf("C ... Nacist lidi ze souboru\n");
        printf("U ... Ulozit lidi do souboru\n");
        printf("P ... Pridej dalsiho cloveka\n");
        printf("D ... Odeber cloveka\n");
        printf("K ... Konec\n");

        // Uzivatel zada, co chce delat
        printf("Vase volba? ");
        volba = getchar();
        getchar();

        // Podle volby neco udelame
        switch (volba) {
        case 'C':
        case 'c':
            nacti();
            break;
        case 'U':
        case 'u':
            uloz();
            break;
        case 'P':
        case 'p':
            pridej();
            break;
        case 'D':
        case 'd':
            odeber();
            break;
        case 'K':
        case 'k':
            // Nedelej nic, budeme koncit
            break;
        default:
            printf("Neplatna volba, zkuste to znovu.\n");
        }

    } while (volba != 'k' && volba != 'K');

    return 0;
}

