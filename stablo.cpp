#include "stablo.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

Stablo::Cvor* Stablo::nadjiCvor(int vrijednost){
    Cvor* trenutni=korijen;
    while(trenutni!=nullptr){
        if(vrijednost==trenutni->vrijednost) return trenutni;
        else if(vrijednost<trenutni->vrijednost)
            trenutni=trenutni->lijevoDijete;
        else if(vrijednost>trenutni->vrijednost)
            trenutni=trenutni->desnoDijete;
    }
    return nullptr; //ukoliko smo presli list a nismo nasli element
}

//voditi racuna o sljedeciInOrder i prethodniInOrder
void Stablo::dodajCvor(int vrijednostInput){
    if(korijen==nullptr) {
        korijen = new Cvor(vrijednostInput);
        //broj nasljednika ostaje 0
        najljevljiCvor = korijen;
        najdesnijiCvor = korijen;
        return;
    }

    bool najmanji = true; //da znamo ukoliko treba updateovat najljevljiCvor tj. pomjerimo se do kraja lijevo
    bool najveci = true; //analogno za najdesnijiCvor

    Cvor* prethodniCvor = nullptr;
    Cvor* trenutniCvor = korijen;
    //ovdje ne mijenjamo sljedeciInOrder i prethodniInOrder, samo trazimo lokaciju gdje treba umetnutni novi cvor
    while(trenutniCvor!=nullptr){
        if(vrijednostInput==trenutniCvor->vrijednost) return; //ne dodajemo vrijednosti koje vec postoje
        else if(vrijednostInput<trenutniCvor->vrijednost){
            prethodniCvor = trenutniCvor;
            trenutniCvor=trenutniCvor->lijevoDijete;
            najveci = false; //idemo lijevo pa sigurno nije najveci
        }
        else if(vrijednostInput>trenutniCvor->vrijednost){
            prethodniCvor = trenutniCvor;
            trenutniCvor=trenutniCvor->desnoDijete;
            najmanji=false; //idemo desno pa sigurno nije najmanji
        }
    }

    Cvor* novi = new Cvor(vrijednostInput);
    novi->roditelj = prethodniCvor;
    //novi je trenutno nullptr, prethodni je cvor-list

    // treba povecati broj nasljednika ne samo prethodnom cvoru nego svim precima
    // to nismo ranije mogli dok se nismo uvjerili da cvor s datom vrijednoscu vec ne postoji u stablu


    if(vrijednostInput<prethodniCvor->vrijednost){
        //novi cvor je lijevo dijete
        prethodniCvor->lijevoDijete = novi;

        novi->sljedeciInOrder = prethodniCvor; //po definiciji inOrder prolazenja
        novi->prethodniInOrder = prethodniCvor->prethodniInOrder;

        if (prethodniCvor->prethodniInOrder) {
            prethodniCvor->prethodniInOrder->sljedeciInOrder = novi;
            }
        prethodniCvor->prethodniInOrder = novi;
        //sljedeci ostaje isti
    }
    else if(vrijednostInput>prethodniCvor->vrijednost){
        //novi cvor je desno dijete
        prethodniCvor->desnoDijete = novi;

        novi->prethodniInOrder = prethodniCvor;
        novi->sljedeciInOrder = prethodniCvor->sljedeciInOrder;

        if (prethodniCvor->sljedeciInOrder) {
            prethodniCvor->sljedeciInOrder->prethodniInOrder = novi;
        }
        prethodniCvor->sljedeciInOrder = novi;
        //prethodni ostaje isti
    }

    novi->dodajPoJednogNasljednikaSveDoKorijena();
    if(najmanji) najljevljiCvor=novi;
    if(najveci) najdesnijiCvor=novi;
}

void Stablo::Cvor::dodajPoJednogNasljednikaSveDoKorijena(){
    //sve dok nismo presli korijen jer korijen->roditelj==nullptr
    Cvor* pomocni=this->roditelj;
    while(pomocni!=nullptr){
        pomocni->brojNasljednika++;
        pomocni=pomocni->roditelj;
        //samo roditeljima se povecava broj nasljednika
    }
}

