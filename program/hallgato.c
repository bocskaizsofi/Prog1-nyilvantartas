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

hallgato_lista *hallgato_lista_beszur(hallgato_lista *eleje, hallgato *beszurt){
    hallgato_lista *uj=(hallgato_lista*)malloc(sizeof(hallgato_lista));
    uj->hallgato_p=beszurt;
    uj->kov=eleje;
    return uj;
}

hallgato_lista *hallgato_lista_torles(hallgato_lista *eleje, hallgato *torolt){
    hallgato_lista *lemarado = NULL;
    hallgato_lista *h = eleje;
    while (h != NULL && h->hallgato_p!=torolt) {
        lemarado = h;
        h = h->kov;
    }
    if (lemarado == NULL) {
        eleje = h->kov;
        free(h);
    }
    else {
        lemarado->kov = h->kov;
        free(h);
    }
    return eleje;
}

hallgato *hallgato_beszur(hallgato *hallgato_p, hallgato *beszurt){
    hallgato *uj=(hallgato*)malloc(sizeof(hallgato));
    uj->kov=hallgato_p;
    strcpy(uj->nev,beszurt->nev);
    strcpy(uj->neptun,beszurt->neptun);
    strcpy(uj->jelenlet_gyakorlat,beszurt->jelenlet_gyakorlat);
    strcpy(uj->jelenlet_labor,beszurt->jelenlet_labor);
    for(int i=0; i<6; i+=1){
        uj->kisZH[i]=beszurt->kisZH[i];
    }
    uj->ZH1=beszurt->ZH1;
    uj->ZH2=beszurt->ZH2;
    uj->IMSC=beszurt->IMSC;
    uj->NHF=beszurt->NHF;
    uj->szorgalmi=beszurt->szorgalmi;
    return uj;
}

hallgato *hallgato_beolvas(hallgato *hallgato_p, int *hallgato_db, kurzus *kurzus_p){
   FILE *fp=fopen("hallgatok.csv","r");
    if(fp==NULL){
        printf("Nem lehet megnyitni a vezerfajlt.\n");
        return NULL;
    }
    hallgato h;
    char *labor;
    char *gyakorlat;
    char *eloadas;
    char sor[180];
    while (fgets(sor, 180, fp)!=NULL) {
        char c;
        sscanf(sor,"%c",&c);
        char *str = strtok(sor, "\",\"");
        strcpy(h.nev,str);
        str=strtok(NULL, "\",\"");
        strcpy(h.neptun,str);
        labor=strtok(NULL, "\",\"");
        gyakorlat=strtok(NULL, "\",\"");
        eloadas=strtok(NULL, "\",\"");
        str=strtok(NULL, "\",\"");
        strcpy(h.jelenlet_gyakorlat,str);
        str=strtok(NULL, "\",\"");
        strcpy(h.jelenlet_labor,str);
        for(int i=0;i<6; i+=1){
            str=strtok(NULL, "\",\"");
            h.kisZH[i]=atoi(str);
        }
        str=strtok(NULL, "\",\"");
        h.ZH1=atoi(str);
        str=strtok(NULL, "\",\"");
        h.ZH2=atoi(str);
        str=strtok(NULL, "\",\"");
        h.NHF=atoi(str);
        str=strtok(NULL, "\",\"");
        h.IMSC=atoi(str);
        str=strtok(NULL, "\",\"");
        h.szorgalmi=atoi(str);
        *hallgato_db+=1;

        hallgato_p=hallgato_beszur(hallgato_p,&h);
        hallgato_p->labor=kurzus_ptr_keres(kurzus_p,labor);
        if(hallgato_p->labor!=NULL){
            hallgato_p->labor->letszam+=1;
            hallgato_p->labor->hallgatok=hallgato_lista_beszur(hallgato_p->labor->hallgatok,hallgato_p);
        }
        hallgato_p->gyakorlat=kurzus_ptr_keres(kurzus_p,gyakorlat);
        if(hallgato_p->gyakorlat!=NULL){
            hallgato_p->gyakorlat->letszam+=1;
            hallgato_p->gyakorlat->hallgatok=hallgato_lista_beszur(hallgato_p->gyakorlat->hallgatok,hallgato_p);
        }
        hallgato_p->eloadas=kurzus_ptr_keres(kurzus_p,eloadas);
        if(hallgato_p->eloadas!=NULL){
            hallgato_p->eloadas->letszam+=1;
            hallgato_p->eloadas->hallgatok=hallgato_lista_beszur(hallgato_p->eloadas->hallgatok,hallgato_p);
        }
    }
    fclose(fp);
    return hallgato_p;
}

