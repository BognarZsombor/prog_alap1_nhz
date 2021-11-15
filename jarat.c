#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "ido.h"
#include "jarat.h"
#include "seged.h"

Jarat *jarat_keres(Jarat *elso_jarat, char *nev) {
    for (Jarat *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
        if (strcmp(temp_j->nev, nev) == 0) {
            free(nev);
            return temp_j;
        }
    }
    free(nev);
    return NULL;
}

Jarat *beolvas_fg(Jarat *elso_jarat, FILE *fajl, Megallo *elso_megallo) {
    Jarat *j;
    if (elso_jarat == NULL) {
        // ha nincs még első elem felveszünk egy újat
        elso_jarat = (Jarat*) malloc(sizeof(Jarat));
        elso_jarat->kov = NULL;
        j = elso_jarat;
    } else {
        // ha volt már első elem, elmegyünk a list végére
        for (j = elso_jarat; j->kov != NULL; j = j->kov) {}
    }
    int szo_vege = 0;

    while (szo_vege != EOF) {
        szo_vege = 0;
        // első sor adatai
        Jarat *temp_j = (Jarat*) malloc(sizeof(Jarat));
        temp_j->nev = kov_szo(' ', fajl, NULL);
        temp_j->elso_indulas = str_to_ido(kov_szo(' ', fajl, NULL));
        temp_j->utolso_indulas = str_to_ido(kov_szo(' ', fajl, NULL));
        temp_j->tovabbi_indulasok = str_to_ido(kov_szo(' ', fajl, NULL));

        // megállók
        temp_j->megallok = (Megallo*) malloc(sizeof(Megallo));
        temp_j->megallok->kov = NULL;
        Megallo *m = temp_j->megallok;

        while (szo_vege != '\n' && szo_vege != EOF) {
            Megallo *temp_m = (Megallo*) malloc(sizeof(Megallo));
            temp_m->nev = kov_szo(',', fajl, &szo_vege);
            temp_m->kov = NULL;
            m->kov = temp_m;
            m = m->kov;
        }

        // időpontok
        temp_j->idopontok = (Ido*) malloc(sizeof(Ido));
        temp_j->idopontok->kov = NULL;
        Ido *i = temp_j->idopontok;
        szo_vege = 0;

        while (szo_vege != '\n' && szo_vege != EOF) {
            Ido *temp_i = str_to_ido(kov_szo(' ', fajl, &szo_vege));
            temp_i->kov = NULL;
            i->kov = temp_i;
            i = i->kov;
        }

        temp_j->kov = NULL;
        j->kov = temp_j;
        j = j->kov;
    }

    return elso_jarat;
}

void kiir_fg(Jarat *jarat) {
    printf("nev: %s, elso indulas: %02d:%02d, utolso indulas: %02d:%02d, tovabbi indulasok: %02d:%02d\n", jarat->nev, jarat->elso_indulas->ora, jarat->elso_indulas->perc, jarat->utolso_indulas->ora, jarat->utolso_indulas->perc, jarat->tovabbi_indulasok->ora, jarat->tovabbi_indulasok->perc);

    printf("megallok/idopontok: ");
    Megallo *temp_m = jarat->megallok;
    Ido *temp_i = jarat->idopontok;
    for (; temp_m != NULL; temp_m = temp_m->kov, temp_i = temp_i->kov) {
        printf("%s/%02d:%02d, ", temp_m->nev, temp_i->ora, temp_i->perc);
    }
    printf("\n");
}

void mentes_fg(Jarat *elso_jarat, FILE *fajl) {

}
