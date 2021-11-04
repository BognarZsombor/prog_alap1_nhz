#include <stdlib.h>
#include "seged.h"

char *kov_szo(char valaszto, FILE *fajl, int *szo_vege) {
    int meret = 0;
    char *szo = (char*) malloc(meret * sizeof(char));

    char c;
    do {
        meret++;
        szo = (char*) realloc(szo, meret * sizeof(char));
        c = getc(fajl);
        szo[meret-1] = c;
    } while (c != valaszto && c != '\n' && c != EOF);

    if (szo_vege != NULL) {
        *szo_vege = c;
        szo[meret-1] = '\0';
    }
    return szo;
}
