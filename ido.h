#ifndef MAIN_C_IDO_H
#define MAIN_C_IDO_H

typedef struct {
    int ora, perc;
} Ido;


/* str_to_ido
 * Egy stringet Ido formátumba alakít át. A stringnek hh:mm formátumban kell lennie.
 * @param char* str Az átírandó string
 * @return Ido A beolvasott Ido
 * */
Ido str_to_ido(char *str);

#endif //MAIN_C_IDO_H
