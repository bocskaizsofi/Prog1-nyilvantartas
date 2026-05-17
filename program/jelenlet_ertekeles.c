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

void jelenlet_ertekeles(kurzus *kurzus_ptr, hallgato *hallgato_ptr){
    system("cls");
    printf("Jelenlet, ertekeles rogzitese\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cJelenlet\n",' ');
    printf("2)%3cZH pontok\n",' ');
    printf("3)%3cNHF pontok\n",' ');
    printf("4)%3cSzorgalmi pontok\n",' ');
    printf("5)%3cIMSC pontok\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,5)){
            printf("Hiba! A fent megadott kodok kozul valasszon!\n");
            beolvas(kod,200);
    }
    bool uj=true;
    switch(kod[0]){
        case '1':while(uj){
                    jelenlet(kurzus_ptr);
                    uj=uj_inditas("Jelenlet");
                }
                break;
        case '2':while(uj){
                    ZH(kurzus_ptr);
                    uj=uj_inditas("ZH pontok");
                 }
                 break;
        case '3':while(uj){
                      NHF(kurzus_ptr);
                      uj=uj_inditas("NHF pontok");
                 }
                 break;
        case '4':while(uj){
                      szorgalmi_IMSC(hallgato_ptr,true);
                      uj=uj_inditas("Szorgalmi pontok");
                 }
                 break;
        default:while(uj){
                    szorgalmi_IMSC(hallgato_ptr,false);
                    uj=uj_inditas("IMSC pontok");
                 }
                 break;
        }
}

void jelenlet(kurzus *kurzus_p){
    system("cls");
    printf("Jelenlet rogzitese\n");
    printf("%-*s %-*s\n",20, "Kurzus kodja",50,"Laborvezeto/Gyakorlatvezeto");
    kurzus *k=kurzus_p;
    while(k!=NULL){
        if(k->kurzus_kod[0]=='L'||k->kurzus_kod[0]=='G')
            printf("%-*s %-*s\n", 20, k->kurzus_kod, 50,k->oktato->nev);
        k=k->kov;
    }
    printf("Valasztott kurzus kod: ");
    char kod[200];
    beolvas(kod,200);
    k=kurzus_ptr_keres(kurzus_p,kod);
    while(k==NULL||k->kurzus_kod[0]=='E'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kod,200);
        k=kurzus_ptr_keres(kurzus_p,kod);
    }
    printf("Het sorszama (1-14 kozott): ");
    int het;
    scanf("%d",&het);
    while(!(het<=14&&het>=1)){
        printf("Ervenytelen het, 1-14 kozti sorszamot adjon meg!\n");
        scanf("%d",&het);
    }
    system("cls");
    getchar();
    char c;
    printf("%-*s %-*s %-*s %-*d %-*s %-*s %-*s\n\n", 8, "Kurzus: ",10,k->kurzus_kod, 5,"Het: ",4, het, 20, "Hianyzas=0", 20, "Jelenlet=1",20,"Nincs modositas=Enter");
    hallgato_lista *h=k->hallgatok;
    while(h!=NULL){
        printf("%-*s %-*s %-*s %-*s\n",5,"Nev: ", 50, h->hallgato_p->nev, 12,"NEPTUN kod: ", 10, h->hallgato_p->neptun);
        c=getchar();
        if(c=='0'||c=='1'){
            if(k->kurzus_kod[0]=='L')
                h->hallgato_p->jelenlet_labor[het-1]=c;
            else
                h->hallgato_p->jelenlet_gyakorlat[het-1]=c;
            getchar();
        }
        h=h->kov;
    }
}

void ZH(kurzus *kurzus_p){
    system("cls");
    printf("ZH pont rogzitese\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3c1. nagy ZH\n",' ');
    printf("2)%3c2. nagy ZH\n",' ');
    printf("3)%3cKis ZH\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,3)){
            printf("Hiba! A fent megadott kodok kozul valasszon!\n");
            beolvas(kod,200);
    }
    printf("%-*s %-*s\n",20, "Kurzus kodja",50,"Gyakorlatvezeto");
    kurzus *k=kurzus_p;
    while(k!=NULL){
        if(k->kurzus_kod[0]=='G')
         printf("%-*s %-*s\n", 20, k->kurzus_kod, 50,k->oktato->nev);
        k=k->kov;
    }
    printf("Valasztott kurzus kod: ");
    char kurzus_kod[200];
    beolvas(kurzus_kod,200);
    k=kurzus_ptr_keres(kurzus_p,kurzus_kod);
    while(k==NULL||k->kurzus_kod[0]!='G'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kurzus_kod,200);
        k=kurzus_ptr_keres(kurzus_p,kurzus_kod);
    }
    if(kod[0]=='1'){
        nagy_ZH(k,true);
    }
    else if(kod[0]=='2'){
        nagy_ZH(k,false);
    }
    else{
        kis_ZH(k);
    }
}

