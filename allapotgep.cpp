/**
 * \file allapotgep.cpp
 *
 * Ebben a fájlban kell megvalósítania az Allapotgep osztály
 * metódusait, valamint mindazon további osztályokat, melyek szükségesek
 * a feladat megvalósításához.
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#include <iostream>
#include <fstream>
#include <string.h>

#include "allapotgep.h"
#include "memtrace.h"

    /**
     * Konfig fájl beolvasása. Ha a fájl nem létezik/nem lehet megnyitni eldobja a NEPTUN-kódot.
     * Újra felépíti az állapotgépet, a korábbit törli ha volt. Kezdő állapotba áll.
     * @param  fajlnév - fájl neve
     * @return -
     * @exception fájl megnyitási hiba esetén NEPTUN_KÓD
    */
void Allapotgep::konfigural(const char* fajlnev){
    if(matrix != nullptr){
        delete[] allapotok;
        for (int i = 0; i < allapotok_szama; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    alaphelyzet();
    std::ifstream f(fajlnev);
    if (!f.is_open()) {
        throw "XJUTSU";
    }
    f >> allapotok_szama;
    char c;
    char nev[21];
    allapotok = new Allapot[allapotok_szama];
    for (int i = 0; i < allapotok_szama; i++) {
        f >> c >> nev;
        if (c == 'I') {
            allapotok[i].elfogado = true;
        } 
        else {
            allapotok[i].elfogado = false;
        }
        strcpy(allapotok[i].allapot_neve, nev);
    }
    matrix = new String* [allapotok_szama];
    for (int i = 0; i < allapotok_szama; i++) {
        matrix[i] = new String [allapotok_szama];
    }

    for (int i = 0; i < allapotok_szama; i++) {
        for (int j = 0; j < allapotok_szama; j++) {
            f >> matrix[i][j];
        }
    }
}

    /** Visszaadja melyik állapot aktív.
     * @return pointer az aktív állapot nevére
     */
const char* Allapotgep::aktualisallapot(){
    return allapotok[aktualis_allapot].allapot_neve;
}

    /**
     * Elfogadó állapotban van-e az állapotgép.
     * @return true, ha elfogadó állapotban van
     */
bool Allapotgep::elfogad(){
    return  allapotok[aktualis_allapot].elfogado;
}

    /**
     * Az aktuális állapotnak és inputnak megfelelő következő állapotba léptet.
     * @param b - beérkező bázis, mint input
     */


void Allapotgep::atmenet(Bazis b){
    for (int i = 0; i < allapotok_szama; i++){
        for (int j = 0; matrix[aktualis_allapot][i][j] != '\0'; j++){
            if (matrix[aktualis_allapot][i][j] == cast(b)){
                aktualis_allapot = i;
                break;
            }
        }
    }
}


    /**
     * Feldolgozza a paraméterként kapott bázissorozatot.
     * Visszaadja, hogy elfogadó állapotba került-e. (Nem áll vissza kezdő állapotba.)
     * @param b - input sorozatra mutató pointer
     * @param n - a sorozat hossza
     * @return tru, ha elfogadó állapotba került
    */
bool Allapotgep::feldolgoz(const Bazis *b, int n){
    for (int i = 0; i < n; i++){
        atmenet(b[i]);
    }
    return allapotok[aktualis_allapot].elfogado;
}

    /**
     * Kezdő állapotba visz.
     */
void Allapotgep::alaphelyzet(){
    aktualis_allapot = 0;
}

Allapotgep::~Allapotgep(){
    if(matrix != nullptr){
    delete[] allapotok;
    
    for (int i = 0; i < allapotok_szama; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    }
}

std::istream& operator>> (std::istream& is, String& str){
    is >> str.str;
    return is;
}