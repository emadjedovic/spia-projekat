#ifndef STABLO_H
#define STABLO_H
#include <vector>

class Stablo {

public:

    struct Cvor {
        int vrijednost;
        int brojNasljednika; //za indeksiranje (zadatak 3)
        Cvor* roditelj;
        Cvor* lijevoDijete;
        Cvor* desnoDijete;
        Cvor* sljedeciInOrder; //za iterator unaprijed (zadatak 1)
        Cvor* prethodniInOrder; // za iterator unazad (zadatak 1)

        Cvor(int vr): vrijednost(vr), brojNasljednika(0), roditelj(nullptr), lijevoDijete(nullptr), desnoDijete(nullptr), sljedeciInOrder(nullptr), prethodniInOrder(nullptr) {}

        void ispisiCvor(Cvor*);
        Cvor* getSljedeciInOrder(Cvor* trenutni) { return trenutni->sljedeciInOrder; }
        Cvor* getPrethodniInOrder(Cvor* trenutni) { return trenutni->prethodniInOrder; }

        //nakon sto dodamo novi cvor, idemo unazad do korijena i povecavamo brojNasljednika za svakog roditelja
        //kao kad se rodi novo dijete u porodici
        void dodajPoJednogNasljednikaSveDoKorijena();
    };

    class inOrderIterator {
        Cvor* pokazivac;
        friend class Stablo;
    public:
        inOrderIterator(Cvor* pok = nullptr): pokazivac(pok) {}
        int getVrijednost() { return pokazivac->vrijednost; }
        void pomjeriNaSljedeceg() { pokazivac=pokazivac->sljedeciInOrder; } //nullptr samo na kraju
        bool dosaoDoKraja() { return pokazivac==nullptr; }

        bool operator!=(const inOrderIterator& drugiIterator) const {
            return pokazivac != drugiIterator.pokazivac;
            //u it!=stablo.End() znaci sve dok cvor na koji pokazuje it nije nullptr
        }

        // postfix, nema potrebe za prefix
        inOrderIterator operator++(int) {
            inOrderIterator stariIterator = *this;
            pomjeriNaSljedeceg(); //update trenutnog, vracamo stari
            return stariIterator;
        }
    };

    class inOrderReverseIterator {
        Cvor* pokazivac;
        friend class Stablo;
    public:
        inOrderReverseIterator(Cvor* pok = nullptr) : pokazivac(pok) {}
        int getVrijednost() { return pokazivac->vrijednost; }
        void pomjeriNaPrethodnog() { pokazivac = pokazivac->prethodniInOrder; }
        bool dosaoDoPocetka() { return pokazivac == nullptr; }

        bool operator!=(const inOrderReverseIterator& drugiIterator) const {
            return pokazivac != drugiIterator.pokazivac;
        }

        inOrderReverseIterator operator++(int) {
            inOrderReverseIterator stariIterator = *this;
            pomjeriNaPrethodnog();
            return stariIterator;
        }
    };

private:

    Cvor* korijen;
    Cvor* najljevljiCvor; //za Begin(), najmanji cvor po vrijednosti
    Cvor* najdesnijiCvor; //za rBegin(), najveci cvor po vrijednosti

    void inOrder(Cvor*); //ne treba nuzno za prvi zadatak
    void inOrderReverse(Cvor*); //ne treba nuzno za prvi zadatak
    void levelOrder(Cvor*); //za ispis i debagiranje
    int getVisinaStabla(Cvor*);

    //podstablo

    void inOrderVektorNapuni(Cvor*, std::vector<int>&) const;
    void pripremiZaKMP(const std::vector<int>&, std::vector<int>&) const;
    bool traziSaKMP(const std::vector<int>&, const std::vector<int>&) const;

    //treci zadatak

    int ktiNajveci(int k, Cvor*);

public:

    Stablo(): korijen(nullptr), najljevljiCvor(nullptr) {}
    int getBrojCvorova() {return 1+korijen->brojNasljednika;}
    bool praznoStablo() {return korijen == nullptr;}
    Cvor* nadjiCvor(int);
    void dodajCvor(int);
    void inOrder() { inOrder(korijen); } //ne treba nuzno za prvi zadatak
    void inOrderReverse() { inOrderReverse(korijen); } //ne treba nuzno za prvi zadatak
    void levelOrder() { levelOrder(korijen); } //za ispis i debagiranje
    int getVisinaStabla() { return getVisinaStabla(korijen); }

    //prvi zadatak

    inOrderIterator Begin() { return najljevljiCvor; }
    inOrderIterator End() { return inOrderIterator(nullptr); }

    inOrderReverseIterator rBegin() { return najdesnijiCvor; }
    inOrderReverseIterator rEnd() { return inOrderReverseIterator(nullptr); }

    //drugi zadatak

    friend bool bPodskupOdA(const Stablo& A, const Stablo& B);

    //podstablo

    friend bool bPodstabloOdA(const Stablo& A, const Stablo& B);

    //treci zadatak

    int operator[](int k) { return ktiNajveci(k, korijen); }
};

#endif // STABLO_H
