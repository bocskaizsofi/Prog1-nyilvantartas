#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
#include "kereses.h"
#include "seged.h"

void kereses(kurzus *kurzus_ptr, hallgato *hallgato_ptr, tanar *tanar_ptr){
    bool uj=true;
    system("cls");
    printf("Kereses\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cHallgato\n",' ');
    printf("2)%3cKurzus\n",' ');
    printf("3)%3cOktato\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,3)){
            printf("Hiba! A fent megadott kodok kozul valasszon!\n");
            beolvas(kod,200);
    }
    switch(kod[0]){
        case '1':while(uj){
                    hallgato_keres(hallgato_ptr);
                    uj=uj_inditas("Hallgato keresese");
                }
                break;
        case '2':while(uj){
                    kurzus_keres(kurzus_ptr);
                    uj=uj_inditas("Kurzus keresese");
                }
                break;
        default:while(uj){
                    tanar_keres(tanar_ptr);
                    uj=uj_inditas("Oktato keresese");
                }
                break;
    }

}

hallgato *hallgato_ptr_keres(hallgato *hallgato_p, char *neptun){
    hallgato *h=hallgato_p;
    while(h!=NULL&&strcmp(h->neptun,neptun)!=0){
        h=h->kov;
    }
    return h;
}

void hallgato_keres(hallgato *hallgato_p){
    system("cls");
    char neptun[9];
    printf("NEPTUN kod: ");
    beolvas(neptun,9);
    hallgato *h=hallgato_ptr_keres(hallgato_p, neptun);
    if(h==NULL)
       printf("A keresett hallgato nem talalhato az adatbazisban.");
    else{
        int labor_db=0;
        int gyakorlat_db=0;
        jelenlet_db(h,&labor_db,&gyakorlat_db);
        printf("Nev: %s\nEloadas kodja: %s\nGyakorlat kodja: %s\nGyakorlat jelenlet: %.2lf %c\n",h->nev, h->eloadas->kurzus_kod, h->gyakorlat->kurzus_kod, 100*gyakorlat_db/14.0,'%');
        printf("Labor kodja: %s\nLabor jelenlet: %.2lf %c\n",h->labor->kurzus_kod, 100*labor_db/14.0, '%');
        int pont=0;

        int akt_jegy=jegy(hallgato_p,&pont);
        printf("Targy pontszam: %d\nJegy: %d\n",pont, akt_jegy);
        printf("IMSC pont: %d",h->IMSC);
    }
    printf("\n\nTovabb: Enter lenyomasa");
    getchar();
}

kurzus *kurzus_ptr_keres(kurzus *kurzus_p, char *kurzus_kod){
    kurzus *k=kurzus_p;
    while(k!=NULL&&strcmp(k->kurzus_kod,kurzus_kod)!=0){
        k=k->kov;
    }
    return k;
}

void kurzus_keres(kurzus *kurzus_p){
    system("cls");
    char kod[12];
    printf("Kurzus kod: ");
    beolvas(kod,12);
    kurzus *k=kurzus_ptr_keres(kurzus_p, kod);
    if(k==NULL)
       printf("A keresett kurzus nem talalhato az adatbazisban.");
    else{
        printf("Idopont: %s\nHelyszin: %s\nOktato neve: %s\nOktato elerhetosege: %s",k->idopont, k->helyszin, k->oktato->nev, k->oktato->elerhetoseg);
    }
    printf("\n\nTovabb: Enter lenyomasa");
    getchar();
}

tanar *tanar_ptr_keres(tanar *tanar_p, char *nev){
    tanar *t;
    t=tanar_p;
    while(t!=NULL&&strcmp(t->nev,nev)!=0){
        t=t->kov;
    }
    return t;
}

void tanar_keres(tanar *tanar_p){
    system("cls");
    char nev[42];
    printf("Oktato neve: ");
    beolvas(nev,42);
    tanar *t=tanar_ptr_keres(tanar_p, nev);
    if(t==NULL)
       printf("A keresett oktato nem talalhato az adatbazisban.");
    else{
        printf("Elerhetoseg: %s\nKurzusok:",t->elerhetoseg);
        kurzus_lista *k=t->kurzusok;
        while(k!=NULL){
            printf(" %s",k->kurzus_p->kurzus_kod);
            k=k->kov;
        }
    }
    printf("\n\nTovabb: Enter lenyomasa");
    getchar();
}
