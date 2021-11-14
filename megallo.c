#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "megallo.h"
#include "seged.h"


void megallo_kiir(Megallo megallo) {
    printf("nev: %s\n", megallo.nev);
    printf("atszallasok: ");
    for (int i = 0; i < megallo.meret; ++i) {
        printf("m%d: %s, ", i, megallo.atszallasok[i]);
    }
}

Megallo *megallo_keres(Megallo_tomb megallok, char *nev) {
    for (int i = 0; i < megallok.meret; ++i) {
        if (strcmp(megallok.tomb[i].nev, nev) == 0) {
            return &megallok.tomb[i];
        }
    }
    free(nev);
    return NULL;
}

void megallo_hozzaad(Megallo *elso_megallo, Megallo *m) {
    Megallo *m1;
    for (m1 = elso_megallo; m1->kov != NULL; m1 = m1->kov) {}
    m1->kov = m;
}

Megallo *mbeolvas_fg(FILE *fajl) {
    Megallo *elso_megallo = (Megallo*) malloc(sizeof(Megallo));
    elso_megallo->kov = NULL;
    int szo_vege = 0;
    Megallo *m = (Megallo*) malloc(sizeof(Megallo));
    elso_megallo->kov = m;

    while (szo_vege != EOF) {
        Megallo *temp_m = (Megallo*) malloc(sizeof(Megallo));
        // megálló neve
        temp_m->nev = kov_szo(',', fajl, &szo_vege);

        // átszállások beolvasása
        Megallo *a = (Megallo*) malloc(sizeof(Megallo));
        m->atszallasok = a;
        while (szo_vege != '\n' || szo_vege != EOF) {

        }
        m->kov = temp_m;
        m = m->kov;
    }

    return elso_megallo;

    do {
        // főmegálló beolvasása
        Megallo m;
        m.nev = kov_szo(',', fajl, &szo_vege);

        // további megállók beolvasása
        Megallo *m;

        while (szo_vege != '\n' && szo_vege != EOF) {
            m.atszallasok
            m.atszallasok[m.meret-1] = kov_szo(',', fajl, &szo_vege);
        }

        //megálló mentése a listába
        megallok.meret++;
        megallok.tomb = (Megallo*) realloc(megallok.tomb, megallok.meret * sizeof(Megallo));
        megallok.tomb[megallok.meret-1] = m;
    } while (szo_vege != EOF);
}

void megallok_hozzaad(Megallo_tomb megallok, Megallo_tomb temp_megallok) {
    megallok.tomb = (Megallo*) realloc(megallok.tomb, (temp_megallok.meret + megallok.meret) * sizeof(Megallo));
    for (int i = megallok.meret-1, j = 0; j < temp_megallok.meret; ++i, ++j) {
        megallok.tomb[i] = temp_megallok.tomb[j];
    }
    megallok.meret += temp_megallok.meret;
}

void megallo_fg(Jarat_tomb jaratok, Megallo_tomb megallok, char *nev) {
    Megallo *temp_m = megallo_keres(megallok, nev);
    if (temp_m == NULL) {
        printf("Nincs ilyen megallo.");
        return;
    }
    megallo_kiir(*temp_m);
    for (int i = 0; i < jaratok.meret; ++i) {
        bool oda = true;
        for (int j = 0; j < jaratok.tomb[i].meret; ++j) {
            if (strcmp(jaratok.tomb[i].megallok[j].nev, temp_m->nev) == 0) {
                if (oda) {
                    printf("\njarat: %s\n", jaratok.tomb[i].nev);
                    oda = false;
                }
                Ido elso_erkezes = ido_osszead(jaratok.tomb[i].elso_indulas, jaratok.tomb[i].idopontok[j]);
                printf("elso erkezes: %02d:%02d, tovabbi erkezesek: %02d:%02d\n", elso_erkezes.ora, elso_erkezes.perc, jaratok.tomb[i].tovabbi_indulasok.ora, jaratok.tomb[i].tovabbi_indulasok.perc);
            }
        }
    }
}

void mmentes_fg(Megallo_tomb megallok, FILE *fajl) {

}
