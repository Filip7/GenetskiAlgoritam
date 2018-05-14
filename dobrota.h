//
// Created by filip on 11.05.18..
//

#ifndef GENETSKIALGORITAM_DOBROTA_H
#define GENETSKIALGORITAM_DOBROTA_H

#include <vector>
#include <cmath>

constexpr int BROJ_BITOVA = 10;
constexpr double VJEROJATNONST_MUTACIJE = 0.01;

int binarniUDecimalni(std::vector<int> jedinka)
{
    int dec = 0;
    int j = 0;
    for (int i = BROJ_BITOVA-1; i>=0; --i) {
        dec += (std::pow(2, j) * jedinka[i]);
        ++j;
    }

    return dec;
}

double dobrota(int jedinka)
{
    // Funkcija računa dobrotu jedinke (int jedinka) prema funkciji prikaznoj u tekstu zadatka
    // Dozvoljene ulazne vrijednosti su u otvorenom intervalu [0, 1023]
    // Funkcija vraća -1 ako je zadana nedozvoljena vrijednost

    if (jedinka<0 || jedinka>=1024) {
        return -1;
    }

    if (jedinka>=0 && jedinka<30) {
        return 60.0;
    } else if (jedinka>=30 && jedinka<90) {
        return (double) jedinka+30.0;
    } else if (jedinka>=90 && jedinka<120) {
        return 120.0;
    } else if (jedinka>=120 && jedinka<210) {
        return -0.83333*(double) jedinka+220;
    } else if (jedinka>=210 && jedinka<270) {
        return 1.75*(double) jedinka-322.5;
    } else if (jedinka>=270 && jedinka<300) {
        return 150.0;
    } else if (jedinka>=300 && jedinka<360) {
        return 2.0*(double) jedinka-450;
    } else if (jedinka>=360 && jedinka<510) {
        return -1.8*(double) jedinka+918;
    } else if (jedinka>=510 && jedinka<630) {
        return 1.5*(double) jedinka-765;
    } else if (jedinka>=630 && jedinka<720) {
        return -1.33333*(double) jedinka+1020;
    } else if (jedinka>=720 && jedinka<750) {
        return 60.0;
    } else if (jedinka>=750 && jedinka<870) {
        return 1.5*(double) jedinka-1065;
    } else if (jedinka>=870 && jedinka<960) {
        return -2.66667*(double) jedinka+2560;
    } else {
        return 0;
    }
}

#endif //GENETSKIALGORITAM_DOBROTA_H
