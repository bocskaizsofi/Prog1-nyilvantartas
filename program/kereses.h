#ifndef KERESES_H_INCLUDED
#define KERESES_H_INCLUDED

#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "seged.h"

void kereses( kurzus *kurzus_ptr, hallgato *hallgato_ptr, tanar *tanar_ptr);

 hallgato *hallgato_ptr_keres( hallgato *hallgato_p, char *neptun);

void hallgato_keres( hallgato *hallgato_p);

 kurzus *kurzus_ptr_keres( kurzus *kurzus_p, char *kurzus_kod);

void kurzus_keres( kurzus *kurzus_p);

 tanar *tanar_ptr_keres( tanar *tanar_p, char *nev);

void tanar_keres( tanar *tanar_p);

#endif // KERESES_H_INCLUDED
