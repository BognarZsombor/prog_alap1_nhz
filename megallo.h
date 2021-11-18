#ifndef MAIN_C_MEGALLO_H
#define MAIN_C_MEGALLO_H

#include "ido.h"
struct Jarat;

typedef struct Megallo {
    char *nev;
    struct *Jarat;
    char **atszallasok;
    int meret;
    struct Megallo *kov;
} Megallo;

/* megallo_keres
 * Megkeres egy megállót a megadott tömbön, a neve alapján.
 * @param Megallo_tomb megallok A tömb, amin keresni kell.
 * @param char* nev A keresett megálló neve
 * @return Megallo A megtalált megálló pointere
 * */
Megallo *megallo_keres(Megallo *elso_megallo, char *nev);

/* mbeolvas_fg
 * Beolvassa a megadott fájlból a megállókat.
 * @param Megallo* elso_megallo Ha ez az alap beolvasás ez NULL, ha további beolvasás akkor a megállók első megállója
 * @param FILE* fajl A fájl, amiből beolvassa a megállókat
 * @return Megallo_tomb Megállók listájának structja
 * */
Megallo* mbeolvas_fg(Megallo *elso_megallo, FILE *fajl);

/* megallo_fg
 * */
void megallo_fg(Megallo *megallo);

/* mmentes_fg
 * */
void mmentes_fg(Megallo *elso_megallo, FILE *fajl);

#endif //MAIN_C_MEGALLO_H
