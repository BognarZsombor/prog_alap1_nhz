#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int ora, perc;
} Ido;

typedef struct {
    char *nev;
    char **megallok;
} Megallo;

typedef struct {
    char *busz;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    char **megallok;
    Ido *idopontok;
} Jarat;

typedef enum {segitseg, mbeolvas, beolvas, kiir, mentes, megallo, utvonal, kilep, hibas} parancsok;

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
char **sor_to_list(char sor[]) {
    //a sor eleji felesleges spacek kihagyása
    int k;
    for (k = 0; sor[k] == ' '; ++k) {
        k++;
    }

    int spaces = 0;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == ' ') {
            spaces++;
        }
    }
    char **temp_sor = (char**) malloc(spaces * sizeof(char*));

    spaces = 0;
    temp_sor[0] = malloc(51 * sizeof(char));
    int j = 0;
    for (int i = k; sor[i] != '\n'; ++i) {
        if (sor[i] == ' ') {
            temp_sor[spaces][j] = '\0';
            spaces++;
            j = 0;
            temp_sor[spaces] = malloc(51 * sizeof(char));
        } else {
            temp_sor[spaces][j++] = sor[i];
        }
    }
    temp_sor[spaces][j] = '\0';

    return temp_sor;
}

/* beolvas_kezdo_m
 * A program indulásánal, ha létezik alap fájl, beolvassa belőle az alap megállókat.
 * */
Megallo *beolvas_kezdo_m(char *fajl) {
    FILE *fp = fopen(fajl, "r");
    if (!fp) {
        //fájl nem létezik
        fclose(fp);
        return NULL;
    }

    int meret = 1;
    Megallo *megallok = (Megallo*) malloc(meret * sizeof(Megallo));

    int c;
    do {
        // főmegálló beolvasása
        int i = 0;
        Megallo m;
        m.nev = (char*) malloc(51 * sizeof(char));
        do {
            c = getc(fp);
            m.nev[i++] = c;
        } while (c != ' ' && c != '\n' && c != EOF);
        m.nev[i - 1] = '\0';

        // további megállók beolvasása
        i = 0;
        do {
            int j = 0;
            m.megallok[i] = (char*) malloc(51 * sizeof(char));
            do {
                c = getc(fp);
                m.megallok[i][j++] = c;
            } while (c != ',' && c != '\n' && c != EOF);
            m.megallok[i][j - 1] = '\0';
            i++;
        } while (c != '\n' && c != EOF);

        //megálló mentése a listába
        megallok = (Megallo*) realloc(megallok, meret * sizeof(Megallo));
        megallok[meret - 1] = m;
        meret++;
    } while (c != EOF);

    fclose(fp);
    return megallok;
}

int main() {
    //alap fájlok beolvasása ha léteznek
    beolvas_kezdo_m("megallok.txt");

    bool futas = true;
    char sor[100+1]; //100 karakter, hogy beleféljen fájl elérési út is ha szükséges (magában 50 karakter kb)
    while (futas) {
        printf("Parancs(max 100 karakter):");
        if (fgets(sor, 101, stdin) == NULL) {
            printf("Hiba a sor beolvasása közben.");
        }
        char **parancssor = sor_to_list(sor);
        switch (str_to_parancs(parancssor[0])) {
            case segitseg:
                printf("Parancsok: segitseg, beolvas, kiir, mentes, megallo, utvonal, kilep\n");
                break;
            case mbeolvas:
                break;
            case beolvas:
                break;
            case kiir:
                break;
            case mentes:
                break;
            case megallo:
                break;
            case utvonal:
                break;
            case kilep:
                futas = false;
                break;
            case hibas:
                printf("Nincs ilyen parancs.\n");
                break;
        }
    }

    return 0;
}
