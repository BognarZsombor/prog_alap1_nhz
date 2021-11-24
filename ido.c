#include <stdio.h>
#include "debugmalloc.h"
#include "ido.h"

Ido str_to_ido(char *str) {
    Ido ido;
    sscanf(str, "%d:%d", &ido.ora, &ido.perc);
    return ido;
}

int ido_to_int(Ido i1) {
    return i1.ora * 60 + i1.perc;
}

Ido int_to_ido(int i1) {
    Ido ido;
    ido.ora = i1 / 60;
    ido.perc = i1 % 60;
    return ido;
}

Ido ido_osszead(Ido i1, Ido i2) {
    Ido ido;
    int osszeg = ido_to_int(i1) + ido_to_int(i2);
    ido.ora = (osszeg / 60) % 24;
    ido.perc = osszeg % 60;
    return ido;
}

int ido_cmp(Ido i1, Ido i2) {
    int a = ido_to_int(i1);
    int b = ido_to_int(i2);
    return a == b ? 0 : a > b ? 1 : -1;
}
