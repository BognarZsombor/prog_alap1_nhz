#ifndef MAIN_C_IDO_H
#define MAIN_C_IDO_H

typedef struct Ido {
    int ora, perc;
    struct Ido *kov;
} Ido;

/* str_to_ido
 * Egy stringet Ido formátumba alakít át. A stringnek hh:mm formátumban kell lennie.
 * @param char* str Az átírandó string
 * @return Ido A beolvasott Ido
 * */
Ido *str_to_ido(char *str);

/* ido_to_int
 * Egy Ido-t int formátumba alakit át. (60*óra + perc)
 * @param Ido i1 Az átváltandó idő
 * @return int Az átváltott érték
 * */
int ido_to_int(Ido *i1);

/* ido_osszead
 * Összead két Ido tipust. Nem kezeli ha átcsúszik másik napra.
 * @param Ido i1 Az első időpont
 * @param Ido i2 A második időpont
 * @return Ido A két időpont összege
 * */
Ido *ido_osszead(Ido *i1, Ido *i2);

/* ido_cmp
 * Megmondja két időtől, hogy melyik a nagyobb.
 * @param Ido i1 Az első időpont
 * @param Ido i2 A második időpont
 * @return int negativ, ha i1<i2 ; 0, ha i1==i2 ; positiv, ha i1>i2
 * */
int ido_cmp(Ido *i1, Ido *i2);

#endif //MAIN_C_IDO_H
