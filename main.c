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
    int meret;
} Megallo;

typedef struct {
    char *nev;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    Megallo *megallok;
    Ido *idopontok;
    int meret;
} Jarat;

typedef struct {
    Megallo *tomb;
    int meret;
} Megallo_tomb;

typedef struct {
    Jarat *tomb;
    int meret;
} Jarat_tomb;

typedef enum {segitseg, mbeolvas, beolvas, mentes, mmentes, kiir, megallo, utvonal, kilep, hibas} parancsok;

/* jarat_kiir
 * Kiirja a megadott járat adatait.
 * @param Jarat jarat A kiirandó járat
 * */
void jarat_kiir(Jarat jarat) {
    printf("név: %s, első indulás: %d:%d, utolsó indulás: %d:%d, további indulások: %d:%d\n", jarat.nev, jarat.elso_indulas.ora, jarat.elso_indulas.perc, jarat.utolso_indulas.ora, jarat.utolso_indulas.perc, jarat.tovabbi_indulasok.ora, jarat.tovabbi_indulasok.perc);

    printf("megállók: ");
    for (int i = 0; i < jarat.meret; ++i) {
        printf("m%d: %s,", i, jarat.megallok[i].nev);
    }
    printf("\n");

    printf("időpontok: ");
    for (int i = 0; i < jarat.meret; ++i) {
        printf("i%d: %d:%d,", i, jarat.idopontok[i].ora, jarat.idopontok[i].perc);
    }
    printf("\n");
}

/* megallo_kiir
 * Kiirja a megadott járat adatait.
 * @param Megallo megallo A kiirandó megálló
 * */
void megallo_kiir(Megallo megallo) {
    printf("név: %s\n", megallo.nev);
    printf("átszállások: ");
    for (int i = 0; i < megallo.meret; ++i) {
        printf("m%d: %s,", i, megallo.nev);
    }
}

/* jarat_keres
 * Megkeres egy járatot a megadott tömbön, a neve alapján.
 * @param Jarat_tomb jaratok A tömb, amin keresni kell.
 * @param char* nev A keresett járat neve
 * @return Jarat A megtalált járat
 * */
Jarat jarat_keres(Jarat_tomb jaratok, char *nev) {
    for (int i = 0; i < jaratok.meret; ++i) {
        if (strcmp(jaratok.tomb[i].nev, nev) == 0) {
            return jaratok.tomb[i];
        }
    }
}

/* megallo_keres
 * Megkeres egy megállót a megadott tömbön, a neve alapján.
 * @param Megallo_tomb megallok A tömb, amin keresni kell.
 * @param char* nev A keresett megálló neve
 * @return Megallo A megtalált megálló
 * */
Megallo megallo_keres(Megallo_tomb megallok, char *nev) {
    for (int i = 0; i < megallok.meret; ++i) {
        if (strcmp(megallok.tomb[i].nev, nev) == 0) {
            return megallok.tomb[i];
        }
    }
}

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
        *szo_vege = c;
        szo[meret-1] = '\0';
    }
    return szo;
}

/* str_to_ido
 * Egy stringet Ido formátumba alakít át. A stringnek hh:mm formátumban kell lennie.
 * @param char* str Az átírandó string
 * @return Ido A beolvasott Ido
 * */
Ido str_to_ido(char *str) {
    Ido ido;
    sscanf(str, "%d:%d", &ido.ora, &ido.perc);
    return ido;
}

/* mbeolvas_fg
 * Beolvassa a megadott fájlból a megállókat.
 * @param FILE* fajl A fájl, amiből beolvassa a megállókat
 * @return Megallo_tomb Megállók listájának structja
 * */
Megallo_tomb mbeolvas_fg(FILE *fajl) {
    Megallo_tomb megallok;
    megallok.meret = 0;
    megallok.tomb = (Megallo*) malloc(megallok.meret * sizeof(Megallo));
    int szo_vege;

    do {
        // főmegálló beolvasása
        Megallo m;
        m.nev = kov_szo(',', fajl, &szo_vege);
        m.meret = 0;

        // további megállók beolvasása
        m.megallok = (char**) malloc(m.meret * sizeof(char*));

        do {
            m.meret++;
            m.megallok = (char**) realloc(m.megallok, m.meret * sizeof(char*));
            m.megallok[m.meret-1] = kov_szo(',', fajl, &szo_vege);
        } while (szo_vege != '\n' && szo_vege != EOF);

        //megálló mentése a listába
        megallok.meret++;
        megallok.tomb = (Megallo*) realloc(megallok.tomb, megallok.meret * sizeof(Megallo));
        megallok.tomb[megallok.meret-1] = m;
    } while (szo_vege != EOF);

    fclose(fajl);
    return megallok;
}

