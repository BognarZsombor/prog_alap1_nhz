#ifndef MAIN_C_MEGALLO_H
#define MAIN_C_MEGALLO_H

#include "ido.h"

typedef struct {
    char *nev;
    char **atszallasok;
    int meret;
} Megallo;

typedef struct {
    Megallo *tomb;
    int meret;
} Megallo_tomb;

/* megallo_kiir
 * Kiirja a megadott járat adatait.
 * @param Megallo megallo A kiirandó megálló
 * */
void megallo_kiir(Megallo megallo);

/* megallo_keres
 * Megkeres egy megállót a megadott tömbön, a neve alapján.
 * @param Megallo_tomb megallok A tömb, amin keresni kell.
 * @param char* nev A keresett megálló neve
 * @return Megallo A megtalált megálló pointere
 * */
Megallo *megallo_keres(Megallo_tomb megallok, char *nev);

/* mbeolvas_fg
 * Beolvassa a megadott fájlból a megállókat.
 * @param FILE* fajl A fájl, amiből beolvassa a megállókat
 * @return Megallo_tomb Megállók listájának structja
 * */
Megallo_tomb mbeolvas_fg(FILE *fajl);

/* megallok_hozzaad
 * Hozzáad egy megállótömbhöz egy másik megállótömböt
 * @param Megallo_tomb megallok Amihez hozzáadjuk az új megállókat
 * @param Megallo_tomb temp_megallok Amit hozzáadunk az eredeti megállókhozs
 * */
void megallok_hozzaad(Megallo_tomb megallok, Megallo_tomb temp_megallok);

/* megallo_fg
 * */
void megallo_fg(Megallo_tomb megallok, char *nev);

/* mmentes_fg
 * */
void mmentes_fg(Megallo_tomb megallok, FILE *fajl);

#endif //MAIN_C_MEGALLO_H
