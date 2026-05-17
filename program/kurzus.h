#ifndef KURZUS_H_INCLUDED
#define KURZUS_H_INCLUDED

#include "debugmalloc.h"
#include "jegy_szamol.h"
#include "jelenlet_ertekeles.h"
#include "kereses.h"
#include "visszajelzo.h"
#include "seged.h"

struct kurzus_lista;
struct hallgato;
struct tanar;
struct hallgato_lista;


typedef struct kurzus{
    char kurzus_kod[10];
    char idopont[9];
    char helyszin[10];
    tanar *oktato;
    int letszam;
    hallgato_lista *hallgatok;
    struct kurzus *kov;
} kurzus;

typedef struct kurzusok_db{
    int labor_db;
    int gyakorlat_db;
    int eloadas_db;
} kurzusok_db;

kurzus *kurzus_beszur(kurzus *kurzus_p, kurzus *adat);

kurzus_lista *kurzus_lista_beszur(kurzus_lista *eleje, kurzus *beszurt);

kurzus_lista *kurzus_lista_torles(kurzus_lista *eleje, kurzus *torolt);

kurzus *kurzus_beolvas(kurzus *kurzus_p, kurzusok_db *kurzus_db, tanar *tanar_p);

void kurzus_modosit(kurzus *kurzus_p, tanar *tanar_p);

kurzus *kurzus_felv(kurzus *kurzus_ptr, kurzusok_db *kurzus_db, tanar *tanar_ptr);

void felszabadit_kurzus(kurzus *kurzus_ptr);

void mentes_kurzus(kurzus *kurzus_ptr);

#endif // KURZUS_H_INCLUDED