void Stablo::inOrder(Cvor* trenutniKorijen) {
    if(trenutniKorijen!=nullptr){
        //inOrder na lijevo podstablo
        inOrder(trenutniKorijen->lijevoDijete);
        cout<<trenutniKorijen->vrijednost<<" ";
        //inOrder na desno podstablo
        inOrder(trenutniKorijen->desnoDijete);
    }
}

void Stablo::inOrderReverse(Cvor* trenutniKorijen) {
    if(trenutniKorijen!=nullptr){
        //inOrder na desno podstablo
        inOrderReverse(trenutniKorijen->desnoDijete);
        cout<<trenutniKorijen->vrijednost<<" ";
        //inOrder na lijevo podstablo
        inOrder(trenutniKorijen->lijevoDijete);
    }
}

//ovdje u level order dodali ispis nasljednika radi provjere
//za ispis i debagiranje
void Stablo::levelOrder(Cvor* trenutniKorijen) {
    queue<Cvor*> red; //ubacujemo prvo roditelje pa djecu, ispisujemo prvo roditelje pa djecu
    red.push(trenutniKorijen);
    while(!red.empty()){
        Cvor* cvorObrada = red.front();
        cout<<"Cvor: "<<cvorObrada->vrijednost<<"; Broj nasljednika: "<<cvorObrada->brojNasljednika<<endl;
        red.pop(); //izbacili cvor koji smo ispisali
        if(cvorObrada->lijevoDijete!=nullptr) red.push(cvorObrada->lijevoDijete); //dodajemo lijevo dijete u red
        if(cvorObrada->desnoDijete!=nullptr) red.push(cvorObrada->desnoDijete); //dodajemo desno dijete u red
    }
}

//za debagiranje, da se nadje
void Stablo::Cvor::ispisiCvor(Cvor* cvor){
    cout<<"Vrijednost: "<<cvor->vrijednost;
    if(cvor->lijevoDijete != nullptr)
        cout<<" Lijevo dijete: "<<cvor->lijevoDijete->vrijednost;
    if(cvor->desnoDijete != nullptr)
        cout<<" Desno dijete: "<<cvor->desnoDijete->vrijednost;
    cout<<"Broj nasljednika: "<<cvor->brojNasljednika;
    cout<<endl;
}

//rekurzivno
int Stablo::getVisinaStabla(Cvor* trenutniKorijen) {
    if(trenutniKorijen==nullptr) return -1;
    else
        return 1+max(getVisinaStabla(trenutniKorijen->lijevoDijete), getVisinaStabla(trenutniKorijen->desnoDijete));
}

//drugi zadatak
void Stablo::inOrderVektorNapuni(Cvor* trenutniKorijen, vector<int>& linearnaStruktura) const {
    if(trenutniKorijen==nullptr) return;
    inOrderVektorNapuni(trenutniKorijen->lijevoDijete, linearnaStruktura);
    linearnaStruktura.push_back(trenutniKorijen->vrijednost);
    inOrderVektorNapuni(trenutniKorijen->desnoDijete, linearnaStruktura);
}

//lps je "longest proper prefix which is also a suffix"
void Stablo::pripremiZaKMP(const vector<int>& stabloVektor, vector<int>& lps) const{
    int duzina = 0;
    int i = 1;
    lps.resize(stabloVektor.size(), 0);
    int m = stabloVektor.size();
    while(i<m){
        if(stabloVektor[i]==stabloVektor[duzina]){
            duzina++;
            lps[i]=duzina;
            i++;
        }
        else {
            if(duzina!=0) duzina = lps[duzina-1];
            else {
                lps[i]=0;
                i++;
            }
        }
    }
}

bool Stablo::traziSaKMP(const vector<int>& veceStabloVektor, const vector<int>& manjeStabloVektor) const{
    vector<int> lps;
    pripremiZaKMP(manjeStabloVektor, lps);

    int i=0; //indeks za vece stablo
    int j=0; //indeks za manje stablo

    while(i<veceStabloVektor.size()){
        if(manjeStabloVektor[j]==veceStabloVektor[i]){
            i++;
            j++;
        }
        if(j==manjeStabloVektor.size()){
            //nasli subvector
            return true;
        }
        if(i<veceStabloVektor.size() && manjeStabloVektor[j]!=veceStabloVektor[i]){
            if(j!=0) j=lps[j-1];
            else i++;
        }
    }

    //nije pronadjen subvector
    return false;
}

