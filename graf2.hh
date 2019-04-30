#ifndef GRAF2_HH
#define GRAF2_HH

#include "lista.hh"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/* Definica wierzchołka */
template <typename Typ>
struct Wierzcholek
{
    Typ zawartosc;
    int index;
};

/* Definica krawedzi */
template <typename Typ>
struct Krawedz
{
    Wierzcholek<Typ> *wsk_1; // Wskazniki na wierzchołki
    Wierzcholek<Typ> *wsk_2; // łączące sie z dana krawedzią
    double waga;
};

/* Definicja grafu  */
template <typename Typ>
class MacierzSasiedztwa
{
    Krawedz<Typ> ***tab;                   // Macierz sasiedztwa
    int value_V, value_E;                  // Ilosc krawedzi i wierzchołków
    int max_V;                             // Maxmalna ilosc bez alkowania pamieci
    bool Skierowany;                       // Czy graf jest skierowanyc czy nie
    Lista<Wierzcholek<Typ> > L_Wierzcholek; // Lista przechowujaca wierzcholki

  public:
    MacierzSasiedztwa( bool S);
    ~MacierzSasiedztwa();
    void IncidentEdges(int index_V);                       // Literowanie poloczonych wierzchołków
    bool AreAdjacent(int index_V1, int index_V2);          // CZy dwa wierzchołki sa połaczone
    bool InsertVertex(Typ Obiekt);                         // Dodaje wierzchołek o zawartosci obiekt
    bool InsertEdge(int index_V1, int index_V2, double w); // Dodaje krawedz o wadze w
    bool RemoveVertex(int index_V);                        // Usuwa wierzchołek i jego krawedzie
    bool RemoveEdge(int index_V1, int index_V2);           // Usuwa krawedz
};

/* Konstruktor */
template <typename Typ>
MacierzSasiedztwa<Typ>::MacierzSasiedztwa( bool S)
{
    max_V = 250;
    value_V = 0;
    Skierowany = S;
    tab = new Krawedz<Typ> **[max_V];
    for (int i = 0; i < max_V; ++i)
    {
        tab[i] = new Krawedz<Typ> *[max_V];
    }
    for (int i = 0; i < max_V; i++)
    {
        for (int j = 0; j < max_V; j++)
        {
            tab[i][j] = NULL;
        }
    }
}

/* Destruktor */
template <typename Typ>
MacierzSasiedztwa<Typ>::~MacierzSasiedztwa()
{
    for (int i = 0; i < value_V; i++)
    {
        for (int j = 0; j < value_V; j++)
        {
            delete tab[i][j];
        }
    }
    for (int i = 0; i < value_V; ++i)
    {
        delete[] tab[i];
    }
    delete[] tab;
}
/* Dodawanie wierzcholka */
template <typename Typ>
bool MacierzSasiedztwa<Typ>::InsertVertex(Typ Objekt)
{
    Wierzcholek<Typ> wierz;
    ++value_V;
    wierz.index = value_V;
    wierz.zawartosc = Objekt;
    L_Wierzcholek.Dodaj_Element(wierz,0);
     return true;
}

#endif
