#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {segitseg, beolvas, kiir, mentes, megallo, utvonal, kilep, hibas} parancsok;

int str_to_parancs(char parancs[]) {
    // leszedjük az első szóközig/sorvégéig tartó stringet, ez lesz maga a parancs
    char temp_parancs[50+1];
    int i = 0;
    while (parancs[i] != ' ' && parancs[i] != '\n') {
        temp_parancs[i] = parancs[i];
        i++;
    }
    temp_parancs[i] = '\0';

    // a parancsból leszedjük az előbb kiválasztott parancsot
    // átirjuk a parancsot kihagyva az összes elemet, az elejétől kezdődően
    int k = 0;
    int j = i;
    while (parancs[j] != '\n') {
        parancs[k++] = parancs[j++];
    }
    parancs[j] = '\0';

    if (strcmp(temp_parancs, "segitseg") == 0)
        return segitseg;
    else if (strcmp(temp_parancs, "beolvas") == 0)
        return beolvas;
    else if (strcmp(temp_parancs, "kiir") == 0)
        return kiir;
    else if (strcmp(temp_parancs, "mentes") == 0)
        return mentes;
    else if (strcmp(temp_parancs, "megallo") == 0)
        return megallo;
    else if (strcmp(temp_parancs, "utvonal") == 0)
        return utvonal;
    else if (strcmp(temp_parancs, "kilep") == 0)
        return kilep;
    else
        return hibas;
}

void datum_f() {};

int main() {
    bool futas = true;
    char parancs[50+1];
    while (futas) {
        printf("Parancs(max 50 karakter):");
        fgets(parancs, 51, stdin);
        switch (str_to_parancs(parancs)) {
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
