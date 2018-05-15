//
// Created by filip on 14.05.18..
//

#ifndef GENETSKIALGORITAM_POMOCNI_H
#define GENETSKIALGORITAM_POMOCNI_H

#include <iostream>
#include <random>

namespace GA{
    /**
     * Predlozak funkcije za racunanje radnom broja, ovisno o tipu podataka i granicama racuna vrijednost.
     * Dio koji je ne koristi se ne compile-ira
     * @tparam Tip double ili int
     * @param broj1 granica od (ukljucivo)
     * @param broj2 granica do (ukljucivo)
     * @return random generirani broj izmedu @param broj1 i @param broj2
     */
    template <typename Tip>
    Tip Rand(int broj1, int broj2){
        std::random_device rd;
        std::mt19937 mt(rd());
        if constexpr (std::is_same_v<Tip, int>){
            std::uniform_int_distribution<Tip> distribucija_tip(broj1, broj2);
            return distribucija_tip(mt);
        }
        else if constexpr (std::is_same_v<Tip, double>){
            std::uniform_real_distribution<double> distribucija_tip(broj1, broj2);
            return distribucija_tip(mt);
        }
    }

}

#endif //GENETSKIALGORITAM_POMOCNI_H
