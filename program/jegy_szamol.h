#ifndef JEGY_SZAMOL_H_INCLUDED
#define JEGY_SZAMOL_H_INCLUDED

#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "jelenlet_ertekeles.h"
#include "kereses.h"
#include "seged.h"

int kisZH_pont(hallgato *hallgato_p);

void jelenlet_db( hallgato *hallgato_p, int *labor, int *gyakorlat);

int ZH_pont( hallgato *hallgato_p);

int jegy( hallgato *hallgato_p, int *targypontszam);

#endif // JEGY_SZAMOL_H_INCLUDED
