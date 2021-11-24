#ifndef PROG_ALAP1_NHZ_UTVONAL_H
#define PROG_ALAP1_NHZ_UTVONAL_H

#include "megallo.h"
#include "jarat.h"

/* utvonal_keres
 * Rekurziv függvény, amely elmegy a céltől a start megállóig, és ha megtalálta az utat kiírja az odavezető lépéseket.
 * Azért megy visszafelé, mert a rekurzióban csak akkor tudjuk kiírni, ha az aktuális útvonal jó volt.
 * @param Megallo start Ahonnan indulni akarunk
 * @param Megallo cel Ahova érkezni akarunk
 * @param Jarat_list* elso_jarat A járatok listája
 * @return int Megtalálta-e már a program a leggyorsabb útvonalat, ki kell-e írni az útvonalat
 * */
int utvonal_keres(Megallo start, Megallo cel, Jarat_list *elso_jarat);

#endif //PROG_ALAP1_NHZ_UTVONAL_H
