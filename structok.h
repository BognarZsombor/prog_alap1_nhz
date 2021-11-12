#ifndef PROG_ALAP1_NHZ_STRUCTOK_H
#define PROG_ALAP1_NHZ_STRUCTOK_H

typedef struct {
    int ora, perc;
} Ido;

typedef struct {
    char *nev;
    char **atszallasok;
    int meret;
} Megallo;

typedef struct {
    Megallo *tomb;
    int meret;
} Megallo_tomb;

typedef struct {
    char *nev;
    Ido elso_indulas, utolso_indulas, tovabbi_indulasok;
    Megallo *megallok;
    Ido *idopontok;
    int meret;
} Jarat;

typedef struct {
    Jarat *tomb;
    int meret;
} Jarat_tomb;

#endif //PROG_ALAP1_NHZ_STRUCTOK_H
