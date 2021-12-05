#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "megallo.h"

void megallo_felszabadit(Megallo_list *elso_megallo) {
    if (elso_megallo != NULL) {
        Megallo_list *temp_m_lemarado = elso_megallo;
        Megallo_list *temp_m = elso_megallo->kov;

        for (; temp_m != NULL; temp_m = temp_m->kov) {
            free(temp_m_lemarado);
            temp_m_lemarado = temp_m;
        }
        free(temp_m_lemarado);
    }
}

Megallo *megallo_keres(Megallo_list *elso_megallo, char *nev) {
    for (Megallo_list *temp_m = elso_megallo; temp_m != NULL; temp_m = temp_m->kov) {
        if (strcmp(temp_m->megallo->nev, nev) == 0) {
            return temp_m->megallo;
        }
    }
    return NULL;
}

Megallo_list *megallo_hozzaad(Megallo_list *elso_megallo, Megallo *megallo, Ido erkezes) {
    if (elso_megallo == NULL) {
        elso_megallo = (Megallo_list*) malloc(sizeof(Megallo_list));
        elso_megallo->megallo = megallo;
        elso_megallo->erkezes = erkezes;
        elso_megallo->kov = NULL;
        return elso_megallo;
    }
    Megallo_list *temp_m;
    for (temp_m = elso_megallo; temp_m->kov != NULL; temp_m = temp_m->kov) {}
    temp_m->kov = (Megallo_list*) malloc(sizeof(Megallo_list));
    temp_m->kov->megallo = megallo;
    temp_m->kov->erkezes = erkezes;
    temp_m->kov->kov = NULL;
    return elso_megallo;
}

Megallo_list *megallo_beolvas(Megallo_list *elso_megallo, FILE *fajl) {
    char akt_sor[2000];
    fscanf(fajl, "%2000[^\n]", akt_sor);
    getc(fajl);
    const char s[2] = ",";
    char *akt_szo;
    akt_szo = strtok(akt_sor, s);

    // alap megállók beolvasása
    while (akt_szo != NULL) {
        Megallo *temp_m = (Megallo*) malloc(sizeof(Megallo));
        int i;
        for (i = 0; akt_szo[i] != '\0'; ++i) {
            temp_m->nev[i] = akt_szo[i];
        }
        temp_m->nev[i] = '\0';
        temp_m->atszallasok = NULL;
        temp_m->tav = str_to_ido("25:00");
        elso_megallo = megallo_hozzaad(elso_megallo, temp_m, str_to_ido("00:00"));
        akt_szo = strtok(NULL, s);
    }

    // átszállások beolvasása
    while (fscanf(fajl, "%2000[^\n]", akt_sor) != EOF) {
        getc(fajl);
        akt_szo = strtok(akt_sor, s);
        Megallo *temp_m = megallo_keres(elso_megallo, akt_szo);
        akt_szo = strtok(NULL, s);

        while (akt_szo != NULL) {
            Megallo *temp_atszallas = megallo_keres(elso_megallo, akt_szo);
            if (temp_atszallas != NULL) {
                temp_m->atszallasok = megallo_hozzaad(temp_m->atszallasok, temp_atszallas, str_to_ido("00:00"));
            } else {
                printf("Nincs %s nevu megallo!", akt_szo);
            }
            akt_szo = strtok(NULL, s);
        }
    }
    return elso_megallo;
}

void megallo_kiir(Megallo megallo) {
    // megallo kiirasa
    printf("nev: %s\n", megallo.nev);
    printf("atszallasok: ");
    Megallo_list *temp_a;
    if (megallo.atszallasok != NULL) {
        for (temp_a = megallo.atszallasok; temp_a->kov != NULL; temp_a = temp_a->kov) {
            printf("%s, ", temp_a->megallo->nev);
        }
        printf("%s\n", temp_a->megallo->nev);
    } else {
        printf("\n");
    }
}

void megallo_mentes(Megallo_list *elso_megallo, FILE *fajl) {
    Megallo_list *temp_m;
    for (temp_m = elso_megallo; temp_m->kov != NULL; temp_m = temp_m->kov) {
        fprintf(fajl, "%s,", temp_m->megallo->nev);
    }
    fprintf(fajl, "%s\n", temp_m->megallo->nev);
    
    for (temp_m = elso_megallo; temp_m != NULL; temp_m = temp_m->kov) {
        Megallo_list *temp_a;
        fprintf(fajl, "%s,", temp_m->megallo->nev);
        if (temp_m->megallo->atszallasok != NULL) {
            for (temp_a = temp_m->megallo->atszallasok; temp_a != NULL; temp_a = temp_a->kov) {
                fprintf(fajl, "%s,", temp_a->megallo->nev);
            }
            fprintf(fajl, "%s\n", temp_a->megallo->nev);
        }
    }
}