bool bPodstabloOdA(const Stablo& A, const Stablo& B){
    Stablo::Cvor* korijenA = A.korijen;
    Stablo::Cvor* korijenB = B.korijen;
    vector<int> linearnoA, linearnoB;

    A.inOrderVektorNapuni(korijenA, linearnoA);
    B.inOrderVektorNapuni(korijenB, linearnoB);

    return A.traziSaKMP(linearnoA, linearnoB);
}

bool bPodskupOdA(const Stablo& A, const Stablo& B){
    Stablo::Cvor* korijenA = A.korijen;
    Stablo::Cvor* korijenB = B.korijen;

    //B: - ... odmah jest podskup
    //A: - ... podskup jedino ako je i B prazan skup

    if(korijenB==nullptr) return true;
    if(korijenA==nullptr && korijenB==nullptr) return true;

    vector<int> inOrderA, inOrderB;
    A.inOrderVektorNapuni(korijenA, inOrderA);
    B.inOrderVektorNapuni(korijenB, inOrderB);

    //B: 1,3,4,5
    //A: 1,2 ... odmah nije podskup

    if(inOrderB.size()>inOrderA.size()) return false;

    //B: 1,2,3,4
    //A: 1,2,3,5,6
    //nije podskup jer Bi<Aj (4<5)

    int indeksA=0;
    int indeksB=0;

    while(indeksA<inOrderA.size() && indeksB<inOrderB.size()){

        //B: 4,5 ... A:1,2,4,5
        if(inOrderB[indeksB]>inOrderA[indeksA]){
            //indeksB ostaje, indeksA se pomijera
            indeksA++;
        }
        //B: 1,2 ... A: 4,5,6
        else if(inOrderB[indeksB]<inOrderA[indeksA]){
            return false;
        }
        //B: 1,2 ... A: 1,2,3,4,5
        else if(inOrderB[indeksB]==inOrderA[indeksA]){
            indeksB++;
            indeksA++;
        }
    }

    //ako smo iz A izasli onda vracamo false, ako smo iz B izasli ond vracamo true
    //odnosno, ako smo dosegli kraj B onda vracamo true, inace false
    return (indeksB==inOrderB.size());
}

int Stablo::ktiNajveci(int k, Cvor* trenutniKorijen) {
    if (trenutniKorijen==nullptr) return -1;
    if (k>=(trenutniKorijen->brojNasljednika+1)) return -1;
    if (trenutniKorijen->desnoDijete) {
        int nasljedniciDesno = trenutniKorijen->desnoDijete->brojNasljednika;
        if (nasljedniciDesno == k - 1) {
            //desno podstablo od cvora ima k elemenata, ali kako je najdesniji cvor k=0 tako je stablo[k] ustvari korijen
            return trenutniKorijen->vrijednost;
        } else if (nasljedniciDesno >= k) {
            //npr. desno imamo 15 elemenata a mi trazimo 4. po velicini
            return ktiNajveci(k, trenutniKorijen->desnoDijete);
        } else if (nasljedniciDesno < k && trenutniKorijen->lijevoDijete!=nullptr) {
            //npr. desno podstablo ima 2 cvora, lijevo ima 11 cvorova, a mi trazimo stablo[5]
        //trazimo stablo[2] u lijevom podstablu, 2=5-(1+1+1)
            int preostalo = k - (nasljedniciDesno+1+1);
            return ktiNajveci(preostalo, trenutniKorijen->lijevoDijete);
        }
    } else if (k==0) {
        // nema desnog podstabla uopste
        return trenutniKorijen->vrijednost;
    } else if (trenutniKorijen->lijevoDijete)
        return ktiNajveci(k-1, trenutniKorijen->lijevoDijete);

    else return -1;
}


