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

int main()
{
    int tanar_db=0;
    int hallgato_db=0;
    kurzusok_db kurzus_db;
    kurzus_db.eloadas_db=0;
    kurzus_db.gyakorlat_db=0;
    kurzus_db.labor_db=0;

    tanar *tanar_ptr=NULL;
    kurzus *kurzus_ptr=NULL;
    hallgato *hallgato_ptr=NULL;

    tanar_ptr=tanar_beolvas(tanar_ptr,&tanar_db);
    kurzus_ptr=kurzus_beolvas(kurzus_ptr, &kurzus_db, tanar_ptr);
    hallgato_ptr=hallgato_beolvas(hallgato_ptr,&hallgato_db,kurzus_ptr);

    bool uj=true;
    fomenu_megjelenit();
    char kod[200];
    beolvas(kod,200);
    while(strcmp(kod,"x")!=0){
        while(!ervenyes(kod,11)){
            printf("Hiba! A fent megadott kodok kozul valasszon!\n");
            beolvas(kod,200);
        }
        if(strcmp(kod,"x")==0)
            break;
        switch(kod[0]){
            case '1':if(kod[1]=='0'){
                        modositas(kurzus_ptr, hallgato_ptr, tanar_ptr);
                        break;
                    }
                    else{
                        uj=true;
                        while(uj){
                            tanar_ptr=oktato_felv(tanar_ptr,&tanar_db);
                            uj=uj_inditas("Uj oktato felvetele");
                        }
                        break;
                    }
            case '2':   uj=true;
                        while(uj){
                            kurzus_ptr=kurzus_felv(kurzus_ptr,&kurzus_db,tanar_ptr);
                            uj=uj_inditas("Uj kurzus felvetele");
                        }
                        break;
            case '3':uj=true;
                    while(uj){
                        hallgato_ptr=hallgato_felv(hallgato_ptr,&hallgato_db,kurzus_ptr);
                        uj=uj_inditas("Uj hallgato felvetele");
                    }
                    break;
            case '4':jelenlet_ertekeles(kurzus_ptr, hallgato_ptr);
                    break;
            case '5':kereses(kurzus_ptr, hallgato_ptr, tanar_ptr);
                    break;
            case '6':uj=true;
                    while(uj){
                        potlas(hallgato_ptr);
                        uj=uj_inditas("Potlasra szorulok listaja");
                    }
                    break;
            case '7':uj=true;
                    while(uj){
                        eredmeny(hallgato_ptr);
                        uj=uj_inditas("Eredmenyek");
                    }
                    break;
            case '8':uj=true;
                    while(uj){
                        ranglista(hallgato_ptr,hallgato_db);
                        uj=uj_inditas("Ranglista");
                    }
                    break;
            default:uj=true;
                    while(uj){
                        statisztika(hallgato_ptr, hallgato_db);
                        uj=uj_inditas("Statisztika");
                    }
                    break;
        }
        system("cls");
        fomenu_megjelenit();
        beolvas(kod,200);
    }

    mentes_tanar(tanar_ptr);
    mentes_kurzus(kurzus_ptr);
    mentes_hallgato(hallgato_ptr);
    printf("Sikeres mentes.\n");

    felszabadit_tanar(tanar_ptr);
    felszabadit_hallgato(hallgato_ptr);
    felszabadit_kurzus(kurzus_ptr);

    return 0;
}
