//
// Created by filip on 11.05.18..
//

#include <iostream>
#include <random>
#include <functional>
#include <vector>
#include "Jedinka.h"
#include "dobrota.h"

namespace GA {

    Jedinka::Jedinka()
    {
        //TODO Isprobati Grayev kod
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribucija_jedinke(0, 1);

        for (int i = 0; i<BROJ_BITOVA; i++) {
            int rand_broj = distribucija_jedinke(mt);
            x.push_back(rand_broj);
        }
        x_dec = binarniUDecimalni(x);

        dobrota_jedinke = static_cast<int>(dobrota(x_dec));
    }

    Jedinka::Jedinka(Jedinka& roditelj1, Jedinka& roditelj2)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> vjerojatnost_nasljedivanja(0, 1);

        std::vector<int> rod1 = roditelj1.getX();
        std::vector<int> rod2 = roditelj2.getX();
        for (int i = 0; i<BROJ_BITOVA; ++i) {
            if (rod1[i]==rod2[i]) {
                this->x.push_back(rod1[i]);
            } else {
                // 0 -> prvi roditelj ; 1 -> drugi roditelj
                int rand_broj = vjerojatnost_nasljedivanja(mt);
                rand_broj ? x.push_back(rod2[i]) : x.push_back(rod1[i]);
            }
        }

        x_dec = binarniUDecimalni(this->x);
        dobrota_jedinke = static_cast<int>(dobrota(x_dec));
    }

    void Jedinka::mutiraj()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> vjerojatnost_mutacije(0, 1);

        for (auto& it : x) {
            if (vjerojatnost_mutacije(mt)<VJEROJATNONST_MUTACIJE) {
                it = it==0 ? 1 : 0;
            }
        }
        x_dec = binarniUDecimalni(x);
        dobrota_jedinke = static_cast<int>(dobrota(x_dec));
    }

    void Jedinka::ispisi(bool ispisi_bin)
    {
        std::cout << "X: ";
        std::cout.width(4);
        std::cout << x_dec;
        if (ispisi_bin) {
            std::cout << "\tBinarno: ";
            for (auto bin : x) {
                std::cout << bin;
            }
        }
        std::cout << "\tDobrota: ";
        std::cout.width(3);
        std::cout << dobrota_jedinke;
        std::cout << std::endl;
    }

    int Jedinka::getDobrota_jedinke() const
    {
        return dobrota_jedinke;
    }

    const std::vector<int>& Jedinka::getX() const
    {
        return x;
    }

    int Jedinka::getNormalizirana_dobrota_jedinke() const
    {
        return normalizirana_dobrota_jedinke;
    }

    void Jedinka::setNormalizirana_dobrota_jedinke(int normalizirana_dobrota_jedinke)
    {
        Jedinka::normalizirana_dobrota_jedinke = normalizirana_dobrota_jedinke;
    }

    int Jedinka::getX_dec() const
    {
        return x_dec;
    }

    bool operator==(const Jedinka& lijevi, const Jedinka& desni)
    {
        if (&lijevi==&desni)
            return true;
        return lijevi.x_dec==desni.x_dec;
    }

    bool operator!=(const Jedinka& lijevi, const Jedinka& desni)
    {
        return !(lijevi==desni);
    }

    std::ostream& operator<<(std::ostream& os, const Jedinka& jed)
    {
        return os << "X: " << jed.x_dec << " Dobrota: " << jed.dobrota_jedinke;
    }

}