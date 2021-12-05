#ifndef PROG_ALAP1_NHZ_UTVONAL_H
#define PROG_ALAP1_NHZ_UTVONAL_H

#include "megallo.h"
#include "jarat.h"

/* megallo_cmp
 * Összehasonlít két megállót a tav-juk szerint.
 * @param const void* m1 Az első megálló void pointerként
 * @param const void* m2 A második megálló void pointerként
 * @return int negativ, ha m1<m2 ; 0, ha m1==m2 ; positiv, ha m1>m2
 * */
int megallo_cmp(const void *m1, const void *m2);

/* utvonal_keres
 * Rekurziv függvény, amely elmegy a céltől a start megállóig, és ha megtalálta az utat kiírja az odavezető lépéseket.
 * Azért megy visszafelé, mert a rekurzióban csak akkor tudjuk kiírni, ha az aktuális útvonal jó volt.
 * A megálló paraméterek, azért nem pointerek, mert nem kell változtatni az értékeiket.
 * @param Megallo start Ahonnan indulni akarunk
 * @param Megallo cel Ahova érkezni akarunk
 * @param Jarat_list* elso_jarat A járatok listája
 * @return int Megtalálta-e már a program a leggyorsabb útvonalat, ki kell-e írni az útvonalat
 * */
int utvonal_keres(Megallo start, Megallo cel, Jarat_list *elso_jarat);

#endif //PROG_ALAP1_NHZ_UTVONAL_H
