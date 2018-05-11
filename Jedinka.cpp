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
    bool Jedinka::isElitna() const {
        return elitna;
    }

    void Jedinka::setElitna(bool elitna) {
        Jedinka::elitna = elitna;
    }

    Jedinka::Jedinka() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> distribucija_jedinke(0, 1);

        for (int i = 0; i < BROJ_BITOVA; i++){
            int rand_broj = distribucija_jedinke(mt);
            x.push_back(rand_broj);
        }
        x_dec = binarniUDecimalni(x);

        dobrota_jedinke = static_cast<int>(dobrota(x_dec));
    }

    void Jedinka::ispisi(bool ispisi_bin) {
        std::cout << "X: ";
        std::cout.width(4);
        std::cout<< x_dec;
        if(ispisi_bin){
            std::cout << "\tBinarno: ";
            for(auto bin : x){
                std::cout << bin;
            }
        }
        std::cout << "\tDobrota: ";
        std::cout.width(3);
        std::cout << dobrota_jedinke;
        std::cout << std::endl;
    }

    int Jedinka::getDobrota_jedinke() const {
        return dobrota_jedinke;
    }

    std::ostream &operator<<(std::ostream &os, const Jedinka &jed) {
        return os << "X: " << jed.x_dec << " Dobrota: " << jed.dobrota_jedinke;
    }
}