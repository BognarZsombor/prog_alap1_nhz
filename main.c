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
    char *nev;
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

/* kov_szo
 * Beolvassa a megadott fájlból a választóig tartó stringet.
 * @param char valaszto Ez a feltétele a string végének
 * @param FILE* fajl A fájl, amiből beolvassa a stringet
 * @param char* szo_vege Azt jelzi, hogy mivel végződött a string (valaszto, \n, EOF)
 * @return char* A beolvasott string
 * */
char *kov_szo(char valaszto, FILE *fajl, int *szo_vege) {
    int meret = 0;
    char *szo = (char*) malloc(meret * sizeof(char));

    char c;
    do {
        meret++;
        szo = (char*) realloc(szo, meret * sizeof(char));
        c = getc(fajl);
        szo[meret-1] = c;
    } while (c != valaszto && c != '\n' && c != EOF);

    if (szo_vege != NULL) {
        szo_vege = c;
        szo[meret-1] = '\0';
    }
    return szo;
}

Ido str_to_ido(char *str) {
    Ido ido;
    sscanf(str, "%d:%d", &ido.ora, &ido.perc);
    return ido;
}

/* beolvas_m_fg
 * Beolvassa a megadott fájlból a megállókat.
 * @param FILE* fajl A fájl, amiből beolvassa a megállókat
 * @return Megallo* Megállók listája
 * */
Megallo *beolvas_m_fg(FILE *fajl) {
    int m_meret = 0;
    Megallo *megallok = (Megallo*) malloc(m_meret * sizeof(Megallo));
    int szo_vege;

    do {
        // főmegálló beolvasása
        Megallo m;
        m.nev = kov_szo(',', fajl, &szo_vege);

        // további megállók beolvasása
        int meret = 1;
        m.megallok = (char**) malloc(meret * sizeof(char*));

        do {
            m.megallok[meret-1] = kov_szo(',', fajl, &szo_vege);
            meret++;
            m.megallok = (char**) realloc(m.megallok, meret * sizeof(char*));
        } while (szo_vege != '\n' && szo_vege != EOF);

        //megálló mentése a listába
        m_meret++;
        megallok = (Megallo*) realloc(megallok, m_meret * sizeof(Megallo));
        megallok[m_meret-1] = m;
    } while (szo_vege != EOF);

    fclose(fajl);
    return megallok;
}

/* beolvas_fg
 * Beolvassa a megadott fájlból a járatokat.
 * @param FILE* fajl A fájl, amiből beolvassa a járatokat
 * @return Jarat* Járatok listája
 * */
Jarat *beolvas_fg(FILE *fajl) {
    int meret = 1;
    Jarat *jaratok = (Jarat*) malloc(meret * sizeof(Jarat));
    int szo_vege;

    do {
        Jarat j;
        j.nev = kov_szo(' ', fajl, &szo_vege);
        j.elso_indulas = str_to_ido(kov_szo(' ', fajl, &szo_vege));
        j.utolso_indulas = kov_szo(' ', fajl, &szo_vege);
    } while (szo_vege != EOF);
}

int main() {
    // megállók és járatok listája
    Megallo *megallok;
    Jarat *jaratok;

    //alap fájlok beolvasása ha léteznek
    FILE *fajl = fopen("megallok.txt", "r");
    if (fajl) {
        megallok = beolvas_m_fg(fajl);
    }
    fajl = fopen("jaratok.txt", "r");
    if (fajl) {
        jaratok = beolvas_fg(fajl);
    }

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
