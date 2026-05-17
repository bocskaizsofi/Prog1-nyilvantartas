#ifndef HALLGATO_H_INCLUDED
#define HALLGATO_H_INCLUDED
#include "debugmalloc.h"
#include "kereses.h"
#include "seged.h"

/*typedef struct kurzus kurzus;
typedef struct hallgato_lista hallgato_lista;
typedef struct tanar tanar;*/
struct tanar;
struct kurzus;

typedef struct hallgato_lista{
    hallgato *hallgato_p;
    struct hallgato_lista *kov;
} hallgato_lista;

typedef struct kurzus_lista{
    kurzus *kurzus_p;
    struct kurzus_lista *kov;
} kurzus_lista;

typedef struct hallgato{
    char nev[40];
    char neptun[7];
    kurzus *labor;
    kurzus *gyakorlat;
    kurzus *eloadas;
    char jelenlet_labor[15];
    char jelenlet_gyakorlat[15];
    int kisZH[6];
    int ZH1;
    int ZH2;
    int IMSC;
    int NHF;
    int szorgalmi;
    struct hallgato *kov;
} hallgato;

typedef struct pontok{
    hallgato *hallgato;
    int pont;
} pontok;

hallgato_lista *hallgato_lista_beszur(hallgato_lista *eleje, hallgato *beszurt);

hallgato_lista *hallgato_lista_torles(hallgato_lista *eleje, hallgato *torolt);

hallgato *hallgato_beszur(hallgato *hallgato_p, hallgato *beszurt);

hallgato *hallgato_beolvas(hallgato *hallgato_p, int *hallgato_db, kurzus *kurzus_p);

hallgato *hallgato_felv(hallgato *hallgato_ptr, int *hallgato_db, kurzus *kurzus_ptr);

void hallgato_modosit(hallgato *hallgato_p, kurzus *kurzus_p);

void mentes_hallgato(hallgato *hallgato_ptr);

void felszabadit_hallgato(hallgato *hallgato_ptr);

#endif // HALLGATO_H_INCLUDED
