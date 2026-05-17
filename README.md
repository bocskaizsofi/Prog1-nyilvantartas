Prog1 Nyilvántartás
A program célja a Programozás alapjai 1 tárgyhoz tartozó hallgatók, kurzusok és oktatók adatainak kezelése.

A rendszer képes:
- hallgatók, oktatók és kurzusok felvételére,
- jelenlét, ZH‑k, NHF, szorgalmi és IMSC pontok rögzítésére,
- keresésre (hallgató, kurzus, oktató),
- pótlásra szorulók listázására,
- eredmények és ranglista megjelenítésére,
- statisztikák készítésére,
- adatok mentésére és betöltésére CSV fájlokból.

A program kilépéskor automatikusan elmenti az adatokat, indításkor pedig betölti a következő fájlokból:
- hallgatok.csv
- kurzusok.csv
- oktatok.csv

Fordítás:
A program/ mappában kell terminált nyitni: gcc *.c -o nyilvantartas
Ez minden .c fájlt lefordít és összelinkel.

Futtatás:
Windows alatt: ./nyilvantartas.exe

A projekt főbb fájljai:
A projekt program mappájában találhatók a futáshoz szükséges fájlok:
- main.c – a program belépési pontja
- tanar.c / tanar.h – oktatók kezelése
- kurzus.c / kurzus.h – kurzusok kezelése
- hallgato.c / hallgato.h – hallgatók kezelése
- jelenlet_ertekeles.c / jelenlet_ertekeles.h – jelenlét és pontok rögzítése
- kereses.c / kereses.h – keresési funkciók
- jegy_szamol.c / jegy_szamol.h – pontszámítás, jegyek
- visszajelzo.c / visszajelzo.h – üzenetek, hibakezelés
- seged.c / seged.h – segédfüggvények
- tipusok.h – struktúrák, típusdefiníciók
- debugmalloc.h - a memóriaszivárgás vizsgálata
- CSV fájlok – adatok tárolása
A projekt dokumentacio mappájában található a részletes felhasználói és programozói dokumentáció.

Használat:
A program indítás után betölti a CSV fájlokat.
Ezután megjelenik a főmenü:
Udvozli a Prog1 nyilvantartas a fomenuben!
Valasszon a kod beirasaval az alabbi lehetosegek kozul:
1) Uj oktato felvetele
2) Uj kurzus felvetele
3) Uj hallgato felvetele
4) Jelenlet, ertekeles rogzitese
5) Kereses
6) Potlasra szorulok listaja
7) Eredmenyek
8) Ranglista
9) Statisztika
10) Modositas
x) Kilepes
A felhasználó minden adat megadása után Entert nyom.
Hibás adat esetén a program figyelmeztet és új adatot kér.

Mentés:
Kilépéskor a program elmenti az adatokat a három CSV fájlba.

Követelmények:
GCC fordító (MinGW ajánlott Windows alatt)
Terminál/PowerShell futtatási lehetőség
