#ifndef VISSZAJELZO_H_INCLUDED
#define VISSZAJELZO_H_INCLUDED

#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "jegy_szamol.h"
#include "jelenlet_ertekeles.h"
#include "kereses.h"
#include "seged.h"


void eredmeny( hallgato *hallgato_p);

void osszpont_rangsor( hallgato *hallgato_p, pontok *tomb);

void szorgalmi_rangsor( hallgato *hallgato_p, pontok *tomb, int *hallgato_db);

void rendez( pontok *tomb, int db);

void ranglista( hallgato *hallgato_p, int hallgato_db);

void statisztika( hallgato *hallgato_p, int hallgato_db);

void potlas( hallgato *hallgato_p);

#endif // VISSZAJELZO_H_INCLUDED
