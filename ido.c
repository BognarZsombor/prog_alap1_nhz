#include <stdio.h>
#include "ido.h"

Ido str_to_ido(char *str) {
    Ido ido;
    sscanf(str, "%d:%d", &ido.ora, &ido.perc);
    return ido;
}
