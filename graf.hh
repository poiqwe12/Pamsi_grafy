#ifndef GRAF_HH
#define GRAF_HH


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "lista.hh"
using namespace std;

class Graf
{
    int **tab;
    int value_V, value_E;
    
  public:
    Graf(int V);
    ~Graf();
    void Stworz_Graf(int index);
    void Zeruj();
    int Get_value_V()
    {
        return value_V;
    }
    int Get_value_E()
    {
        return value_E;
    }
    int **Get_tab()
    {
        return tab;
    }
};
/* Alokowanie pamieci na macierz i wyzerowanie macierzy */
Graf::Graf(int V)
{
    value_V = V;
    tab = new int *[V];
    for (int i = 0; i < V; ++i)
    {
        tab[i] = new int[V];
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            tab[i][j] = 0;
        }
    }
}
Graf::~Graf()
{
    for (int i = 0; i < value_V; ++i)
    {
        delete[] tab[i];
    }
    delete[] tab;
}
void Graf::Zeruj()
{
    for (int i = 0; i < value_V; i++)
    {
        for (int j = 0; j < value_V; j++)
        {
            tab[i][j] = 0;
        }
    }
}
void Graf::Stworz_Graf(int index)
{
    srand(time(NULL));
    int E;
    int k, l;
    switch (index)
    {
    case 0:
        value_E = value_V * (value_V - 1) / 2;
        break;
    case 1:
        value_E = value_V * (value_V - 1) * 3 / 8;
        break;
    case 2:
        value_E = value_V * (value_V - 1) / 4;
        break;
    case 3:
        value_E = value_V * (value_V - 1) / 8;
        break;
    default:
        break;
    }
    E = value_E;                                /// Ilosc krawedzi wyznaczona z gestosci
    while (E > 0)
    {
        k = rand() % value_V;                   /// Losowanie miejsca na krawedz
        l = rand() % value_V;       
        if (l < k)
        {
            if (tab[l][k] == 0)
            {
                tab[l][k] = 1;                  /// Tutaj mozna ustawic wagi
                E--;
            }
        }
    }
    for (int i = 0; i < value_V; i++)           /// Tworzenie macierzy symetrycznej
    {
        for (int j = 0; j < i; j++)
        {
            tab[i][j] = tab[j][i];
        }
    }
}

/////////Wyswietlanie macierzy sasiedztwa/////////////
std::ostream &operator<<(std::ostream &stream, Graf &G)
{
    cout << "   ";
    for (int i = 0; i < G.Get_value_V(); i++)
    {
        cout << setw(3) << i;
    }
    cout << endl
         << endl;
    for (int i = 0; i < G.Get_value_V(); i++)
    {
        cout << setw(2) << i << "|";
        for (int j = 0; j < G.Get_value_V(); j++)
        {
            cout << setw(3) << (int)G.Get_tab()[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << "Ilosc wierzchołkow:  " << G.Get_value_V() << endl;
    cout << "Ilosc krawedzi:      " << G.Get_value_E() << endl;
    cout << endl;

    return stream;
}

#endif
