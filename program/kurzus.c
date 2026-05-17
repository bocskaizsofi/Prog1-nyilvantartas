#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tanar.h"
#include "kurzus.h"
#include "hallgato.h"
#include "debugmalloc.h"
//#include "jegy_szamol.h"
//#include "jelenlet_ertekeles.h"
#include "kereses.h"
#include "seged.h"

kurzus *kurzus_beszur(kurzus *kurzus_p, kurzus *adat){
    kurzus *uj=(kurzus*)malloc(sizeof(kurzus));
    uj->kov=kurzus_p;
    strcpy(uj->kurzus_kod,adat->kurzus_kod);
    strcpy(uj->idopont,adat->idopont);
    strcpy(uj->helyszin,adat->helyszin);
    uj->oktato=adat->oktato;
    uj->hallgatok = adat->hallgatok;
    uj->letszam=adat->letszam;
    return uj;
}

kurzus_lista *kurzus_lista_beszur(kurzus_lista *eleje, kurzus *beszurt){
    kurzus_lista *uj=(kurzus_lista*)malloc(sizeof(kurzus_lista));
    uj->kov=eleje;
    uj->kurzus_p=beszurt;
    return uj;
}

kurzus_lista *kurzus_lista_torles(kurzus_lista *eleje, kurzus *torolt){
    kurzus_lista *lemarado = NULL;
    kurzus_lista *k = eleje;
    while (k != NULL && k->kurzus_p!=torolt) {
        k = k;
        k = k->kov;
    }
    if (lemarado == NULL) {
        eleje = k->kov;
        free(k);
    }
    else {
        lemarado->kov = k->kov;
        free(k);
    }
    return eleje;
}

kurzus *kurzus_beolvas(kurzus *kurzus_p, kurzusok_db *kurzus_db, tanar *tanar_ptr){
    FILE *fp=fopen("kurzusok.csv","r");
    if(fp==NULL){
        printf("Nem lehet megnyitni a vezerfajlt.\n");
        return NULL;
    }
    kurzus k;
    char sor[100];
    while (fgets(sor, 100, fp)!=NULL) {
        char c;
        sscanf(sor,"%c",&c);
        char *str = strtok(sor, "\",\"");
        strcpy(k.kurzus_kod,str);
        str=strtok(NULL, "\",\"");
        strcpy(k.idopont,str);
        str=strtok(NULL, "\",\"");
        strcpy(k.helyszin,str);
        str=strtok(NULL, "\",\"");
        tanar *t=tanar_ptr;
        while(t!=NULL&&strcmp(t->nev,str)!=0){
            t=t->kov;
        }

        k.oktato = t;
        k.hallgatok=NULL;
        k.letszam=0;

        kurzus_p=kurzus_beszur(kurzus_p,&k);

        if(t!=NULL){
            t->kurzusok=kurzus_lista_beszur(t->kurzusok,kurzus_p);
        }
        switch(k.kurzus_kod[0]){
            case 'L':kurzus_db->labor_db+=1;
                    break;
            case 'G':kurzus_db->gyakorlat_db+=1;
                    break;
            default:kurzus_db->eloadas_db+=1;
                    break;
        }
    }
    fclose(fp);
    return kurzus_p;
}

void kurzus_modosit(kurzus *kurzus_p, tanar *tanar_p){
    char str[40];
    printf("Modositani kivant kurzus kodja: ");
    beolvas(str,10);
    kurzus *k=kurzus_ptr_keres(kurzus_p,str);
    while(k==NULL){
        printf("Hiba! A megadott kurzus nem talalhato az adatbazisban!\n");
        beolvas(str,10);
        k=kurzus_ptr_keres(kurzus_p,str);
    }
    system("cls");
    printf("Kurzus kod: %s\n",k->kurzus_kod);
    beolvas(str,10);
    if(str[0]!='\n')
        strcpy(k->kurzus_kod,str);
    printf("Idopont: %s\n",k->idopont);
    beolvas(str,10);
    if(str[0]!='\n')
        strcpy(k->kurzus_kod,str);
    printf("Helyszin: %s\n",k->helyszin);
    beolvas(str,10);
    if(str[0]!='\n')
        strcpy(k->helyszin,str);
    printf("Oktato: %s\n",k->oktato->nev);
    beolvas(str,10);
    if(str[0]!='\n'){
        tanar *t=tanar_ptr_keres(tanar_p,str);
        if(t==NULL){
            printf("\n");
            t=tanar_listaz_beolvas(tanar_p);
        }
        t->kurzusok=kurzus_lista_beszur(t->kurzusok,kurzus_p);
        t->kurzus_db+=1;
        k->oktato->kurzusok=kurzus_lista_torles(k->oktato->kurzusok,k);
        k->oktato->kurzus_db-=1;
        k->oktato = t;
    }
}

kurzus *kurzus_felv(kurzus *kurzus_ptr, kurzusok_db *kurzus_db, tanar *tanar_ptr){
    system("cls");
    printf("Uj kurzus felvetele\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cEloadas\n",' ');
    printf("2)%3cGyakorlat\n",' ');
    printf("3)%3cLabor\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,3)){
        printf("Hiba! A fent megadott kodok kozul valasszon!\n");
        beolvas(kod,200);
    }
    kurzus k;
    char temp[10]="";
    switch(kod[0]){
        case '1':kurzus_db->eloadas_db+=1;
                sprintf(temp,"E%d",kurzus_db->eloadas_db);
                break;
        case '2':kurzus_db->gyakorlat_db+=1;
                sprintf(temp,"G%d",kurzus_db->gyakorlat_db);
                break;
        default:kurzus_db->labor_db+=1;
                sprintf(temp,"L%d",kurzus_db->labor_db);
                break;
    }
    strcpy(k.kurzus_kod,temp);
    tanar *t=tanar_listaz_beolvas(tanar_ptr);

    printf("Idopont: ");
    beolvas(k.idopont,10);
    printf("Helyszin: ");
    scanf("%s",k.helyszin);
    getchar();
    k.hallgatok=NULL;
    k.oktato = t;
    k.letszam=0;
    kurzus_ptr=kurzus_beszur(kurzus_ptr,&k);
    t->kurzusok=kurzus_lista_beszur(t->kurzusok,kurzus_ptr);
    t->kurzus_db+=1;
    return kurzus_ptr;
}

void felszabadit_kurzus(kurzus *kurzus_ptr){
    kurzus *k=kurzus_ptr;
    while(k!=NULL){
        hallgato_lista *h=k->hallgatok;
        while(h!=NULL){
            hallgato_lista *kov_h=h->kov;
            free(h);
            h=kov_h;
        }
        kurzus *kov_k=k->kov;
        free(k);
        k=kov_k;
    }
}

void mentes_kurzus(kurzus *kurzus_ptr){
    FILE *fp=NULL;
    fp=fopen("kurzusok.csv","w");
    if(fp==NULL){
        printf("Nem sikerult megnyitni a fajlt.\n");
        return;
    }
    kurzus *kurzus_p=kurzus_ptr;
    while(kurzus_p!=NULL){
        fprintf(fp,"\"%s\",\"%s\",\"%s\",\"%s\"\n",kurzus_p->kurzus_kod, kurzus_p->idopont, kurzus_p->helyszin, kurzus_p->oktato->nev);

        kurzus_p=kurzus_p->kov;
    }
    fclose(fp);
}