hallgato *hallgato_felv(hallgato *hallgato_ptr, int *hallgato_db, kurzus *kurzus_ptr){
    system("cls");
    printf("Uj hallgato felvetele\n");
    hallgato h;
    for(int i=0; i<6; i++){
        h.kisZH[i]=0;
    }
    h.ZH1=0;
    h.ZH2=0;
    h.IMSC=0;
    h.NHF=0;
    h.szorgalmi=0;
    char temp[]="00000000000000";
    strcpy(h.jelenlet_gyakorlat,temp);
    strcpy(h.jelenlet_labor,temp);
    printf("Hallgato neve: ");
    beolvas(h.nev,40);
    printf("NEPTUN kod: ");
    scanf("%s",h.neptun);
    getchar();
    hallgato_ptr=hallgato_beszur(hallgato_ptr,&h);
    printf("\nValaszthato laborok:\n");
    kurzus *k=kurzus_ptr;
    printf("%-*s %-*s %-*s %-*s %-*s\n", 10, "Kod", 15, "Idopont", 15, "Helyszin",50,"Laborvezeto",30,"Jelentkezett hallgatok szama");
    while(k!=NULL){
        if(k->kurzus_kod[0]=='L'){
            printf("%-*s %-*s %-*s %-*s %-*d\n", 10, k->kurzus_kod, 15, k->idopont, 15, k->helyszin,50,k->oktato->nev,30,k->letszam);
        }
        k=k->kov;
    }
    char kod[200];
    printf("Valasztott labor kodja: ");
    beolvas(kod,200);
    k=kurzus_ptr_keres(kurzus_ptr,kod);

    while(k==NULL||k->kurzus_kod[0]!='L'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kod,200);
        k=kurzus_ptr_keres(kurzus_ptr,kod);
    }

    k->letszam+=1;
    hallgato_ptr->labor=k;
    k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_ptr);

    printf("\nValaszthato gyakorlatok:\n");
    k=kurzus_ptr;
    printf("%-*s %-*s %-*s %-*s %-*s\n", 10, "Kod", 15, "Idopont", 15, "Helyszin",50,"Laborvezeto",30,"Jelentkezett hallgatok szama");
    while(k!=NULL){
        if(k->kurzus_kod[0]=='G'){
            printf("%-*s %-*s %-*s %-*s %-*d\n", 10, k->kurzus_kod, 15, k->idopont, 15, k->helyszin,50,k->oktato->nev,30,k->letszam);

        }
        k=k->kov;
    }
    printf("Valasztott gyakorlat kodja: ");
    beolvas(kod,200);
    k=kurzus_ptr_keres(kurzus_ptr,kod);
    while(k==NULL||k->kurzus_kod[0]!='G'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kod,200);
        k=kurzus_ptr_keres(kurzus_ptr,kod);
    }
    k->letszam+=1;
    hallgato_ptr->gyakorlat=k;
    k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_ptr);

    k=kurzus_ptr;
    printf("\nValaszthato eloadasok:\n");
    printf("%-*s %-*s %-*s %-*s %-*s\n", 10, "Kod", 15, "Idopont", 15, "Helyszin",50,"Laborvezeto",30,"Jelentkezett hallgatok szama");
    while(k!=NULL){
        if(k->kurzus_kod[0]=='E'){
            printf("%-*s %-*s %-*s %-*s %-*d\n", 10, k->kurzus_kod, 15, k->idopont, 15, k->helyszin,50,k->oktato->nev,30,k->letszam);
        }
        k=k->kov;
    }
    printf("Valasztott eloadas kodja: ");
    beolvas(kod,200);
    k=kurzus_ptr_keres(kurzus_ptr,kod);
    while(k==NULL||k->kurzus_kod[0]!='E'){
        printf("Hiba! A fent megadott kurzusok kozul valasszon!\n");
        beolvas(kod,200);
        k=kurzus_ptr_keres(kurzus_ptr,kod);
    }
    k->letszam+=1;
    hallgato_ptr->eloadas=k;
    k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_ptr);
    *hallgato_db+=1;

    return hallgato_ptr;
}

