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
#include "visszajelzo.h"
#include "seged.h"

void eredmeny(hallgato *hallgato_p){
    system("cls");
    printf("Hallgatok eredmenyei:\n");
    hallgato *h=hallgato_p;
    int akt_jegy, pont;
    printf("%-*s %-*s %-*s %-*s %-*s %-*s\n",40, "Nev",15,"NEPTUN kod",15,"Targypontszam",15, "Jegy",15 ,"IMSC pont", 20, "Teljesites");
    while(h!=NULL){
        akt_jegy=jegy(h,&pont);
        printf("%-*s %-*s %-*d %-*d %-*d %-*s\n",40, h->nev,15,h->neptun,15,pont,15, akt_jegy,15 ,h->IMSC, 20, akt_jegy>1?"TELJESITETTE":"NEM TELJESITETTE");
        h=h->kov;
    }
    printf("\nTovabb: Enter lenyomasa");
    getchar();
}

void osszpont_rangsor(hallgato *hallgato_p, pontok *tomb){
    hallgato *h=hallgato_p;
    int id=0;
    int pont;
    while(h!=NULL){
        jegy(h,&pont);
        tomb[id].hallgato=h;
        tomb[id].pont=pont;
        id+=1;
        h=h->kov;
    }
}

void szorgalmi_rangsor(hallgato *hallgato_p, pontok *tomb, int *hallgato_db){
    hallgato *h=hallgato_p;
    int id=0;
    while(h!=NULL){
        if(h->szorgalmi==0){
            *hallgato_db-=1;
        }
        else{
            tomb[id].hallgato=h;
            tomb[id].pont=h->szorgalmi;
            id+=1;
        }
        h=h->kov;
    }
}

void rendez(pontok *tomb, int db){
    for (int i = 0; i < db-1; ++i) {
        int minid = i;
        for (int j = i+1; j < db; ++j)
            if (tomb[j].pont > tomb[minid].pont)
                minid = j;

        if (minid != i) {
            pontok temp;
            temp=tomb[minid];
            tomb[minid] = tomb[i];
            tomb[i] = temp;
        }
    }
}

void ranglista(hallgato *hallgato_p, int hallgato_db){
    system("cls");
    printf("Ranglista\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cOsszpontszam szerint\n",' ');
    printf("2)%3cSzorgalmi pontok szerint\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,2)){
        printf("Hiba! A fent megadott kodok kozul valasszon!\n");
        beolvas(kod,200);
    }
    pontok rangsor[hallgato_db];
    if(kod[0]=='1'){
        osszpont_rangsor(hallgato_p, rangsor);
    }
    else{
        szorgalmi_rangsor(hallgato_p, rangsor, &hallgato_db);
    }

    rendez(rangsor, hallgato_db);
    system("cls");
    printf("%-*s %-*s %-*s\n",15,"Helyezes", 50, "Nev",10,"Pontszam");
    int helyezes=1;
    int elozo=rangsor[0].pont;
    for(int i=0; i<hallgato_db; i+=1){
        if(rangsor[i].pont<elozo){
            elozo=rangsor[i].pont;
            helyezes+=1;
        }
        printf("%-*d %-*s %-*d\n",15,helyezes, 50, rangsor[i].hallgato->nev,10,rangsor[i].pont);
    }
    printf("\nTovabb: Enter lenyomasa");
    getchar();
}

void statisztika(hallgato *hallgato_p, int hallgato_db){
    system("cls");
    printf("Statisztika:\n");
    hallgato *h=hallgato_p;
    int akt_jegy, pont;
    double jegyek_osszege=0;
    double pontok_osszege=0;
    int jegy_db[5]={0};
    while(h!=NULL){
        akt_jegy=jegy(h,&pont);
        jegy_db[akt_jegy-1]++;
        jegyek_osszege+=akt_jegy;
        pontok_osszege+=pont;
        h=h->kov;
    }
    printf("Jegyek:\n");
    for(int i=0; i<5; i++){
        printf("%3d - %d darab\n",i+1,jegy_db[i]);
    }
    printf("Jegyek atlaga: %.2lf\n",jegyek_osszege/hallgato_db);
    printf("Pontszamok atlaga: %.2lf\n",pontok_osszege/hallgato_db);
    printf("Targyat teljesito diakok: %.2lf %c\n",100.0*(hallgato_db-jegy_db[0])/hallgato_db,'%');
    printf("\nTovabb: Enter lenyomasa");
    getchar();

}

void potlas(hallgato *hallgato_p){
    system("cls");
    printf("Potlasra szorulok listaja\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cNHF potlas\n",' ');
    printf("2)%3cZH potlas\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,2)){
            printf("Hiba! A fent megadott kodok kozul valasszon!\n");
            beolvas(kod,200);
    }
    system("cls");
    if(kod[0]=='1'){
        hallgato *h=hallgato_p;
        printf("NHF potlasra szorulok listaja:\n");
        printf("%-*s %-*s %-*s %-*s\n",40, "Hallgato neve",20,"NEPTUN kodja",20,"Labor kodja",40, "Laborvezeto neve");
        while(h!=NULL){
            if(h->NHF<10)
                printf("%-*s %-*s %-*s %-*s\n",40, h->nev,20,h->neptun,20,h->labor->kurzus_kod,40, h->labor->oktato->nev);
            h=h->kov;
        }
    }
    else{
        hallgato *h=hallgato_p;
        printf("ZH potlasra szorulok listaja:\n");
        printf("%-*s %-*s %-*s %-*s\n",40, "Hallgato neve",20,"NEPTUN kodja",20,"Gyakorlat kodja",40, "Gyakorlatvezeto neve");
        while(h!=NULL){
            if(ZH_pont(h)<40)
                printf("%-*s %-*s %-*s %-*s\n",40, h->nev,20,h->neptun,20,h->gyakorlat->kurzus_kod,40, h->gyakorlat->oktato->nev);
            h=h->kov;
        }
    }
    printf("\nTovabb: Enter lenyomasa");
    getchar();
}
