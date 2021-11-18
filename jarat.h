#ifndef MAIN_C_JARAT_H
#define MAIN_C_JARAT_H

#include "ido.h"
#include "megallo.h"

typedef struct Jarat {
    char *nev;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    Megallo_list *megallok;
    Ido *idopontok;
    int meret;
    struct Jarat *kov;
} Jarat;

/* jarat_keres
 * Megkeres egy járatot a megadott tömbön, a neve alapján.
 * @param Jarat_tomb jaratok A tömb, amin keresni kell.
 * @param char* nev A keresett járat neve
 * @return Jarat* A megtalált járat pointere
 * */
Jarat *jarat_keres(Jarat *elso_jarat, char *nev);

/* beolvas_fg
 * Beolvassa a megadott fájlból a járatokat.
 * @param FILE* fajl A fájl, amiből beolvassa a járatokat
 * @return Jarat_tomb Járatok listájának structja
 * */
Jarat *beolvas_fg(Jarat *elso_jarat, FILE *fajl, Megallo *elso_megallo);

/* kiir_fg
 * */
void kiir_fg(Jarat *jarat);

/* mentes_fg
 * */
void mentes_fg(Jarat *elso_jarat, FILE *fajl);

#endif //MAIN_C_JARAT_H