void kis_ZH(kurzus *kurzus_p){
    printf("Kis ZH sorszama (1-6 kozott): ");
    int sorszam;
    scanf("%d",&sorszam);
    while(!(sorszam<=6&&sorszam>=1)){
        printf("Ervenytelen sorszam, 1-6 kozti sorszamot adjon meg!\n");
        scanf("%d",&sorszam);
    }
    getchar();
    system("cls");
    char kod[4];
    printf("%-*s %-*s %-*s %-*d %-*s\n\n", 8, "Kurzus: ",10,kurzus_p->kurzus_kod, 9,"Sorszam: ",4, sorszam,20,"Nincs modositas=Enter");
    hallgato_lista *h=kurzus_p->hallgatok;
    printf("%-*s %-*s\n",20,"NEPTUN kod", 50,"Nev");
    while(h!=NULL){
        printf("%-*s %-*s\n",20,h->hallgato_p->neptun, 50,h->hallgato_p->nev);
        beolvas(kod,4);
        if(kod[0]!='\n'){
            h->hallgato_p->kisZH[sorszam-1]=atoi(kod);
        }

        h=h->kov;
    }
}

void nagy_ZH(kurzus *kurzus_p, bool elso){
    system("cls");
    char kod[4];
    if(elso)
        printf("%-*s %-*s %-*s %-*s\n\n", 8, "Kurzus: ",10,kurzus_p->kurzus_kod, 15,"Elso nagy ZH",20,"Nincs modositas=Enter");
    else
        printf("%-*s %-*s %-*s %-*s\n\n", 8, "Kurzus: ",10,kurzus_p->kurzus_kod, 18,"Masodik nagy ZH",20,"Nincs modositas=Enter");
    hallgato_lista *h=kurzus_p->hallgatok;
    printf("%-*s %-*s\n",20,"NEPTUN kod", 50,"Nev");
    while(h!=NULL){
        printf("%-*s %-*s\n",20,h->hallgato_p->neptun, 50,h->hallgato_p->nev);
        beolvas(kod,4);
        if(kod[0]!='\n'){
            if(elso)
                h->hallgato_p->ZH1=atoi(kod);
            else
                h->hallgato_p->ZH2=atoi(kod);
        }

        h=h->kov;
    }
}

void NHF(kurzus *kurzus_p){
    system("cls");
    printf("NHF pont rogzitese\n");
    printf("%-*s %-*s\n",20, "Kurzus kodja",50,"Laborvezeto");
    kurzus *k=kurzus_p;
    while(k!=NULL){
        if(k->kurzus_kod[0]=='L')
         printf("%-*s %-*s\n", 20, k->kurzus_kod, 50,k->oktato->nev);

        k=k->kov;
    }
    printf("Valasztott kurzus kod: ");
    char kod[200];
    beolvas(kod,200);
    k=kurzus_ptr_keres(kurzus_p,kod);
    while(k==NULL||k->kurzus_kod[0]!='L'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kod,4);
        k=kurzus_p;
        while(k!=NULL&&strcmp(k->kurzus_kod,kod)!=0){
            k=k->kov;
        }
    }
    system("cls");
    printf("%-*s %-*s %-*s %-*s\n\n", 8, "Kurzus",11,k->kurzus_kod, 10,"NFH",25,"Nincs modositas=Enter");
    hallgato_lista *h=k->hallgatok;
    printf("%-*s %-*s\n",20,"NEPTUN kod", 50,"Nev");
    char pont[4];
    while(h!=NULL){
        printf("%-*s %-*s\n",20,h->hallgato_p->neptun, 50,h->hallgato_p->nev);
        beolvas(pont,4);
        if(pont[0]!='\n'){
            h->hallgato_p->NHF=atoi(pont);
        }
        h=h->kov;
    }
}

void szorgalmi_IMSC(hallgato *hallgato_p, bool szorgalmi){
    system("cls");
    printf("%s pont rogzitese\n",szorgalmi ? "Szorgalmi" : "IMSC");
    printf("NEPTUN kod: ");
    char kod[10];
    beolvas(kod,10);
    hallgato *h=hallgato_ptr_keres(hallgato_p,kod);
    while(h==NULL){
        printf("A keresett hallgato nem talalhato az adatbazisban.\n");
        beolvas(kod,10);
        h=hallgato_ptr_keres(hallgato_p,kod);
    }
    printf("%s pont: ",szorgalmi ? "Szorgalmi" : "IMSC");
    int pont;
    scanf("%d",&pont);
    if(szorgalmi){
        h->szorgalmi+=pont;
    }
    else{
        h->IMSC+=pont;
    }
    getchar();
}
