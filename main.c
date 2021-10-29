#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {segitseg, beolvas, kiir, mentes, megallo, utvonal, kilep, hibas} parancsok;

int str_to_parancs(char parancs[]) {
    char temp_parancs[50+1];
    int i = 0;
    for (i = 0; parancs[i] != ' '; ++i) {
        temp_parancs[i] = parancs[i];
    }
    temp_parancs[i] = '\0';

    for (int j = i; temp_parancs[i]; ++i) {

    }

    if (strcmp(temp_parancs, "segitseg"))
        return segitseg;
    else if (strcmp(temp_parancs, "beolvas"))
        return beolvas;
    else if (strcmp(temp_parancs, "kiir"))
        return kiir;
    else if (strcmp(temp_parancs, "mentes"))
        return mentes;
    else if (strcmp(temp_parancs, "megallo"))
        return megallo;
    else if (strcmp(temp_parancs, "utvonal"))
        return utvonal;
    else if (strcmp(temp_parancs, "kilep"))
        return kilep;
    else
        return hibas;
}

void datum_f() {};

int main() {
    bool futas = true;
    char parancs[50+1];
    while (futas) {
        printf("Parancs:");
        fgets(parancs, 50, stdin);
        printf("%s", parancs);
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
