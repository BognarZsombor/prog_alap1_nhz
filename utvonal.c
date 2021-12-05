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
    if (strcmp(start.nev, cel.nev) == 0) {
        return 1;
    } else {
        // innen elérhető megállók távjainak beállítása
        // átszállások
        Megallo akt_atszallasok[100];
        int akt_atszallasok_meret = 0;
        for (Megallo_list *temp_m = start.atszallasok; temp_m != NULL; temp_m = temp_m->kov) {
            if (ido_cmp(temp_m->megallo->tav, start.tav) == 1) {
                temp_m->megallo->tav = start.tav;
                akt_atszallasok[akt_atszallasok_meret++] = *temp_m->megallo;
            }
        }
        // járatok
        // lista felvétele a megállók elmentésére
        Megallo akt_megallok[100];
        int akt_megallok_meret = 0;
        for (Jarat_list *temp_j = elso_jarat; temp_j != NULL; temp_j = temp_j->kov) {
            // hogyha az aktuális járatban benne van a start megálló
            if (megallo_keres(temp_j->jarat.megallok, start.nev) != NULL) {
                // végigmegyünk a járat megállóin és ha ez egy rovidebb út, innen is újrahívjuk majd a fv-t
                // először elemgyünk az adott megállóig és az innen következő megállókat nézzük
                // azért kell végigmennünk mégegyszer, mert a listában kell idáig eljutnunk és a megallo_keres nem Megallo_list,
                // nem Megallo-t ad vissza, így nem tudjuk melyik megálló következik utána
                Megallo_list *temp_m = temp_j->jarat.megallok;
                for (; strcmp(temp_m->megallo->nev, start.nev) != 0; temp_m = temp_m->kov) {}
                if (temp_m->kov != NULL) {
                    // aktuális indulás kiszámolása
                    int kulonbseg = ido_to_int(
                            ido_kivon(start.tav, ido_osszead(temp_j->jarat.elso_indulas, temp_m->kov->erkezes)));
                    int indulas_count = (int) ceil(
                            (double) (kulonbseg) / (double) ido_to_int(temp_j->jarat.tovabbi_indulasok));
                    Ido akt_indulas = ido_osszead(temp_j->jarat.elso_indulas, temp_m->kov->erkezes);
                    Ido temp_i = int_to_ido(ido_to_int(temp_j->jarat.tovabbi_indulasok) * indulas_count);
                    akt_indulas = ido_osszead(akt_indulas, temp_i);
                    akt_indulas = ido_kivon(akt_indulas, temp_m->erkezes);

                    for (; temp_m->kov != NULL; temp_m = temp_m->kov) {
                        if (ido_cmp(temp_m->kov->megallo->tav, ido_osszead(akt_indulas, temp_m->kov->erkezes)) == 1 &&
                                ido_cmp(temp_j->jarat.utolso_indulas, akt_indulas) == 1 && ido_cmp(akt_indulas, temp_j->jarat.elso_indulas) == 1) {
                            temp_m->kov->megallo->tav = ido_osszead(akt_indulas, temp_m->kov->erkezes);
                            akt_megallok[akt_megallok_meret] = *temp_m->kov->megallo;
                            int i;
                            for (i = 0; temp_j->jarat.nev[i] != '\0'; ++i) {
                                akt_megallok[akt_megallok_meret].jarat_atszallas[i] = temp_j->jarat.nev[i];
                            }
                            akt_megallok[akt_megallok_meret++].jarat_atszallas[i] = '\0';
                        }
                    }
                }
            }
        }

        // fv újrahívása az innen elérhető megállókra táv szerint növekvő sorrendben
        // átszállások
        // lista rendezése táv alapján
        qsort(akt_atszallasok, akt_atszallasok_meret, sizeof(Megallo), megallo_cmp);

        // fv újrahívása
        for (int i = 0; i < akt_atszallasok_meret; ++i) {
            if (utvonal_keres(akt_atszallasok[i], cel, elso_jarat) == 1) {
                printf("Atszallas %s megallobol %s megalloba / %02d:%02d-kor.\n", start.nev, akt_atszallasok[i].nev, akt_atszallasok[i].tav.ora, akt_atszallasok[i].tav.perc);
                return 1;
            }
        }

        // járatok
        // lista rendezése tav alapján
        qsort(akt_megallok, akt_megallok_meret, sizeof(Megallo), megallo_cmp);

        // fv újrahívása
        for (int i = 0; i < akt_megallok_meret; ++i) {
            if (utvonal_keres(akt_megallok[i], cel, elso_jarat) == 1) {
                printf("Felszallas %s megalloban %s jaratra es utazas %s megalloig / erkezes: %02d:%02d-kor.\n", start.nev, akt_megallok[i].jarat_atszallas, akt_megallok[i].nev, akt_megallok[i].tav.ora, akt_megallok[i].tav.perc);
                return 1;
            }
        }

        // dead end / innen nem lehet továbbmenni
        return 0;
    }
}
