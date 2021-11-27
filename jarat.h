#ifndef MAIN_C_JARAT_H
#define MAIN_C_JARAT_H

#include "ido.h"
#include "megallo.h"

typedef struct Jarat {
    char nev[51];
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    Megallo_list *megallok;
} Jarat;

typedef struct Jarat_list {
    Jarat jarat;
    struct Jarat_list *kov;
} Jarat_list;

void jarat_felszabadit(Jarat_list *elso_jarat);

/* jarat_keres
 * Megkeres egy járatot a megadott tömbön, a neve alapján.
 * @param Jarat_tomb jaratok A tömb, amin keresni kell.
 * @param char* nev A keresett járat neve
 * @return Jarat* A megtalált járat pointere
 * */
Jarat *jarat_keres(Jarat_list *elso_jarat, char *nev);

/* jarat_hozzaad
 * */
Jarat_list *jarat_hozzaad(Jarat_list *elso_jarat, Jarat jarat);

/* jarat_beolvasas
 * Beolvassa a megadott fájlból a járatokat.
 * @param FILE* fajl A fájl, amiből beolvassa a járatokat
 * @return Jarat_tomb Járatok listájának structja
 * */
Jarat_list *jarat_beolvas(Jarat_list *elso_jarat, FILE *fajl, Megallo_list *elso_megallo);

/* jarat_kiir
 * Kiirja az adott járat adatait
 * @param Jarat jarat A kiirandó járat
 * @return
 * */
void jarat_kiir(Jarat jarat);

/* jarat_mentes
 * Elmenti egy a beolvasással azonos formátumú fájlba a megadott járatokat tartalmazó lista elemeit.
 * @param Jarat_list* elso_jarat A megadott járat lista
 * @param FILE* fajl A kiirandó fájl
 * @return
 * */
void jarat_mentes(Jarat_list *elso_jarat, FILE *fajl);

#endif //MAIN_C_JARAT_H
