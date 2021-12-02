#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "jarat.h"

void jarat_felszabadit(Jarat_list *elso_jarat) {
    if (elso_jarat != NULL) {
        Jarat_list *temp_m_lemarado = elso_jarat;
        Jarat_list *temp_m = elso_jarat->kov;

        for (; temp_m != NULL; temp_m = temp_m->kov) {
            free(temp_m_lemarado);
            temp_m_lemarado = temp_m;
        }
        free(temp_m_lemarado);
    }
}

Jarat *jarat_keres(Jarat_list *elso_jarat, char *nev) {
    for (Jarat_list *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
        if (strcmp(temp_j->jarat.nev, nev) == 0) {
            return &temp_j->jarat;
        }
    }
    return NULL;
}

Jarat_list *jarat_hozzaad(Jarat_list *elso_jarat, Jarat jarat) {
    if (elso_jarat == NULL) {
        elso_jarat = (Jarat_list*) malloc(sizeof(Jarat_list));
        elso_jarat->jarat = jarat;
        elso_jarat->kov = NULL;
        return elso_jarat;
    }
    Jarat_list *temp_j;
    for (temp_j = elso_jarat; temp_j->kov != NULL; temp_j = temp_j->kov) {}
    temp_j->kov = (Jarat_list*) malloc(sizeof(Jarat_list));
    temp_j->kov->jarat = jarat;
    temp_j->kov->kov = NULL;
    return elso_jarat;
}

Jarat_list *jarat_beolvas(Jarat_list *elso_jarat, FILE *fajl, Megallo_list *elso_megallo) {
    char akt_sor[2000];
    const char s[2] = ",";

    while (fscanf(fajl, "%2000[^\n]", akt_sor) != EOF) {
        getc(fajl);
        char *akt_szo;
        akt_szo = strtok(akt_sor, s);

        Jarat temp_j;
        temp_j.megallok = NULL;

        // első sor adatai
        int i;
        for (i = 0; akt_szo[i] != '\0'; ++i) {
            temp_j.nev[i] = akt_szo[i];
        }
        temp_j.nev[i] = '\0';
        akt_szo = strtok(NULL, s);
        temp_j.elso_indulas = str_to_ido(akt_szo);
        akt_szo = strtok(NULL, s);
        temp_j.utolso_indulas = str_to_ido(akt_szo);
        akt_szo = strtok(NULL, s);
        temp_j.tovabbi_indulasok = str_to_ido(akt_szo);
        akt_szo = strtok(NULL, s);

        while (akt_szo != NULL) {
            // megállók
            char megallonev[51];
            for (i = 0; akt_szo[i] != '\0'; ++i) {
                megallonev[i] = akt_szo[i];
            }
            megallonev[i] = '\0';
            akt_szo = strtok(NULL, s);
            char idostr[51];
            for (i = 0; akt_szo[i] != '\0'; ++i) {
                idostr[i] = akt_szo[i];
            }
            idostr[i] = '\0';

            Megallo *megallo = megallo_keres(elso_megallo, megallonev);
            if (megallo != NULL) {
                temp_j.megallok = megallo_hozzaad(temp_j.megallok, megallo, str_to_ido(idostr));
            } else {
                printf("Nincs %s nevu megallo", megallonev);
            }

            akt_szo = strtok(NULL, s);
        }
        elso_jarat = jarat_hozzaad(elso_jarat, temp_j);
    }
    return elso_jarat;
}

void jarat_kiir(Jarat jarat) {
    printf("nev: %s, elso indulas: %02d:%02d, utolso indulas: %02d:%02d, tovabbi indulasok: %02d:%02d\n", jarat.nev, jarat.elso_indulas.ora, jarat.elso_indulas.perc, jarat.utolso_indulas.ora, jarat.utolso_indulas.perc, jarat.tovabbi_indulasok.ora, jarat.tovabbi_indulasok.perc);

    printf("megallok/idopont:\n");
    Megallo_list *temp_m;
    for (temp_m = jarat.megallok; temp_m != NULL; temp_m = temp_m->kov) {
        printf("%s/%02d:%02d\n", temp_m->megallo->nev, temp_m->erkezes.ora, temp_m->erkezes.perc);
    }
}

void jarat_mentes(Jarat_list *elso_jarat, FILE *fajl) {
    Jarat_list *temp_j;
    for (temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
        fprintf(fajl, "%s,", temp_j->jarat.nev);
        fprintf(fajl, "%02d:%02d,", temp_j->jarat.elso_indulas.ora, temp_j->jarat.elso_indulas.perc);
        fprintf(fajl, "%02d:%02d,", temp_j->jarat.utolso_indulas.ora, temp_j->jarat.utolso_indulas.perc);
        fprintf(fajl, "%02d:%02d,", temp_j->jarat.tovabbi_indulasok.ora, temp_j->jarat.tovabbi_indulasok.perc);
        Megallo_list *temp_m;
        for (temp_m = temp_j->jarat.megallok; temp_m->kov != NULL; temp_m = temp_m->kov) {
            fprintf(fajl, "%s,%02d:%02d,", temp_m->megallo->nev, temp_m->erkezes.ora, temp_m->erkezes.perc);
        }
        fprintf(fajl, "%s,%02d:%02d\n", temp_m->megallo->nev, temp_m->erkezes.ora, temp_m->erkezes.perc);
    }
}
