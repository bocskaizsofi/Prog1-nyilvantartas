#ifndef SEGED_H_INCLUDED
#define SEGED_H_INCLUDED
#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "kereses.h"

typedef struct kurzus kurzus;
typedef struct hallgato hallgato;
typedef struct tanar tanar;

void fomenu_megjelenit();

void beolvas(char *str, int karakter_db);

bool ervenyes(char *kod, int lehetosegdb);

bool uj_inditas(char *szoveg);

void modositas(kurzus *kurzus_ptr, hallgato *hallgato_ptr, tanar *tanar_ptr);

#endif // SEGED_H_INCLUDED
