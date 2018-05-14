//
// Created by filip on 11.05.18..
//

#ifndef GENETSKIALGORITAM_JEDINKA_H
#define GENETSKIALGORITAM_JEDINKA_H

#include <vector>

/**
 * GA - Genetski Algoritam
 * */
namespace GA {

    class Jedinka {
        friend std::ostream& operator<<(std::ostream& os, const Jedinka& jed);

        friend bool operator==(const Jedinka& lijevi, const Jedinka& desni);

        friend bool operator!=(const Jedinka& lijevi, const Jedinka& desni);

    private:
        std::vector<int> x;
        int dobrota_jedinke;
        int normalizirana_dobrota_jedinke;
        int x_dec;
        double vjerojatnostP;

    public:
        /**
         * Izraduje jedinku, nasumicno generira 10-bitni broj pomocu Mersenne Twister algoritma
         * koristi se samo tijekom prve inicijalizacije jedinke
         */
        Jedinka();

        /**
         * Izraduje novu jedinku iz dva roditelja, korisiti se prilikom razmnozavanja
         * @param roditelj1 prvi roditelj
         * @param roditelj2 drugi roditlej
         */
        Jedinka(Jedinka& roditelj1, Jedinka& roditelj2);

        const std::vector<int>& getX() const;

        int getDobrota_jedinke() const;

        int getNormalizirana_dobrota_jedinke() const;

        void setNormalizirana_dobrota_jedinke(int normalizirana_dobrota_jedinke);

        int getX_dec() const;

        /**
         * Odraduje mutiranje, koristi se u konstruktoru za izradu nove jedinke preko roditelja
         */
        void mutiraj();

        /**
         * Ispis parametara jedinke
         * @param ispisi_bin true ako se ispisuje binarni zapis X-a, odnosno false ako se ne ispisuje
         */
        void ispisi(bool ispisi_bin = false);
    };

}

#endif //GENETSKIALGORITAM_JEDINKA_H
