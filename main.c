#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "ido.h"
#include "megallo.h"
#include "jarat.h"

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

    // hány db elválasztó van a sor-ba -> ennyi paraméter lesz + 1
    int spaces = 1;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == elvalaszto) {
            spaces++;
        }
    }
    char **temp_sor = (char**) malloc((spaces+1) * sizeof(char*));

    // sor szétválogatása
    spaces = 0;
    temp_sor[0] = (char*) malloc(101 * sizeof(char));
    int j = 0;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == elvalaszto) {
            temp_sor[spaces][j] = '\0';
            spaces++;
            j = 0;
            temp_sor[spaces] = (char*) malloc(101 * sizeof(char));
        } else {
            temp_sor[spaces][j++] = sor[i];
        }
    }
    temp_sor[spaces][j] = '\0';
    temp_sor[spaces+1] = "-1";

    return temp_sor;
}

int main() {
    // megállók és járatok listája
    Jarat* elso_jarat;
    Megallo *elso_megallo;

    //alap fájlok beolvasása ha léteznek
    FILE *fajl = fopen("megallok.txt", "r");
    if (fajl) {
        elso_megallo = mbeolvas_fg(fajl);
        fclose(fajl);
    }
    fajl = fopen("jaratok.txt", "r");
    if (fajl) {
        elso_jarat = beolvas_fg(fajl, elso_megallo);
        fclose(fajl);
    }

    bool futas = true;
    char sor[100+1]; //100 karakter, hogy beleféljen fájl elérési út is ha szükséges (magában 50 karakter kb)
    char **parancssor = NULL;
    while (futas) {
        printf("\nParancs(max 100 karakter):");
        if (fgets(sor, 101, stdin) == NULL) {
            printf("Hiba a sor beolvasasanal.");
        }

        // előző parancs futtatása
        if (strcmp(sor, "up\n")  != 0) {
            if (parancssor != NULL) {
                // előző memória felszabadítása
                for (int i = 0; strcmp(parancssor[i], "-1") != 0; ++i) {
                    free(parancssor[i]);
                }
                free(parancssor);
            }

            parancssor = sor_to_list(sor);
        } else {
            int i;
            for (i = 0; strcmp(parancssor[i+1], "-1") != 0; ++i) {
                printf("%s-", parancssor[i]);
            }
            printf("%s", parancssor[i]);
            printf("\n");
        }

        switch (str_to_parancs(parancssor[0])) {
            case segitseg:
                printf("Parancsok: up, segitseg, mbeolvas, beolvas, mmentes, mentes, kiir, megallo, utvonal, kilep\n");
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
                break;
            case kilep:
                printf("Kilepes!\n");
                // memória felszabadítása
                for (int i = 0; strcmp(parancssor[i], "-1") != 0; ++i) {
                    free(parancssor[i]);
                }
                free(parancssor);
                for (int i = 0; i < jaratok.meret; ++i) {
                    free(jaratok.tomb[i].nev);
                    free(jaratok.tomb[i].idopontok);
                    free(jaratok.tomb[i].megallok);
                }
                free(jaratok.tomb);
                for (int i = 0; i < megallok.meret; ++i) {
                    free(megallok.tomb[i].nev);
                    for (int j = 0; j < megallok.tomb[i].meret; ++j) {
                        free(megallok.tomb[i].atszallasok[j]);
                    }
                    free(megallok.tomb[i].atszallasok);
                }
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
