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

void fomenu_megjelenit(){
    printf("Udvozli a Prog1 nyilvantartas a fomenuben!\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cUj oktato felvetele\n",' ');
    printf("2)%3cUj kurzus felvetele\n",' ');
    printf("3)%3cUj hallgato felvetele\n",' ');
    printf("4)%3cJelenlet, ertekeles rogzitese\n",' ');
    printf("5)%3cKereses\n",' ');
    printf("6)%3cPotlasra szorulok listaja\n",' ');
    printf("7)%3cEredmenyek\n",' ');
    printf("8)%3cRanglista\n",' ');
    printf("9)%3cStatisztika\n",' ');
    printf("10)%2cModositas\n",' ');
    printf("x)%3cKilepes\n",' ');
}

void beolvas(char *str, int karakter_db){
    fgets(str,karakter_db,stdin);
    if(str[0]=='\n')
        return;
    int id=0;
    while(str[id]!='\n'){
        id++;
    }
    str[id]='\0';
}

bool ervenyes(char *kod, int lehetosegdb){
    if(lehetosegdb==11){
        if(strcmp(kod,"x")==0)
            return true;
        for(int i=1;i<lehetosegdb; i+=1){
            char str[200];
            sprintf(str,"%d",i);
            if (strcmp(kod,str)==0)
                return true;
        }
        return false;
    }
    for(int i=1;i<lehetosegdb+1; i+=1){
        char str[200];
        sprintf(str,"%d",i);
        if (strcmp(kod,str)==0)
            return true;
    }
    return false;
}

bool uj_inditas(char *szoveg){
    system("cls");
    printf("Valasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3c%s\n",' ',szoveg);
    printf("2)%3cVissza a fomenube\n",' ');
    char ujkod[200];
    beolvas(ujkod,200);
    while(!ervenyes(ujkod,2)){
        printf("Hiba! A fent megadott kodok kozul valasszon!\n");
        beolvas(ujkod,200);
        }
   return ujkod[0]=='1';
}

void modositas(kurzus *kurzus_ptr, hallgato *hallgato_ptr, tanar *tanar_ptr){
    bool uj=true;
    system("cls");
    printf("Modositas\nValasszon a kod beirasaval az alabbi lehetosegek kozul:\n");
    printf("1)%3cOktato\n",' ');
    printf("2)%3cKurzus\n",' ');
    printf("3)%3cHallgato\n",' ');
    char kod[200];
    beolvas(kod,200);
    while(!ervenyes(kod,3)){
        printf("Hiba! A fent megadott kodok kozul valasszon!\n");
        beolvas(kod,200);
    }
    switch(kod[0]){
        case '1':while(uj){
                    oktato_modosit(tanar_ptr);
                    uj=uj_inditas("Oktato modositas");
                }
                break;
        case '2':while(uj){
                    kurzus_modosit(kurzus_ptr,tanar_ptr);
                    uj=uj_inditas("Kurzus modositas");
                }
                break;
        default:while(uj){
                    hallgato_modosit(hallgato_ptr,kurzus_ptr);
                    uj=uj_inditas("Hallgato modositas");
                }
                break;
    }
}
