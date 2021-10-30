#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int ora, perc;
} Ido;

typedef struct {
    char *busz;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    char **megallok;
    Ido *idopontok;
} Jarat;

typedef enum {segitseg, beolvas, kiir, mentes, megallo, utvonal, kilep, hibas} parancsok;

/* str_to_parancs()
 * Visszaadja melyik előre definiált paranccsal egyenlő a beérkezett string.
 * A string eleji szóközök nélkül értelmezi a parancsot. A sor elejéről leszedi a parancsot és szóközöket.
 * @param char* sor A beérkező sor
 * @return parancsok közül ad vissza egyet
 * */
int str_to_parancs(char sor[]) {
    // leszedjük az első szóközig/sorvégéig tartó stringet, ez lesz maga a parancs
    char parancs[50+1];
    int i = 0;
    while (sor[i] == ' ')
        i++;
    int l = 0;
    while (sor[i] != ' ' && sor[i] != '\n') {
        parancs[l++] = sor[i++];
    }
    parancs[l] = '\0';

    // a parancsból leszedjük az előbb kiválasztott parancsot
    // átirjuk a parancsot kihagyva az összes elemet, az elejétől kezdődően
    int k = 0;
    int j = i+1;
    while (sor[j] != '\n') {
        sor[k++] = sor[j++];
    }
    sor[k] = '\0';

    if (strcmp(parancs, "segitseg") == 0)
        return segitseg;
    else if (strcmp(parancs, "beolvas") == 0)
        return beolvas;
    else if (strcmp(parancs, "kiir") == 0)
        return kiir;
    else if (strcmp(parancs, "mentes") == 0)
        return mentes;
    else if (strcmp(parancs, "megallo") == 0)
        return megallo;
    else if (strcmp(parancs, "utvonal") == 0)
        return utvonal;
    else if (strcmp(parancs, "kilep") == 0)
        return kilep;
    else
        return hibas;
}

int main() {
    bool futas = true;
    char sor[50+1];
    while (futas) {
        printf("Parancs(max 50 karakter):");
        if (fgets(sor, 51, stdin) == NULL) {
            printf("Hiba a sor beolvasása közben.");
            return -1;
        }
        switch (str_to_parancs(sor)) {
            case segitseg:
                printf("Parancsok: segitseg, beolvas, kiir, mentes, megallo, utvonal, kilep\n");
                break;
            case beolvas:
                break;
            case kiir:
                break;
            case mentes:
                break;
            case megallo:
                break;
            case utvonal:
                break;
            case kilep:
                futas = false;
                break;
            case hibas:
                printf("Nincs ilyen parancs.\n");
                break;
        }
    }

    return 0;
}
