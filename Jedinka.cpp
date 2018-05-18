//
// Created by filip on 11.05.18..
//

#include <iostream>
#include <random>
#include <functional>
#include <vector>
#include "Jedinka.h"
#include "dobrota.h"
#include "Pomocni.h"

namespace GA {

    Jedinka::Jedinka()
    {
        //TODO Isprobati Grayev kod

        for (int i = 0; i<BROJ_BITOVA; i++) {
            auto rand_broj = Rand<int>(0, 1);
            x.push_back(rand_broj);
        }

        postaviXDec_dobrotu();
    }

    Jedinka::Jedinka(Jedinka& roditelj1, Jedinka& roditelj2)
    {
        std::vector<int> rod1 = roditelj1.getX();
        std::vector<int> rod2 = roditelj2.getX();
        for (int i = 0; i<BROJ_BITOVA; ++i) {
            if (rod1[i]==rod2[i]) {
                this->x.push_back(rod1[i]);
            } else {
                // 0 -> prvi roditelj ; 1 -> drugi roditelj
                auto rand_broj = Rand<int>(0, 1);
                rand_broj ? x.push_back(rod2[i]) : x.push_back(rod1[i]);
            }
        }

        postaviXDec_dobrotu();
    }

    void Jedinka::mutiraj()
    {
        for (auto& it : x) {
            if (Rand<double>(0, 1)<VJEROJATNONST_MUTACIJE) {
                it = it==0 ? 1 : 0;
            }
        }

        postaviXDec_dobrotu();
    }

    void Jedinka::postaviXDec_dobrotu()
    {
        x_dec = binarniUDecimalni(x);
        dobrota_jedinke = static_cast<int>(dobrota(x_dec));
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
        os << "X: ";
        os.width(4);
        os << jed.x_dec;
        os << "\tBinarno: ";
        for (auto bin : jed.getX()) {
            os << bin;
        }
        os << " Dobrota: ";
        os.width(3);
        os << jed.dobrota_jedinke;

        return os;
    }

}