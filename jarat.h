#ifndef MAIN_C_JARAT_H
#define MAIN_C_JARAT_H

#include "ido.h"
#include "megallo.h"

typedef struct Jarat {
    char *nev;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    Megallo *megallok;
    Ido *idopontok;
    struct Jarat *kov;
} Jarat;

/* jarat_kiir
 * Kiirja a megadott járat adatait.
 * @param Jarat jarat A kiirandó járat
 * */
void jarat_kiir(Jarat jarat);

/* jarat_keres
 * Megkeres egy járatot a megadott tömbön, a neve alapján.
 * @param Jarat_tomb jaratok A tömb, amin keresni kell.
 * @param char* nev A keresett járat neve
 * @return Jarat* A megtalált járat pointere
 * */
Jarat *jarat_keres(Jarat_tomb jaratok, char *nev);

/* beolvas_fg
 * Beolvassa a megadott fájlból a járatokat.
 * @param FILE* fajl A fájl, amiből beolvassa a járatokat
 * @return Jarat_tomb Járatok listájának structja
 * */
Jarat_tomb beolvas_fg(FILE *fajl, Megallo_tomb megallok);

/* jarat_hozzaad
 * Hozzáad egy járattömbhöz egy másik járattömböt
 * @param Jarat_tomb jaratok Amihez hozzáadjuk az új járatokat
 * @param Jarat_tomb temp_jaratok Amit hozzáadunk az eredeti járatokhoz
 * */
void jarat_hozzaad(Jarat_tomb jaratok, Jarat_tomb temp_jaratok);

/* kiir_fg
 * */
void kiir_fg(Jarat_tomb jaratok, char *nev);

/* mentes_fg
 * */
void mentes_fg(Jarat_tomb jaratok, FILE *fajl);

#endif //MAIN_C_JARAT_H