/* beolvas_fg
 * Beolvassa a megadott fájlból a járatokat.
 * @param FILE* fajl A fájl, amiből beolvassa a járatokat
 * @return Jarat_tomb Járatok listájának structja
 * */
Jarat_tomb beolvas_fg(FILE *fajl, Megallo_tomb megallok) {
    Jarat_tomb jaratok;
    jaratok.tomb = 0;
    jaratok.tomb = (Jarat*) malloc(jaratok.meret * sizeof(Jarat));
    int szo_vege;

    do {
        // első sor adatai
        Jarat j;
        j.nev = kov_szo(' ', fajl, &szo_vege);
        j.elso_indulas = str_to_ido(kov_szo(' ', fajl, NULL));
        j.utolso_indulas = str_to_ido(kov_szo(' ', fajl, NULL));
        j.tovabbi_indulasok = str_to_ido(kov_szo(' ', fajl, NULL));
        j.meret = 0;

        // megállók adatai
        j.megallok = (Megallo*) malloc(j.meret * sizeof(Megallo));
        do {
            j.meret++;
            j.megallok = (Megallo*) realloc(j.megallok, j.meret * sizeof(Megallo));
            j.megallok[j.meret-1] = megallo_keres(megallok, kov_szo(',', fajl, &szo_vege));
        } while (szo_vege != '\n');

        // megállók indulásai
        j.idopontok = (Ido*) malloc(j.meret * sizeof(Ido));
        for (int i = 0; i < j.meret; ++i) {
            j.idopontok[i] = str_to_ido(kov_szo(' ', fajl, NULL));
        }

        // járatok növelése
        jaratok.meret++;
        jaratok.tomb = (Jarat*) realloc(jaratok.tomb, jaratok.meret * sizeof(Jarat));
        jaratok.tomb[jaratok.meret-1] = j;
    } while (szo_vege != EOF);

    return jaratok;
}

/* megallok_hozzaad
 * Hozzáad egy megállótömbhöz egy másik megállótömböt
 * @param Megallo_tomb megallok Amihez hozzáadjuk az új megállókat
 * @param Megallo_tomb temp_megallok Amit hozzáadunk az eredeti megállókhozs
 * */
void megallok_hozzaad(Megallo_tomb megallok, Megallo_tomb temp_megallok) {
    megallok.tomb = (Megallo*) realloc(megallok.tomb, (temp_megallok.meret + megallok.meret) * sizeof(Megallo));
    for (int i = megallok.meret-1, j = 0; j < temp_megallok.meret; ++i, ++j) {
        megallok.tomb[i] = temp_megallok.tomb[j];
    }
    megallok.meret += temp_megallok.meret;
}

/* jarat_hozzaad
 * Hozzáad egy járattömbhöz egy másik járattömböt
 * @param Jarat_tomb jaratok Amihez hozzáadjuk az új járatokat
 * @param Jarat_tomb temp_jaratok Amit hozzáadunk az eredeti járatokhoz
 * */
void jarat_hozzaad(Jarat_tomb jaratok, Jarat_tomb temp_jaratok) {
    jaratok.tomb = (Megallo*) realloc(jaratok.tomb, (temp_jaratok.meret + jaratok.meret) * sizeof(Megallo));
    for (int i = jaratok.meret-1, j = 0; j < temp_jaratok.meret; ++i, ++j) {
        jaratok.tomb[i] = temp_jaratok.tomb[j];
    }
    jaratok.meret += temp_jaratok.meret;
}

/* kiir_fg
 * */
void kiir_fg(Jarat_tomb jaratok, char *nev) {
    for (int i = 0; i < jaratok.meret; ++i) {
        if (strcmp(jaratok.tomb[i].nev, nev) == 0) {
            jarat_kiir(jaratok.tomb[i]);
        }
    }
}

/* megallo_fg
 * */
void megallo_fg(Megallo_tomb megallok, char *nev) {
    for (int i = 0; i < megallok.meret; ++i) {
        if (strcmp(megallok.tomb[i].nev, nev) == 0) {
            megallo_kiir(megallok.tomb[i]);
        }
    }
}

void mentes_fg(Jarat_tomb jaratok, FILE *fajl) {

}

void mmentes_fg(Megallo_tomb megallok, FILE *fajl) {

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
        printf("Parancs(max 100 karakter):");
        if (fgets(sor, 101, stdin) == NULL) {
            printf("Hiba a sor beolvasása közben.");
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
                }
                fclose(fajl);
                break;
            case beolvas:
                fajl = fopen(parancssor[1], "r");
                Jarat_tomb temp_jaratok;
                if (fajl) {
                    temp_jaratok = beolvas_fg(fajl, megallok);
                    jarat_hozzaad(jaratok, temp_jaratok);
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
                megallo_fg(megallok, parancssor[1]);
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
