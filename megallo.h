#ifndef MAIN_C_MEGALLO_H
#define MAIN_C_MEGALLO_H

#include "ido.h"

typedef struct Megallo {
    char nev[51];
    struct Megallo_list *atszallasok;
    Ido tav;
    char jarat_atszallas[51];
} Megallo;

typedef struct Megallo_list {
    Megallo *megallo;
    Ido erkezes;
    struct Megallo_list *kov;
} Megallo_list;

void megallo_felszabadit(Megallo_list *elso_megallo);

/* megallo_keres
 * Megkeres egy megállót a megadott tömbön, a neve alapján.
 * @param Megallo_tomb megallok A tömb, amin keresni kell.
 * @param char* nev A keresett megálló neve
 * @return Megallo A megtalált megálló pointere
 * */
Megallo *megallo_keres(Megallo_list *elso_megallo, char *nev);

/* megallo_hozzaad
 * */
Megallo_list *megallo_hozzaad(Megallo_list *elso_megallo, Megallo *megallo, Ido erkezes);

/* megallo_beolvas
 * Beolvassa a megadott fájlból a megállókat.
 * @param Megallo* elso_megallo Ha ez az alap beolvasás ez NULL, ha további beolvasás akkor a megállók első megállója
 * @param FILE* fajl A fájl, amiből beolvassa a megállókat
 * @return Megallo_tomb Megállók listájának structja
 * */
Megallo_list *megallo_beolvas(Megallo_list *elso_megallo, FILE *fajl);

/* megallo_kiir
 * */
void megallo_kiir(Megallo megallo);

/* megallo_mentes
 * */
void megallo_mentes(Megallo_list *elso_megallo, FILE *fajl);

#endif //MAIN_C_MEGALLO_H
