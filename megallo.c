#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "megallo.h"
#include "seged.h"

void megallo_kiir(Megallo megallo) {
    printf("nev: %s\n", megallo.nev);
    printf("atszallasok: ");
    for (int i = 0; i < megallo.meret; ++i) {
        printf("m%d: %s, ", i, megallo.nev);
    }
}

Megallo *megallo_keres(Megallo_tomb megallok, char *nev) {
    for (int i = 0; i < megallok.meret; ++i) {
        if (strcmp(megallok.tomb[i].nev, nev) == 0) {
            return &megallok.tomb[i];
        }
    }
    return NULL;
}

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

void megallok_hozzaad(Megallo_tomb megallok, Megallo_tomb temp_megallok) {
    megallok.tomb = (Megallo*) realloc(megallok.tomb, (temp_megallok.meret + megallok.meret) * sizeof(Megallo));
    for (int i = megallok.meret-1, j = 0; j < temp_megallok.meret; ++i, ++j) {
        megallok.tomb[i] = temp_megallok.tomb[j];
    }
    megallok.meret += temp_megallok.meret;
}

void megallo_fg(Megallo_tomb megallok, char *nev) {
    Megallo *temp_m = megallo_keres(megallok, nev);
    if (temp_m == NULL) {
        printf("Nincs ilyen megallo.");
    } else {
        megallo_kiir(*temp_m);
    }
}

void mmentes_fg(Megallo_tomb megallok, FILE *fajl) {

}
