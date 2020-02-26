#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
ofstream g("date.out");

struct tranzitie{
    char caracter;
    int destinatie;
};

struct stare{
    int numarStare;
    int eFinal = 0;
    int nrTranzitii = 0;
    vector<tranzitie> tranzitii;
};

int gasesteStare(vector<stare> stari, int numarStareCautata, int nrStari)
{
    int i;

    for (i = 0; i < nrStari; i++)
        if (stari.at(i).numarStare == numarStareCautata)
            return i;

    return 0;
}


int evalueazaCuvant(int nrStari, vector<stare> stari, int stareCurenta, string cuvant, int literaCurenta)
{
    int i, sum, j;
    char lit;

    sum = 0;

    if (literaCurenta + 1 > cuvant.length())
        return stari.at(stareCurenta).eFinal;

    lit = cuvant.at(literaCurenta);

    for (i = 0; i < stari.at(stareCurenta).nrTranzitii; i++)
        if (stari.at(stareCurenta).tranzitii.at(i).caracter == lit)
        {
            //cout<<stari.at(stareCurenta).numarStare<<" - > "<<stari.at(stareCurenta).tranzitii.at(i).destinatie<<" cu "<<lit<<" ("<<cuvant<<")"<<endl;
            sum += evalueazaCuvant(nrStari, stari, gasesteStare(stari, stari.at(stareCurenta).tranzitii.at(i).destinatie, nrStari), cuvant, literaCurenta + 1);
        }

    return sum;
}

int main()
{
    int nrStari, i, nrLitere, stareInitiala, nrStariFinale, nrTranzitii, a, c, nrCuvinte;
    char b;

    vector<char> litere;
    vector<stare> stari;
    vector<string> cuvinte;
    string cuvant;


    cout<<"Numar stari: ";
    cin>>nrStari;

    for (i = 0; i < nrStari; i++)
    {
        cout<<"Starea "<<i + 1<<": ";

        stare nou = *new(stare);
        cin>>nou.numarStare;

        stari.push_back(nou);
    }

    cout<<"Numar litere: ";
    cin>>nrLitere;

    for (i = 0; i < nrLitere; i++)
    {
        cout<<"Litera "<<i+1<<": ";
        cin>>b;
        litere.push_back(b);
    }

    cout<<"Stare initiala: ";
    cin>>stareInitiala;

    cout<<"Numar stari finale: ";
    cin>>nrStariFinale;

    for (i = 0; i < nrStariFinale; i++)
    {
        cout<<"Starea finala "<<i+1<<": ";
        cin>>a;
        a = gasesteStare(stari, a, nrStari);
        stari.at(a).eFinal = 1;
    }

    cout<<"Numar tranzitii: ";
    cin>>nrTranzitii;

    for (i = 0; i < nrTranzitii; i++)
    {
        cout<<"Tranzitia "<<i+1<<": ";
        cin>>a>>b>>c;

        a = gasesteStare(stari, a, nrStari);

        tranzitie nou = *new(tranzitie);
        nou.caracter = b;
        nou.destinatie = c;

        stari.at(a).tranzitii.push_back(nou);
        stari.at(a).nrTranzitii++;
    }

    cout<<"Numar cuvinte: ";
    cin>>nrCuvinte;

    cin.get();
    for (i = 0; i < nrCuvinte; i++)
    {
        cout<<"Cuvantul "<<i+1<<": ";
        getline(cin, cuvant);
        cuvinte.push_back(cuvant);
        //cout<<"am citit "<<cuvant<<endl;
    }

    for (i = 0; i < nrCuvinte; i++)
    {
        if (evalueazaCuvant(nrStari, stari, gasesteStare(stari, stareInitiala, nrStari), cuvinte.at(i), 0) > 0)
            g<<"DA"<<endl;//cout<<"DA"<<endl;
        else
            g<<"NU"<<endl;//cout<<"NU"<<endl;
    }

    g.close();

    return 0;
}
