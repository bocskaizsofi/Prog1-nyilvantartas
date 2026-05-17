#ifndef TANAR_H_INCLUDED
#define TANAR_H_INCLUDED
#include "debugmalloc.h"
#include "kereses.h"
#include "seged.h"

struct kurzus_lista;
struct kurzus;
struct hallgato;
struct hallgato_lista;

typedef struct tanar{
    char nev[40];
    char elerhetoseg[30];
    int kurzus_db;
    kurzus_lista *kurzusok;
    struct tanar *kov;
} tanar;

tanar *tanar_beszur(tanar *tanar_p, tanar *adat);

tanar *tanar_listaz_beolvas(tanar *tanar_p);

void oktato_modosit(tanar *tanar_p);

tanar *tanar_beolvas(tanar *tanar_p, int *tanar_db);

tanar *oktato_felv(tanar *tanar_ptr, int *tanar_db);

void felszabadit_tanar(tanar *tanar_ptr);

void mentes_tanar(tanar *tanar_ptr);

#endif // TANAR_H_INCLUDED
