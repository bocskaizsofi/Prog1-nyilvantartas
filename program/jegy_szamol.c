#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "jegy_szamol.h"
#include "jelenlet_ertekeles.h"
#include "kereses.h"
#include "seged.h"

int kisZH_pont(hallgato *hallgato_p){
    int minid1=0;
    for(int i=1; i<6; i+=1){
        if(hallgato_p->kisZH[i] < hallgato_p->kisZH[minid1])
            minid1=i;
    }
    int minid2=0;
    if(minid1==0)
        minid2=1;
    for(int i=0; i<6; i+=1){
        if(i != minid1 && hallgato_p->kisZH[i] < hallgato_p->kisZH[minid2])
            minid2=i;
    }
    int pont=0;
    for(int i=0; i<6; i+=1){
        if(i != minid1 && i != minid2)
            pont+=hallgato_p->kisZH[i];
    }
    return pont;
}

void jelenlet_db(hallgato *hallgato_p, int *labor, int *gyakorlat){
    *labor=*gyakorlat=0;
    for(int i=0; i<15; i+=1){
        if(hallgato_p->jelenlet_labor[i]=='1')
            *labor += 1;
        if(hallgato_p->jelenlet_gyakorlat[i]=='1')
            *gyakorlat += 1;
    }
}

int ZH_pont(hallgato *hallgato_p){
    if(hallgato_p->ZH2 > hallgato_p->ZH1)
        return 2*hallgato_p->ZH2;
    return hallgato_p->ZH2 + hallgato_p->ZH1;
}

int jegy(hallgato *hallgato_p, int *targypontszam){
    //max(NZH1 + NZH2, 2 × NZH2) + sum(legjobb4(KZH1, KZH2, KZH3, KZH4, KZH5, KZH6)) + NHF + SZORGALMI + NZH_IMSc
    int kisZH=kisZH_pont(hallgato_p);
    int ZH=ZH_pont(hallgato_p);
    *targypontszam = ZH + kisZH + hallgato_p->NHF + hallgato_p->szorgalmi + hallgato_p->IMSC;
    int labor_db, gyakorlat_db;
    jelenlet_db(hallgato_p, &labor_db, &gyakorlat_db);
    if(labor_db >= 10 && gyakorlat_db >= 10 && kisZH >= 20 && ZH >= 40 && hallgato_p->NHF >= 10 && *targypontszam > 69){
        if(*targypontszam >= 125)
            return 5;
        if(*targypontszam >= 110)
            return 4;
        if(*targypontszam >= 90)
            return 3;
        if(*targypontszam >= 70)
            return 2;
    }
    return 1;
}

