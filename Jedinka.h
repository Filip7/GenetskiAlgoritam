//
// Created by filip on 11.05.18..
//

#ifndef GENETSKIALGORITAM_JEDINKA_H
#define GENETSKIALGORITAM_JEDINKA_H

#include <vector>

namespace GA {

    class Jedinka {
        friend std::ostream& operator<<(std::ostream& os, const Jedinka& jed);
    private:
        int dobrota_jedinke;
        bool elitna;
    public:
        int getDobrota_jedinke() const;

    public:
        std::vector<int> x;
        int x_dec;

        Jedinka();

        bool isElitna() const;

        void setElitna(bool elitna);

        void ispisi(bool ispisi_bin = false);
    };

}

#endif //GENETSKIALGORITAM_JEDINKA_H
