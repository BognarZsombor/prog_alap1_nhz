#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "megallo.h"
#include "seged.h"

Megallo *megallo_keres(Megallo *elso_megallo, char *nev) {
    for (Megallo *temp_m = elso_megallo->kov; temp_m != NULL; temp_m = temp_m->kov) {
        if (strcmp(temp_m->nev, nev) == 0) {
            return temp_m;
        }
    }
    return NULL;
}

Megallo *mbeolvas_fg(Megallo *elso_megallo, FILE *fajl) {
    Megallo *m;
    for (m = elso_megallo; m != NULL; m = m->kov) {}
    int szo_vege = 0;

    while (szo_vege != EOF) {
        Megallo *temp_m = (Megallo*) malloc(sizeof(Megallo));
        // megálló neve
        temp_m->nev = kov_szo(',', fajl, &szo_vege);

        // átszállások beolvasása
        temp_m->atszallasok = NULL;
        Megallo *a = temp_m->atszallasok;
        while (szo_vege != '\n' && szo_vege != EOF) {
            Megallo *temp_a = (Megallo*) malloc(sizeof(Megallo));
            temp_a->nev = kov_szo(',', fajl, &szo_vege);
            temp_a->kov = NULL;
            a = temp_a;
            a = a->kov;
        }

        temp_m->kov = NULL;
        m = temp_m;
        m = m->kov;
    }

    return elso_megallo;
}

void megallo_fg(Megallo *megallo) {
    // megallo kiirasa
    printf("nev: %s\n", megallo->nev);
    printf("atszallasok: ");
    Megallo *temp_a;
    for (temp_a = megallo->atszallasok; temp_a != NULL; temp_a = temp_a->kov) {
        printf("%s, ", temp_a->nev);
    }

    // jaratokbeli erkezesek kiirasa
    /*for (Jarat *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
        bool oda = true;
        Megallo *temp_m = temp_j->megallok;
        Ido *temp_i = temp_j->idopontok;
        for (; temp_m != NULL; temp_m = temp_m->kov, temp_i = temp_i->kov) {
            if (strcmp(temp_m->nev, megallo->nev) == 0) {
                if (oda) {
                    printf("\njarat: %s\n", temp_m->nev);
                    oda = false;
                }
                Ido *elso_erkezes = ido_osszead(temp_j->elso_indulas, temp_i);
                printf("elso erkezes: %02d:%02d, tovabbi erkezesek: %02d:%02d\n", elso_erkezes->ora, elso_erkezes->perc, temp_j->tovabbi_indulasok->ora, temp_j->tovabbi_indulasok->perc);
            }
        }
    }*/
}

void mmentes_fg(Megallo *elso_megallo, FILE *fajl) {

}
