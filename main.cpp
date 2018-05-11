#include <iostream>
#include <algorithm>
#include <vector>
#include "Jedinka.h"

using namespace std;

constexpr int BROJ_ITERACIJA = 30;
constexpr int VELICINA_POPULACIJE = 20;
constexpr double VJEROJATNOST_KRIZANJA = 0.9;
constexpr double VJEROJATNONST_MUTACIJE = 0.01;

bool usporedbaDobroteJedinki(GA::Jedinka *x, GA::Jedinka *y);
void ispis(vector<GA::Jedinka*> &jedinke, GA::Jedinka *max);

int main() {
    vector<GA::Jedinka*> jedinke;
    for(int i = 0; i < VELICINA_POPULACIJE; ++i){
        jedinke.push_back(new GA::Jedinka);
    }
    sort(jedinke.begin(), jedinke.end(), usporedbaDobroteJedinki);

    for(int iter = 0; iter < BROJ_ITERACIJA; ++iter){
        cout << "Generacija: " << iter + 1 << endl;

        auto max = *std::max_element(begin(jedinke), end(jedinke), usporedbaDobroteJedinki);
        max->setElitna(true);

        // Dodati selekciju, mutaciju i mnozenje

        ispis(jedinke, max);
    }

    for(auto a : jedinke){
        delete a;
    }

	return 0;
}

bool usporedbaDobroteJedinki(GA::Jedinka *x, GA::Jedinka *y) {
    return x->getDobrota_jedinke() < y->getDobrota_jedinke();
}

void ispis(vector<GA::Jedinka*> &jedinke, GA::Jedinka *max){
    double prosjecnaDobrotaJedinki = 0;
    for(auto &jedinka : jedinke){
        jedinka->ispisi(true);
        //cout << *a << endl;
        prosjecnaDobrotaJedinki += jedinka->getDobrota_jedinke();
    }
    cout << endl << "Max dobrota jedinke: " << max->getDobrota_jedinke() << endl;
    cout << "Prosjecna dobrota jedinki: " << prosjecnaDobrotaJedinki << endl << endl << endl;
}
