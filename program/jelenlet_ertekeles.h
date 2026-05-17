#ifndef JELENLET_ERTEKELES_H_INCLUDED
#define JELENLET_ERTEKELES_H_INCLUDED

#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "jegy_szamol.h"
#include "kereses.h"
#include "visszajelzo.h"
#include "seged.h"

void jelenlet_ertekeles( kurzus *kurzus_ptr, hallgato *hallgato_ptr);

void jelenlet( kurzus *kurzus_p);

void ZH( kurzus *kurzus_p);

void kis_ZH( kurzus *kurzus_p);

void nagy_ZH( kurzus *kurzus_p, bool elso);

void NHF( kurzus *kurzus_p);

void szorgalmi_IMSC( hallgato *hallgato_p, bool szorgalmi);

//typedef struct kurzus kurzus;

/*void jelenlet_ertekeles(struct kurzus *kurzus_ptr,struct hallgato *hallgato_ptr);

void jelenlet(struct kurzus *kurzus_p);

void ZH(struct kurzus *kurzus_p);

void kis_ZH(struct kurzus *kurzus_p);

void nagy_ZH(struct kurzus *kurzus_p, bool elso);

void NHF(struct kurzus *kurzus_p);

void szorgalmi_IMSC(struct hallgato *hallgato_p, bool szorgalmi)*/




#endif // JELENLET_ERTEKELES_H_INCLUDED
