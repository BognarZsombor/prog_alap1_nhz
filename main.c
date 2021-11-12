#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ido.h"
#include "megallo.h"
#include "jarat.h"

/* Tevékenységlista: mindig van idopont és megálló.
 * Ha átszállás történt az adott megállóból a következőbe, akkor a járat NULL
 * Az idopont utolsó eleme mindig az aktuális utazásiidő
 * */
typedef struct {
    Megallo *megallok;
    Jarat *jaratok;
    Ido *idopontok;
    int meret;
} Utvonal;

typedef struct {
    Utvonal *tomb;
    int meret;
} Utvonal_tomb;

typedef enum {segitseg, mbeolvas, beolvas, mentes, mmentes, kiir, megallo, utvonal, kilep, hibas} parancsok;

/* str_to_parancs
 * A beérkető string alapján visszaadja a hozzátartozó parancsot
 * @param char parancs A beérkező string
 * @return int A strinhez tartozó parancs enum alapján
 * */
int str_to_parancs(char *parancs) {
    if (strcmp(parancs, "segitseg") == 0)
        return segitseg;
    if (strcmp(parancs, "mbeolvas") == 0)
        return mbeolvas;
    else if (strcmp(parancs, "beolvas") == 0)
        return beolvas;
    else if (strcmp(parancs, "kiir") == 0)
        return kiir;
    else if (strcmp(parancs, "mentes") == 0)
        return mentes;
    else if (strcmp(parancs, "mmentes") == 0)
        return mmentes;
    else if (strcmp(parancs, "megallo") == 0)
        return megallo;
    else if (strcmp(parancs, "utvonal") == 0)
        return utvonal;
    else if (strcmp(parancs, "kilep") == 0)
        return kilep;
    else
        return hibas;
}

/* sor_to_list
 * Szétszedi a beadott sort egy stringekből álló listára, aminek az első eleme a parancs, a többi pedig a hozzá tartozó paraméterek.
 * @param char* sor A beérkező string
 * @return char** A szóközött alapján szétszedett stringlista
 * */
char **sor_to_list(char const sor[]) {
    char elvalaszto = '-';

    // a sor eleji felesleges spacek kihagyása
    int k;
    for (k = 0; sor[k] == ' '; ++k) {
        k++;
    }

    // hány db elválasztó van a sor-ba -> hány paraméter lesz
    int spaces = 0;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == elvalaszto) {
            spaces++;
        }
    }
    char **temp_sor = (char**) malloc(spaces * sizeof(char*));

    // sor szétválogatása
    spaces = 0;
    temp_sor[0] = malloc(101 * sizeof(char));
    int j = 0;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == elvalaszto) {
            temp_sor[spaces][j] = '\0';
            spaces++;
            j = 0;
            temp_sor[spaces] = malloc(101 * sizeof(char));
        } else {
            temp_sor[spaces][j++] = sor[i];
        }
    }
    temp_sor[spaces][j] = '\0';

    return temp_sor;
}

/* utvonal_seged_fg
 * Az utvonalban van tárolva, hogy hol tartunk utazási időben. Az aktuális útvonal az utvonalban van tárolva.
 * Az összes útvonal az utvonalakban van tárolva.
 * */
void utvonal_seged_fg(Megallo_tomb megallok, Jarat_tomb jaratok, Megallo m1, Megallo m2, Ido *indulasi_ido, Utvonal_tomb *utvonalak, Utvonal *utvonal) {
    /*if (strcmp(m1.nev, m2.nev) == 0) {
        // hozzáadás a kész útvonalakhoz
        utvonalak->meret++;
        utvonalak->tomb = (Utvonal*) realloc(utvonalak->tomb, utvonalak->meret * sizeof(Utvonal));
        utvonalak->tomb[utvonalak->meret-1] = *utvonal;
    } else {
        // átszállás
        utvonal->m_meret++;
        utvonal->megallok = (Megallo*) realloc(utvonal->megallok, utvonal->m_meret * sizeof )
        for (int i = 0; i < m1.meret; ++i) {
            utvonal
        }
        // járat következő megállója
        for (int i = 0; i < jaratok.meret; ++i) {
            for (int j = 0; j < jaratok.tomb[i].meret; ++j) {
                
            }
        }
    }*/
}

void utvonal_fg(Megallo_tomb megallok, Jarat_tomb jaratok, char *k, char *v, char *ora) {
    /*if (megallo_keres(megallok, k) == NULL || megallo_keres(megallok, v) == NULL) {
        printf("Nincsenek ilyen megállók!");
        return;
    }
    Megallo m1 = *megallo_keres(megallok, k);
    Megallo m2 = *megallo_keres(megallok, v);
    Ido indulasi_ido = str_to_ido(ora);

    utvonal_seged_fg(megallok, jaratok, m1, m2, &indulasi_ido);*/
}

int main() {
    // megállók és járatok listája
    Jarat_tomb jaratok;
    Megallo_tomb megallok;

    //alap fájlok beolvasása ha léteznek
    FILE *fajl = fopen("megallok.txt", "r");
    if (fajl) {
        megallok = mbeolvas_fg(fajl);
    }
    fclose(fajl);
    fajl = fopen("jaratok.txt", "r");
    if (fajl) {
        jaratok = beolvas_fg(fajl, megallok);
    }
    fclose(fajl);

    bool futas = true;
    char sor[100+1]; //100 karakter, hogy beleféljen fájl elérési út is ha szükséges (magában 50 karakter kb)
    while (futas) {
        printf("\nParancs(max 100 karakter):");
        if (fgets(sor, 101, stdin) == NULL) {
            printf("Hiba a sor beolvasasanal.");
        }
        char **parancssor = sor_to_list(sor);
        switch (str_to_parancs(parancssor[0])) {
            case segitseg:
                printf("Parancsok: segitseg, mbeolvas, beolvas, mmentes, mentes, kiir, megallo, utvonal, kilep\n");
                break;
            case mbeolvas:
                fajl = fopen(parancssor[1], "r");
                Megallo_tomb temp_megallok;
                if (fajl) {
                    temp_megallok = mbeolvas_fg(fajl);
                    megallok_hozzaad(megallok, temp_megallok);
                    free(temp_megallok.tomb);
                }
                fclose(fajl);
                break;
            case beolvas:
                fajl = fopen(parancssor[1], "r");
                Jarat_tomb temp_jaratok;
                if (fajl) {
                    temp_jaratok = beolvas_fg(fajl, megallok);
                    jarat_hozzaad(jaratok, temp_jaratok);
                    free(temp_jaratok.tomb);
                }
                fclose(fajl);
                break;
            case mentes:
                fajl = fopen(parancssor[1], "w");
                if (fajl) {
                    mentes_fg(jaratok, fajl);
                    printf("Fájl elmentve!\n");
                }
                break;
            case mmentes:
                fajl = fopen(parancssor[1], "w");
                if (fajl) {
                    mmentes_fg(megallok, fajl);
                    printf("Fájl elmentve!\n");
                }
                break;
            case kiir:
                kiir_fg(jaratok, parancssor[1]);
                break;
            case megallo:
                megallo_fg(jaratok, megallok, parancssor[1]);
                break;
            case utvonal:
                utvonal_fg(megallok, jaratok, parancssor[1], parancssor[2], parancssor[3]);
                break;
            case kilep:
                printf("Kilepes!\n");
                free(jaratok.tomb);
                free(megallok.tomb);
                futas = false;
                break;
            case hibas:
                printf("Nincs ilyen parancs.\n");
                break;
        }
    }

    return 0;
}