void hallgato_modosit(hallgato *hallgato_p, kurzus *kurzus_p){
    char str[40];
    printf("Modositani kivant hallgato NEPTUN kodja: ");
    beolvas(str,10);
    hallgato *h=hallgato_ptr_keres(hallgato_p,str);
    while(h==NULL){
        printf("Hiba! A megadott hallgato nem talalhato az adatbazisban!\n");
        beolvas(str,10);
        h=hallgato_ptr_keres(hallgato_p,str);
    }
    system("cls");
    printf("Nev: %s\n",h->nev);
    beolvas(str,40);
    if(str[0]!='\n')
        strcpy(h->nev,str);
    printf("NEPTUN kod: %s\n",h->neptun);
    beolvas(str,10);
    if(str[0]!='\n')
        strcpy(h->neptun,str);
    kurzus *k;
    printf("Labor kod: %s\n",h->labor->kurzus_kod);
    beolvas(str,10);
    if(str[0]!='\n'){
        k=kurzus_ptr_keres(kurzus_p,str);
        while(k==NULL||k->kurzus_kod[0]!='L'){
            printf("Hiba! A megadott kurzus nem talalhato az adatbazisban!\n");
            beolvas(str,10);
            k=kurzus_ptr_keres(kurzus_p,str);
        }
        k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_p);
        k->letszam+=1;
        hallgato_p->labor->hallgatok=hallgato_lista_torles(hallgato_p->labor->hallgatok, hallgato_p);
        hallgato_p->labor->letszam-=1;
        hallgato_p->labor=k;
    }
    printf("Gyakorlat kod: %s\n",h->gyakorlat->kurzus_kod);
    beolvas(str,10);
    if(str[0]!='\n'){
        k=kurzus_ptr_keres(kurzus_p,str);
        while(k==NULL||k->kurzus_kod[0]!='G'){
            printf("Hiba! A megadott kurzus nem talalhato az adatbazisban!\n");
            beolvas(str,10);
            k=kurzus_ptr_keres(kurzus_p,str);
        }
        k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_p);
        k->letszam+=1;
        hallgato_p->gyakorlat->hallgatok=hallgato_lista_torles(hallgato_p->gyakorlat->hallgatok, hallgato_p);
        hallgato_p->gyakorlat->letszam-=1;
        hallgato_p->gyakorlat=k;

    }
    printf("Eloadas kod: %s\n",h->eloadas->kurzus_kod);
    beolvas(str,10);
    if(str[0]!='\n'){
        k=kurzus_ptr_keres(kurzus_p,str);
        while(k==NULL||k->kurzus_kod[0]!='E'){
            printf("Hiba! A megadott kurzus nem talalhato az adatbazisban!\n");
            beolvas(str,10);
            k=kurzus_ptr_keres(kurzus_p,str);
        }
        k->hallgatok=hallgato_lista_beszur(k->hallgatok,hallgato_p);
        k->letszam+=1;
        hallgato_p->eloadas->hallgatok=hallgato_lista_torles(hallgato_p->eloadas->hallgatok, hallgato_p);
        hallgato_p->eloadas->letszam-=1;
        hallgato_p->eloadas=k;

    }
    printf("Labor jelenlet: %s\n",h->jelenlet_labor);
    beolvas(str,16);
    if(str[0]!='\n')
        strcpy(h->jelenlet_labor,str);
    printf("Gyakorlat jelenlet: %s\n",h->jelenlet_gyakorlat);
    beolvas(str,16);
    if(str[0]!='\n')
        strcpy(h->jelenlet_gyakorlat,str);
    for(int i=0; i<6; i+=1){
        printf("%d. kis ZH: %d\n",i+1,h->kisZH[i]);
        beolvas(str,4);
        if(str[0]!='\n')
            h->kisZH[i]=atoi(str);
    }
    printf("1. nagy ZH: %d\n",h->ZH1);
    beolvas(str,4);
    if(str[0]!='\n')
        h->ZH1=atoi(str);
    printf("2. nagy ZH: %d\n",h->ZH2);
    beolvas(str,4);
    if(str[0]!='\n')
        h->ZH2=atoi(str);
    printf("IMSC pont: %d\n",h->IMSC);
    beolvas(str,4);
    if(str[0]!='\n')
        h->IMSC=atoi(str);
    printf("NHF pont: %d\n",h->NHF);
    beolvas(str,4);
    if(str[0]!='\n')
        h->NHF=atoi(str);
    printf("Szorgalmi pont: %d\n",h->szorgalmi);
    beolvas(str,4);
    if(str[0]!='\n')
        h->szorgalmi=atoi(str);
}

void felszabadit_hallgato(hallgato *hallgato_ptr){
    hallgato *h=hallgato_ptr;
    while(h!=NULL){
        hallgato *kov_h=h->kov;
        free(h);
        h=kov_h;
    }
}

void mentes_hallgato(hallgato *hallgato_ptr){
    FILE *fp=NULL;
    fp=fopen("hallgatok.csv","w");
    if(fp==NULL){
        printf("Nem sikerult megnyitni a fajlt.\n");
        return;
    }
    hallgato *hallgato_p=hallgato_ptr;
    while(hallgato_p!=NULL){
        fprintf(fp,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"",hallgato_p->nev, hallgato_p->neptun, hallgato_p->labor->kurzus_kod, hallgato_p->gyakorlat->kurzus_kod, hallgato_p->eloadas->kurzus_kod, hallgato_p->jelenlet_gyakorlat, hallgato_p->jelenlet_labor);
        for(int j=0; j<6; j+=1){
            fprintf(fp,",\"%d\"",hallgato_p->kisZH[j]);
        }
        fprintf(fp,",\"%d\",\"%d\",\"%d\",\"%d\",\"%d\"\n", hallgato_p->ZH1, hallgato_p->ZH2, hallgato_p->NHF, hallgato_p->IMSC, hallgato_p->szorgalmi);
        hallgato_p=hallgato_p->kov;
    }
    fclose(fp);
}
