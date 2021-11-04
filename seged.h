#ifndef MAIN_C_SEGED_H
#define MAIN_C_SEGED_H

#include <stdio.h>

/* kov_szo
 * Beolvassa a megadott fájlból a választóig tartó stringet.
 * @param char valaszto Ez a feltétele a string végének
 * @param FILE* fajl A fájl, amiből beolvassa a stringet
 * @param char* szo_vege Azt jelzi, hogy mivel végződött a string (valaszto, \n, EOF)
 * @return char* A beolvasott string
 * */
char *kov_szo(char valaszto, FILE *fajl, int *szo_vege);

#endif //MAIN_C_SEGED_H
