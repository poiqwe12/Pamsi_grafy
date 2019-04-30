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
    Lista<Wierzcholek <Typ> > L_Wierzcholek; // Lista przechowujaca wierzcholki

  public:
    MacierzSasiedztwa(bool S);
    ~MacierzSasiedztwa();
    void IncidentEdges(int index_V);                       // Literowanie poloczonych wierzchołków
    bool AreAdjacent(int index_V1, int index_V2);          // CZy dwa wierzchołki sa połaczone
    bool InsertVertex(Typ Obiekt);                         // Dodaje wierzchołek o zawartosci obiekt
    bool InsertEdge(int index_V1, int index_V2, double w); // Dodaje krawedz o wadze w
    bool RemoveVertex(int index_V);                        // Usuwa wierzchołek i jego krawedzie
    bool RemoveEdge(int index_V1, int index_V2);           // Usuwa krawedz
    void ShowTime();
};

/* Konstruktor */
template <typename Typ>
MacierzSasiedztwa<Typ>::MacierzSasiedztwa(bool S)
{
    max_V = 25;
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
    Wierzcholek<Typ> wierz;                         // Tworzy wierzcholek daje mu kolejny index
    ++value_V;                                      // oraz dodaje go do listy wierzchołków
    wierz.index = value_V;
    wierz.zawartosc = Objekt;   
    L_Wierzcholek.Dodaj_Element(wierz, 0);
    return true;
}

/* Dodawanie krawedzi */
template <typename Typ>
bool MacierzSasiedztwa<Typ>::InsertEdge(int index_V1, int index_V2, double w)
{
    if (Skierowany) //Procedura dla grafu skierowanego
    {
        tab[index_V1][index_V2] = new Krawedz<Typ>;                        // Tworzenie krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V1 - 1]); // Dodanie łączących wierzchołków do krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V2 - 1]);
        (tab[index_V1][index_V2])->waga = w;
    }
    else // Procedura dla grafu nieskierowanego
    {
        tab[index_V1][index_V2] = new Krawedz<Typ>;                        // Tworzenie krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V1 - 1]); // Dodanie łączących wierzchołków do krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V2 - 1]); // Jak jest nieskierowany dodaje ten sam wskaznik
        tab[index_V2][index_V1] = tab[index_V1][index_V2];                 // krawedzi do drugiej pozycji w macierzy 
        (tab[index_V1][index_V2])->waga = w;
    }
    return true;
}

/* Wyswietlanie macierzy sasiedztwa */
template <typename Typ>
void MacierzSasiedztwa<Typ>::ShowTime()
{
    cout << "   ";
    for (int i = 0; i < max_V; i++)
    {
        cout << setw(3) << i;
    }
    cout << endl
         << endl;
    for (int i = 0; i < max_V; i++)
    {
        cout << setw(2) << i << "|";
        for (int j = 0; j < max_V; j++)
        {   
            if(tab[i][j]==NULL)
            {
                cout << setw(3) << "N";
            }
            else
            {
            cout << setw(3) << (tab[i][j])->waga;
        }
        }
        cout << endl;
    }
}








#endif
