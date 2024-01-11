#include "stablo.h"
#include "podstablo.h"
#include <iostream>
using namespace std;

void PrviZadatak(Stablo s){
    cout<<"\n------ PRVI ZADATAK ------\n\n";

    if(s.praznoStablo()){
        cout<<"Ne radimo s praznim stablom.\n";
        return;
    }
    cout<<"inOrder\n";
    s.inOrder();
    cout<<endl<<endl;

    cout<<"levelOrder"<<endl;
    s.levelOrder();
    cout<<endl;

    cout<<"getVisinaStabla: "<<s.getVisinaStabla()<<endl<<endl;

    cout<<"In-Order iterator za stablo: for(it = s.Begin(); !it.dosaoDoKraja(); it.pomjeriNaSljedeceg())..."<<endl;
    Stablo::inOrderIterator it;
    for(it = s.Begin(); !it.dosaoDoKraja(); it.pomjeriNaSljedeceg()){
        cout << it.getVrijednost()<<" ";
    }
    cout<<endl<<endl;

    cout<<"Prvi zadatak - Iterator: for(auto it = s.Begin(); it != s.End(); it++)...\n";
    for(auto it = s.Begin(); it!=s.End(); it++){
        cout << it.getVrijednost()<<" ";
    }

    cout<<endl<<endl;
    cout<<"Prvi zadatak - Reverse iterator: for(auto it = s.rBegin(); it!=s.rEnd(); it++)...\n";
    for(auto it = s.rBegin(); it!=s.rEnd(); it++){
        cout << it.getVrijednost()<<" ";
    }
    cout<<endl;
}

void TreciZadatak(Stablo s){
    cout<<"\n------ TRECI ZADATAK ------\n\n";
    if(s.praznoStablo()){
        cout<<"Ne radimo s praznim stablom.\n";
        return;
    }
    int k;
    cout<<"Indeksiranje: stablo[k] vraca (k+1). element po velicini.\nUnesite k (-1 za prekid): ";
    cin>>k;
    while(k!=-1){
        cout<<"stablo[k] = "<<s[k]<<endl;
        cout<<"Unesite k (-1 za prekid): ";
        cin>>k;
    }
}

void DrugiZadatak(){
    cout<<"\n------ DRUGI ZADATAK ------\n\n";

    //prvo stablo

    Stablo s1;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s1.dodajCvor(broj);
    }
    cout<<"\ninOrder: ";
    s1.inOrder();
    cout<<endl<<endl;

    //drugo stablo

    Stablo s2;
    cout<<"Unesite podskup prvog stabla.\n"<<endl;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s2.dodajCvor(broj);
    }
    cout<<"\ninOrder: ";
    s2.inOrder();
    cout<<endl<<endl;
    cout<<"Je li doista podskup? "<<bPodskupOdA(s1, s2)<<endl<<endl;

    //trece stablo

    Stablo s3;
    cout<<"Unesite stablo koje nije podskup prvog stabla.\n"<<endl;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s3.dodajCvor(broj);
    }
    cout<<"\ninOrder: ";
    s3.inOrder();
    cout<<"\nJe li podskup? "<<bPodskupOdA(s1, s3)<<endl;
}

int main() {

    Stablo s;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s.dodajCvor(broj);
    }

    PrviZadatak(s);
    TreciZadatak(s);
    DrugiZadatak();

    //dodatno
   // TestPodstablo();*/

    cout<<"\n------ KRAJ ------\n";

    return 0;
}
