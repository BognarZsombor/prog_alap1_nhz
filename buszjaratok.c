#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "debugmalloc.h"
#include "ido.h"
#include "megallo.h"
#include "jarat.h"
#include "utvonal.h"

typedef enum {segitseg, mbeolvas, beolvas, mentes, mmentes, jarat, megallo, utvonal, kilep, hibas} parancsok;

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
    else if (strcmp(parancs, "jarat") == 0)
        return jarat;
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

int main() {
    // megállók és járatok listája
    Jarat_list *elso_jarat;
    Megallo_list *elso_megallo;

    //alap fájlok beolvasása ha léteznek
    FILE *fajl = fopen("megallok.txt", "r");
    if (fajl) {
        elso_megallo = megallo_beolvas(NULL, fajl);
        fclose(fajl);
    }
    fajl = fopen("jaratok.txt", "r");
    if (fajl) {
        elso_jarat = jarat_beolvas(NULL, fajl, elso_megallo);
        fclose(fajl);
    }

    bool futas = true;
    char sor[101]; //100 karakter, hogy beleféljen fájl elérési út is ha szükséges (magában 50 karakter kb)
    char *parancssor[10];
    while (futas) {
        printf("\nParancs(max 100 karakter):");
        if (fgets(sor, 101, stdin) == NULL) {
            printf("Hiba a sor beolvasasanal.");
        }

        // string parancssorba átirása
        char elvalaszto[2] = "-";
        sor[strlen(sor)-1] = '\0';
        parancssor[0] = strtok(sor, elvalaszto);
        for (int i = 1; parancssor[i-1] != NULL; ++i) {
            parancssor[i] = strtok(NULL, elvalaszto);
        }

        switch (str_to_parancs(parancssor[0])) {
            case segitseg:
                printf("Parancsok: segitseg, mbeolvas, beolvas, mmentes, mentes, jarat, megallo, utvonal, kilep\n");
                break;
            case mbeolvas:
                fajl = fopen(parancssor[1], "r");
                if (fajl) {
                    elso_megallo = megallo_beolvas(elso_megallo, fajl);
                    fclose(fajl);
                }
                break;
            case beolvas:
                fajl = fopen(parancssor[1], "r");
                if (fajl) {
                    elso_jarat = jarat_beolvas(elso_jarat, fajl, elso_megallo);
                    fclose(fajl);
                }
                break;
            case mentes:
                fajl = fopen(parancssor[1], "w");
                if (fajl) {
                    jarat_mentes(elso_jarat, fajl);
                    printf("Fajl elmentve!\n");
                    fclose(fajl);
                } else {
                    printf("Fajl mentese nem sikerult!\n");
                }
                break;
            case mmentes:
                fajl = fopen(parancssor[1], "w");
                if (fajl) {
                    megallo_mentes(elso_megallo, fajl);
                    printf("Fajl elmentve!\n");
                    fclose(fajl);
                } else {
                    printf("Fajl mentese nem sikerult!\n");
                }
                break;
            case jarat:
            {
                Jarat *temp_j = jarat_keres(elso_jarat, parancssor[1]);
                if (temp_j != NULL) {
                    jarat_kiir(*temp_j);
                } else {
                    printf("Nincs ilyen jarat!\n");
                }
                break;
            }
            case megallo:
            {
                Megallo *temp_m = megallo_keres(elso_megallo, parancssor[1]);
                if (temp_m != NULL) {
                    megallo_kiir(*temp_m);
                } else {
                    printf("Nincs ilyen megallo!\n");
                }
                break;
            }
            case utvonal:
            {
                Megallo *start = megallo_keres(elso_megallo, parancssor[1]);
                Megallo *cel = megallo_keres(elso_megallo, parancssor[2]);
                if (start == NULL || cel == NULL) {
                    printf("Nem letezik ilyen megallo!\n");
                } else if (parancssor[3] == NULL) {
                    printf("Nincs idopont megadva!\n");
                } else {
                    start->tav = str_to_ido(parancssor[3]);
                    if (utvonal_keres(*start, *cel, elso_jarat) == 0) {
                        printf("Nincs elerheto utvonal a ket megallo kozott!\n");
                    }
                    // megállók távjának resetelése
                    for (Megallo_list *temp_m = elso_megallo; temp_m != NULL; temp_m = temp_m->kov) {
                        temp_m->megallo->tav = str_to_ido("25:00");
                    }
                }
                break;
            }
            case kilep:
                printf("Kilepes!\n");
                // memória felszabadítása
                // megállok
                for (Megallo_list *temp_m = elso_megallo; temp_m != NULL; temp_m = temp_m->kov) {
                    megallo_felszabadit(temp_m->megallo->atszallasok);
                    free(temp_m->megallo);
                }
                megallo_felszabadit(elso_megallo);

                // járatok
                for (Jarat_list *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
                    megallo_felszabadit(temp_j->jarat.megallok);
                }
                jarat_felszabadit(elso_jarat);

                futas = false;
                break;
            case hibas:
                printf("Nincs ilyen parancs.\n");
                break;
        }
    }

    return 0;
}
