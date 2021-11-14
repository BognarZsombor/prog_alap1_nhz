#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"
#include "jarat.h"
#include "megallo.h"
#include "seged.h"

void jarat_kiir(Jarat jarat) {
    printf("nev: %s, elso indulas: %02d:%02d, utolso indulas: %02d:%02d, tovabbi indulasok: %02d:%02d\n", jarat.nev, jarat.elso_indulas.ora, jarat.elso_indulas.perc, jarat.utolso_indulas.ora, jarat.utolso_indulas.perc, jarat.tovabbi_indulasok.ora, jarat.tovabbi_indulasok.perc);

    printf("megallok: ");
    for (int i = 0; i < jarat.meret; ++i) {
        printf("m%d: %s, ", i, jarat.megallok[i].nev);
    }
    printf("\n");

    printf("idopontok: ");
    for (int i = 0; i < jarat.meret; ++i) {
        printf("i%d: %02d:%02d,", i, jarat.idopontok[i].ora, jarat.idopontok[i].perc);
    }
    printf("\n");
}

Jarat *jarat_keres(Jarat_tomb jaratok, char *nev) {
    for (int i = 0; i < jaratok.meret; ++i) {
        if (strcmp(jaratok.tomb[i].nev, nev) == 0) {
            return &jaratok.tomb[i];
        }
    }
    free(nev);
    return NULL;
}

Jarat_tomb beolvas_fg(FILE *fajl, Megallo_tomb megallok) {
    Jarat_tomb jaratok;
    jaratok.tomb = 0;
    jaratok.meret = 0;
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
            char *szo = kov_szo(',', fajl, &szo_vege);
            Megallo *temp_m = megallo_keres(megallok, szo);
            if (temp_m != NULL) {
                j.megallok[j.meret-1] = *temp_m;
            } else {
                printf("Sikertelen beolvasas. Nincs a keresett megallo elmentve (%s)!", szo);
            }
            free(szo);
        } while (szo_vege != '\n');

        // megállók indulásai
        j.idopontok = (Ido*) malloc(j.meret * sizeof(Ido));
        for (int i = 0; i < j.meret; ++i) {
            j.idopontok[i] = str_to_ido(kov_szo(' ', fajl, &szo_vege));
        }

        // járatok növelése
        jaratok.meret++;
        jaratok.tomb = (Jarat*) realloc(jaratok.tomb, jaratok.meret * sizeof(Jarat));
        jaratok.tomb[jaratok.meret-1] = j;
    } while (szo_vege != EOF);

    return jaratok;
}

void jarat_hozzaad(Jarat_tomb jaratok, Jarat_tomb temp_jaratok) {
    jaratok.tomb = (Jarat*) realloc(jaratok.tomb, (temp_jaratok.meret + jaratok.meret) * sizeof(Megallo));
    for (int i = jaratok.meret-1, j = 0; j < temp_jaratok.meret; ++i, ++j) {
        jaratok.tomb[i] = temp_jaratok.tomb[j];
    }
    jaratok.meret += temp_jaratok.meret;
}

void kiir_fg(Jarat_tomb jaratok, char *nev) {
    Jarat *temp_j = jarat_keres(jaratok, nev);
    if (temp_j == NULL) {
        printf("Nincs ilyen jarat.");
    } else {
        jarat_kiir(*temp_j);
    }
}

void mentes_fg(Jarat_tomb jaratok, FILE *fajl) {

}
