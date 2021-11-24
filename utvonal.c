#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utvonal.h"

int megallo_cmp(const void *m1, const void *m2) {
    Megallo *a = (Megallo*) m1;
    Megallo *b = (Megallo*) m2;
    return ido_cmp(a->tav, b->tav);
}

int utvonal_keres(Megallo start, Megallo cel, Jarat_list *elso_jarat) {
    if (strcmp(cel.nev, start.nev) == 0) {
        return 0;
    } else {
        // innen elérhető megállók távjainak beállítása
        // átszállások
        for (Megallo_list *temp_m = cel.atszallasok; temp_m != NULL; temp_m = temp_m->kov) {
            if (ido_cmp(temp_m->megallo->tav, cel.tav) == 1) {
                temp_m->megallo->tav = cel.tav;
            }
        }
        // járatok
        // lista felvétele a megállók elmentésére
        Megallo akt_megallok[100];
        int akt_megallok_meret = 0;
        for (Jarat_list *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
            for (Megallo_list *temp_m = temp_j->jarat.megallok; temp_m->kov != NULL; temp_m = temp_m->kov) {
                if (strcmp(temp_m->megallo->nev, cel.nev) == 0) {
                    Ido akt_indulas = int_to_ido((int) ceil((double)(ido_to_int(cel.tav) - ido_to_int(temp_j->jarat.elso_indulas) - ido_to_int(temp_m->kov->erkezes)) /
                                 (double) ido_to_int(temp_j->jarat.tovabbi_indulasok)));
                    if (ido_cmp(temp_m->kov->megallo->tav, akt_indulas) == 1) {
                        temp_m->kov->megallo->tav = akt_indulas;
                    }
                    akt_megallok[akt_megallok_meret++] = *temp_m->kov->megallo;
                }
            }
        }

        // fv újrahívása az innen elérhető megállókra táv szerint növekvő sorrendben
        // átszállások
        Ido pre_min = str_to_ido("-1:-1");
        for (Megallo_list *temp_m = start.atszallasok; temp_m != NULL; temp_m = temp_m->kov) {
            Megallo mini = *start.atszallasok->megallo;
            while (ido_cmp(pre_min, mini.tav) == 1) {
                mini = *temp_m->kov->megallo;
                temp_m = temp_m->kov;
            }
            // minkeresés
            for (Megallo_list *temp_a = start.atszallasok; temp_a != NULL; temp_a = temp_a->kov) {
                if (ido_cmp(mini.tav, temp_a->megallo->tav) == 1 && ido_cmp(mini.tav, pre_min) == 1) {
                    mini.tav = temp_a->megallo->tav;
                }
            }
            pre_min = mini.tav;
            // fv újrahívása
            if (utvonal_keres(start, mini, elso_jarat) == 1) {
                printf("Átszállás %s megállóból %s megállóba / %02d:%02d-kor.\n", mini.nev, cel.nev, cel.tav.ora, cel.tav.perc);
                return 1;
            }
        }
        
        // járatok
        // lista rendezése tav alapján
        qsort(akt_megallok, akt_megallok_meret, sizeof(Megallo), megallo_cmp);

        // fv újrahívása
        for (int i = 0; i < akt_megallok_meret; ++i) {
            if (utvonal_keres(start, akt_megallok[i], elso_jarat) == 1) {
                printf("Átszállás %s járatról %s járatra / %02d:%02d-kor.\n", akt_megallok[i].nev, cel.nev, akt_megallok[i].tav.ora, akt_megallok[i].tav.perc);
                return 1;
            }
        }

        // dead end / innen nem lehet továbbmenni
        return 0;
    }
}
