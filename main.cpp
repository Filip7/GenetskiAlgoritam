#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <random>
#include "Jedinka.h"

using namespace std;

constexpr int BROJ_ITERACIJA = 30;

constexpr int VELICINA_POPULACIJE = 20;
constexpr double VJEROJATNOST_KRIZANJA = 0.9;

bool usporedbaDobroteJedinki(GA::Jedinka *x, GA::Jedinka *y);
void ispis(vector<GA::Jedinka*> &jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka *max);
void zapisUDatoteku(fstream &dat, vector<GA::Jedinka*> &jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka *max);
vector<GA::Jedinka*> selektirajJedinke(vector<GA::Jedinka*> &jedinke, double ukupnaDobrota, GA::Jedinka *max);

void isprazniJedinke(vector<GA::Jedinka *> &jedinke);

int main() {
    string PUTANJA = "../genetskiAlgoritamRezultat.txt";
    vector<GA::Jedinka*> jedinke;

    /*Izrada prve populacije, sve jednike su nasumicno generirane*/
    for(int i = 0; i < VELICINA_POPULACIJE; ++i){
        jedinke.push_back(new GA::Jedinka);
    }

    sort(jedinke.begin(), jedinke.end(), usporedbaDobroteJedinki);

    fstream dat{PUTANJA, ios_base::out};
    if(!dat){
        dat.clear();
        dat.open(PUTANJA, ios_base::out);
    }

    for(int iter = 0; iter < BROJ_ITERACIJA; ++iter){
        double ukupnaDobrotaJedinki = 0;
        double prosjecnaDobrotaJedinki;
        cout << "Generacija: " << iter + 1 << endl;
        dat << "Generacija: " << iter + 1 << endl;

        for(auto &jedinka : jedinke){
            ukupnaDobrotaJedinki += jedinka->getDobrota_jedinke();
        }

        for(auto &jedinka : jedinke){
            auto normaliziranaDobrota = jedinka->getDobrota_jedinke() / ukupnaDobrotaJedinki * 100;
            jedinka->setNormalizirana_dobrota_jedinke(static_cast<int>(normaliziranaDobrota));
        }

        prosjecnaDobrotaJedinki = ukupnaDobrotaJedinki / jedinke.size();
        auto max = *std::max_element(begin(jedinke), end(jedinke), usporedbaDobroteJedinki);
        max->setElitna(true);

        ispis(jedinke, ukupnaDobrotaJedinki, prosjecnaDobrotaJedinki, max);
        zapisUDatoteku(dat, jedinke, ukupnaDobrotaJedinki, prosjecnaDobrotaJedinki, max);

        jedinke = selektirajJedinke(jedinke, ukupnaDobrotaJedinki, max);
        sort(jedinke.begin(), jedinke.end(), usporedbaDobroteJedinki);
    }

    dat.close();
    isprazniJedinke(jedinke);

	return 0;
}

/**
 * Obavlja selekciju jedinki, odabir roditelja te stvara novu populaciju
 * @param jedinke vector svih jedinki prethodne generacije
 * @param max maksimalna jedinka, koristi se za elitizam
 * @return vector nove generacije jedinki
 */
vector<GA::Jedinka*> selektirajJedinke(vector<GA::Jedinka*> &jedinke, GA::Jedinka *max){
    //TODO Optimizirati selekciju
    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> vjerojatnost_krizanja(0, 1);

    vector<unsigned int> pool;
    vector<GA::Jedinka*> nova_populacija;
    nova_populacija.push_back(max);
    max->setElitna(false);

    for(unsigned int i = 0; i < VELICINA_POPULACIJE; ++i){
        int n = jedinke[i]->getNormalizirana_dobrota_jedinke(); //Neki ispadaju 0 pa se ne unose po trenutacnoj implementaciji
        for(int j = 0; j < n; ++j){
            pool.push_back(i);
        }
    }

    auto broj_jedinki_u_poolu = static_cast<int>(pool.size());
    uniform_int_distribution<int> odabranik(0, broj_jedinki_u_poolu);
    while(nova_populacija.size() != VELICINA_POPULACIJE){
        bool kontrola = true;
        int rod1 = odabranik(mt);
        int rod2 = odabranik(mt);
        while(rod1 == rod2){
            rod2 = odabranik(mt);
        }

        if(vjerojatnost_krizanja(mt) < VJEROJATNOST_KRIZANJA){
            auto *dijete = new GA::Jedinka(*jedinke.at(pool[rod1]), *jedinke.at(pool[rod2]));
            dijete->mutiraj();
            for(auto &rod : nova_populacija){
                if(*dijete == *rod)
                    kontrola = false;
            }
            if(kontrola) {
                nova_populacija.push_back(dijete);
            }
        }
    }
    return nova_populacija;
}

/**
 * Brise vector jedinki
 * @param jedinke vector svih jedinki prethodne generacije
 */
void isprazniJedinke(vector<GA::Jedinka *> &jedinke) {
    for(int iter = VELICINA_POPULACIJE - 1; iter >= 0; --iter){
        delete jedinke[iter];
        jedinke.pop_back();
    }
}

/**
 * Usporeduje dobrote jedinki, koristi se za pronalazk max jedinke
 * @param x prva jedinka za usporedbu
 * @param y druga jedinka za usporedbu
 * @return veca jedinka izmedu x i y
 */
bool usporedbaDobroteJedinki(GA::Jedinka *x, GA::Jedinka *y) {
    return x->getDobrota_jedinke() < y->getDobrota_jedinke();
}

/**
 * Ispisuje jedinke na zaslon
 * @param jedinke vector svih jedinki generacije
 * @param jedinke vector svih jedinki generacije
 * @param ukupnaDobrota zbroj dobrota svih jedinki generacije
 * @param prosjecnaDobrotaJedinki prosjek dobrota generacije
 * @param max maksimalna jedinka, koristi se za elitizam
 */
void ispis(vector<GA::Jedinka*> &jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka *max){
    for(auto &jedinka : jedinke){
        jedinka->ispisi(true);
        //cout << *jedinka << endl;
    }

    cout << endl << "Max dobrota jedinke: " << max->getDobrota_jedinke() << endl;
    cout << "Prosjecna dobrota jedinki: " << prosjecnaDobrotaJedinki << endl;
    cout << "Ukupna dobrota jedinki: " << ukupnaDobrotaJedinki << endl << endl << endl;
}

/**
 * Ispisuje jedinke u datoteku
 * @param dat datoteka u koju se zapisuje
 * @param jedinke vector svih jedinki generacije
 * @param ukupnaDobrota zbroj dobrota svih jedinki generacije
 * @param prosjecnaDobrotaJedinki prosjek dobrota generacije
 * @param max maksimalna jedinka, koristi se za elitizam
 */
void zapisUDatoteku(fstream &dat, vector<GA::Jedinka*> &jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka *max){
    for(auto &jedinka : jedinke){
        dat << "X: ";
        dat.width(4);
        dat << jedinka->getX_dec();
        dat << "\tDobrota: ";
        dat.width(3);
        dat << jedinka->getDobrota_jedinke();
        dat << endl;
    }

    dat << endl << "Max dobrota jedinke: " << max->getDobrota_jedinke() << endl;
    dat << "Prosjecna dobrota jedinki: " << prosjecnaDobrotaJedinki << endl;
    dat << "Ukupna dobrota jedinki: " << ukupnaDobrotaJedinki << endl << endl << endl;
}
