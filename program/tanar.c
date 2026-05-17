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

tanar *tanar_beszur(tanar *tanar_p, tanar *adat){
    tanar *uj=(tanar*)malloc(sizeof(tanar));
    uj->kov=tanar_p;
    strcpy(uj->nev,adat->nev);
    strcpy(uj->elerhetoseg,adat->elerhetoseg);
    uj->kurzus_db=adat->kurzus_db;
    uj->kurzusok=adat->kurzusok;
    return uj;
}

tanar *tanar_beolvas(tanar *tanar_p, int *tanar_db){
    FILE* fp=fopen("oktatok.csv","r");
    if(fp==NULL){
        printf("Nem lehet megnyitni a vezerfajlt.\n");
        return NULL;
    }
    tanar t;
    char sor[330];
    while (fgets(sor, 330, fp)!=NULL) {
        char c;
        sscanf(sor,"%c",&c);
        char *str = strtok(sor, "\",\"");
        strcpy(t.nev,str);
        str=strtok(NULL, "\",\"");
        strcpy(t.elerhetoseg,str);
        str=strtok(NULL, "\",\"");
        t.kurzus_db=atoi(str);
        t.kurzusok=NULL;
        *tanar_db+=1;
        tanar_p=tanar_beszur(tanar_p,&t);


    }
    fclose(fp);
    return tanar_p;

}

void oktato_modosit(tanar *tanar_p){
    char str[40];
    printf("Modositani kivant oktato neve: ");
    beolvas(str,40);
    tanar *t=tanar_ptr_keres(tanar_p,str);
    while(t==NULL){
        printf("Hiba! A megadott oktato nem talalhato az adatbazisban!\n");
        beolvas(str,40);
        t=tanar_ptr_keres(tanar_p,str);
    }
    system("cls");
    printf("Nev: %s\n",t->nev);
    beolvas(str,40);
    if(str[0]!='\n')
        strcpy(t->nev,str);
    printf("Elerhetoseg: %s\n",t->elerhetoseg);
    beolvas(str,40);
    if(str[0]!='\n')
        strcpy(t->elerhetoseg,str);
}

tanar *tanar_listaz_beolvas(tanar *tanar_p){
    tanar *t;
    t=tanar_p;
    printf("Oktatok:\n");
    while(t!=NULL){
        printf("Nev: %-*s Kurzusainak szama: %-*d\n", 50, t->nev, 5, t->kurzus_db);
        t=t->kov;
    }
    char nev[42];
    printf("Valasztott oktato neve: ");
    beolvas(nev,42);

    t=tanar_ptr_keres(tanar_p,nev);
    while(t==NULL){
        printf("Hiba! A fent megadott oktatok kozul valasszon!\n");
        beolvas(nev,42);
        t=tanar_ptr_keres(tanar_p,nev);
    }
    return t;
}

tanar *oktato_felv(tanar *tanar_ptr, int *tanar_db){
    system("cls");
    printf("Uj oktato felvetele\n");
    tanar t;
    printf("Oktato neve: ");
    beolvas(t.nev,42);
    printf("Oktato elerhetosege (e-mail cim): ");
    scanf("%s",t.elerhetoseg);
    getchar();
    t.kurzus_db=0;
    t.kurzusok=NULL;
    tanar_ptr=tanar_beszur(tanar_ptr,&t);
    *tanar_db+=1;
    return tanar_ptr;
}

void felszabadit_tanar(tanar *tanar_ptr){
    tanar *t=tanar_ptr;
    while(t!=NULL){
        kurzus_lista *k=t->kurzusok;
        while(k!=NULL){
            kurzus_lista *kov_k=k->kov;
            free(k);
            k=kov_k;
        }
        tanar *kov_t=t->kov;
        free(t);
        t=kov_t;
    }
}

void mentes_tanar(tanar *tanar_ptr){
    FILE* fp=NULL;
    fp=fopen("oktatok.csv","w");
    if(fp==NULL){
        printf("Nem sikerult megnyitni a fajlt.\n");
        return;
    }
    tanar *tanar_p=tanar_ptr;
    while(tanar_p!=NULL){
        fprintf(fp,"\"%s\",\"%s\",\"%d\"",tanar_p->nev, tanar_p->elerhetoseg, tanar_p->kurzus_db);
        kurzus_lista *k=NULL;
        k=tanar_p->kurzusok;
        while(k!=NULL){
            fprintf(fp,",\"%s\"",k->kurzus_p->kurzus_kod);
            k=k->kov;
        }
        fprintf(fp,"\n");
        tanar_p=tanar_p->kov;
    }
    fclose(fp);
}
