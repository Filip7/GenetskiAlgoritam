#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Jedinka.h"
#include "Pomocni.h"

using namespace std;

constexpr int BROJ_ITERACIJA = 30;

constexpr int VELICINA_POPULACIJE = 20;
constexpr double VJEROJATNOST_KRIZANJA = 0.9;

void
ispis(vector<GA::Jedinka*>& jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka* max);

void
zapisUDatoteku(fstream& dat, vector<GA::Jedinka*>& jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki,
        GA::Jedinka* max);

vector<GA::Jedinka*> selektirajJedinke(vector<GA::Jedinka*>& jedinke, GA::Jedinka* max);

void isprazniJedinke(vector<GA::Jedinka*>& jedinke);

int main()
{
    string PUTANJA = "../genetskiAlgoritamRezultat.txt";
    vector<GA::Jedinka*> jedinke;

    auto usporedi = [](GA::Jedinka* x, GA::Jedinka* y) { return x->getDobrota_jedinke() < y->getDobrota_jedinke(); };

    /*Izrada prve populacije, sve jednike su nasumicno generirane*/
    for (int i = 0; i<VELICINA_POPULACIJE; ++i) {
        jedinke.push_back(new GA::Jedinka{});
    }

    sort(jedinke.begin(), jedinke.end(), usporedi);

    fstream dat{PUTANJA, ios_base::out};
    if (!dat) {
        dat.clear();
        dat.open(PUTANJA, ios_base::out);
    }

    fstream datProsjek{"../Graf/prosjeci.txt", ios_base::out};
    if (!datProsjek) {
        datProsjek.clear();
        datProsjek.open(PUTANJA, ios_base::out);
    }

    for (int iter = 0; iter<BROJ_ITERACIJA; ++iter) {
        double ukupnaDobrotaJedinki = 0;
        double prosjecnaDobrotaJedinki;
        cout << "Generacija: " << iter+1 << endl;
        dat << "Generacija: " << iter+1 << endl;

        for (auto& jedinka : jedinke) {
            ukupnaDobrotaJedinki += jedinka->getDobrota_jedinke();
        }

        for (auto& jedinka : jedinke) {
            auto normaliziranaDobrota = jedinka->getDobrota_jedinke() / ukupnaDobrotaJedinki * 100;
            jedinka->setNormalizirana_dobrota_jedinke(static_cast<int>(normaliziranaDobrota));
        }

        prosjecnaDobrotaJedinki = ukupnaDobrotaJedinki / jedinke.size();
        datProsjek << prosjecnaDobrotaJedinki << endl;

        auto max = *std::max_element(begin(jedinke), end(jedinke), usporedi);

        ispis(jedinke, ukupnaDobrotaJedinki, prosjecnaDobrotaJedinki, max);
        zapisUDatoteku(dat, jedinke, ukupnaDobrotaJedinki, prosjecnaDobrotaJedinki, max);

        jedinke = selektirajJedinke(jedinke, max);
        sort(jedinke.begin(), jedinke.end(), usporedi);
    }

    dat.close();
    datProsjek.close();

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        cout << endl << endl << "KRAJ PROGRAMA" << endl << "Unesi bilo sto za kraj:";
        char a;
        cin >> a;
    #endif

    isprazniJedinke(jedinke);

    return 0;
}

/**
 * Obavlja selekciju jedinki, odabir roditelja te stvara novu populaciju
 * @param jedinke vector svih jedinki prethodne generacije
 * @param max maksimalna jedinka, koristi se za elitizam
 * @return vector nove generacije jedinki
 */
vector<GA::Jedinka*> selektirajJedinke(vector<GA::Jedinka*>& jedinke, GA::Jedinka* max)
{
    vector<unsigned int> pool;
    vector<GA::Jedinka*> nova_populacija;
    nova_populacija.push_back(max);
    max->mutiraj();

    // Izrada "poola" jedinki gdje se biraju nasumicni za razmnozavanje
    for (unsigned int i = 0; i<VELICINA_POPULACIJE; ++i) {
        int n = jedinke[i]->getNormalizirana_dobrota_jedinke();
        for (int j = 0; j < n; ++j) {
            pool.push_back(i);
        }
    }

    auto broj_jedinki_u_poolu = static_cast<int>(pool.size());

    // Izrada novih jedniki dok god populacija ne dostigne zadanu velicinu
    while (nova_populacija.size() !=VELICINA_POPULACIJE) {
        bool kontrola = true;
        //int rod1 = odabranik(mt);
        auto rod1 = GA::Rand<int>(0, broj_jedinki_u_poolu-1);
        auto rod2 = GA::Rand<int>(0, broj_jedinki_u_poolu-1);
        while (rod1==rod2) {
            // Ako su odabrana dva ista roditelja trazi drugog dok nije razlicit
            rod2 = GA::Rand<int>(0, broj_jedinki_u_poolu-1);
        }

        // Racunamo vjerojatnost krizanja te ako je zadovoljeno krizamo jedinke
        if (GA::Rand<double>(0, 1) < VJEROJATNOST_KRIZANJA) {
            auto* dijete = new GA::Jedinka{*jedinke.at(pool[rod1]), *jedinke.at(pool[rod2])};
            // Nakon izrade dijete se mutira
            dijete->mutiraj();
            for (auto& rod : nova_populacija) {
                if (*dijete == *rod) {
                    // Ako dijete vec postoji, ne pohranjujemo ga nego ponavljamo selekciju
                    kontrola = false;
                }
            }

            if (kontrola) {
                // Dijete je unikatno te ga pohranjujemo u novu populaciju
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
void isprazniJedinke(vector<GA::Jedinka*>& jedinke)
{
    for (int iter = VELICINA_POPULACIJE-1; iter>=0; --iter) {
        delete jedinke[iter];
        jedinke.pop_back();
    }
}

/**
 * Ispisuje jedinke na zaslon
 * @param jedinke vector svih jedinki generacije
 * @param jedinke vector svih jedinki generacije
 * @param ukupnaDobrota zbroj dobrota svih jedinki generacije
 * @param prosjecnaDobrotaJedinki prosjek dobrota generacije
 * @param max maksimalna jedinka, koristi se za elitizam
 */
void ispis(vector<GA::Jedinka*>& jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki, GA::Jedinka* max)
{
    for (auto& jedinka : jedinke) {
        cout << *jedinka << endl;
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
void
zapisUDatoteku(fstream& dat, vector<GA::Jedinka*>& jedinke, double ukupnaDobrotaJedinki, double prosjecnaDobrotaJedinki,
        GA::Jedinka* max)
{
    for (auto& jedinka : jedinke) {
        dat << *jedinka << endl;
    }

    dat << endl << "Max dobrota jedinke: " << max->getDobrota_jedinke() << endl;
    dat << "Prosjecna dobrota jedinki: " << prosjecnaDobrotaJedinki << endl;
    dat << "Ukupna dobrota jedinki: " << ukupnaDobrotaJedinki << endl << endl << endl;
}
