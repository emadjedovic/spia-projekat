#include <iostream>
#include "stablo.h"
#include "podstablo.h"
using namespace std;

void TestPodstablo()
{
    cout<<"\n------ TEST PODSTABLO ------\n\n";

    //prvo stablo

    Stablo s1;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s1.dodajCvor(broj);
    }
    cout<<endl;
    cout<<"levelOrder"<<endl;
    s1.levelOrder();
    cout<<endl;
    cout<<"getVisinaStabla: "<<s1.getVisinaStabla()<<endl;

    //drugo stablo

    Stablo s2;
    cout<<"\nUnesite stablo koje je podstablo prvog."<<endl;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s2.dodajCvor(broj);
    }
    cout<<endl;
    cout<<"levelOrder"<<endl;
    s2.levelOrder();
    cout<<endl;
    cout<<"getVisinaStabla: "<<s2.getVisinaStabla()<<endl;
    cout<<"Imamo podstablo? "<<bPodstabloOdA(s1, s2)<<endl;

    //trece stablo

    Stablo s3;
    cout<<"\nUnesite stablo koje nije podstablo prvog."<<endl;
    while(true) {
        int broj;
        cout<<"Unesi broj (0 za kraj): ";
        cin>>broj;
        if(broj==0) break;
        s3.dodajCvor(broj);
    }
    cout<<endl;
    cout<<"levelOrder"<<endl;
    s3.levelOrder();
    cout<<endl;
    cout<<"getVisinaStabla: "<<s3.getVisinaStabla()<<endl;
    cout<<"Imamo podstablo? "<<bPodstabloOdA(s1, s3)<<endl;
}
