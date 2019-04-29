#ifndef GRAF2_HH
#define GRAF2_HH


#include "lista.hh"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/* Definica wierzchołka */
template<typename Typ>
struct Wierzcholek
{
    Typ zawartosc;
    int index;
};

/* Definica krawedzi */
template<typename Typ>
struct Krawedz
{   
    Wierzcholek<Typ> *wsk_1;        // Wskazniki na wierzchołki 
    Wierzcholek<Typ> *wsk_2;        // łączące sie z dana krawedzią            
    double waga;
};

/* Definicja grafu  */
template<typename Typ>
class MacierzSasiedztwa
{
   Krawedz<Typ>         **tab;                  // Macierz sasiedztwa
   int                  value_V,value_E;        // Ilosc krawedzi i wierzchołków
   int                  max_V;                  // Maxmalna ilosc bez alkowania pamieci

 public:
    MacierzSasiedztwa(int V);
    ~MacierzSasiedztwa();
    IncidentEdges(int index_V);                 // Literowanie poloczonych wierzchołków
    AreAdjacent(int index_V1,int index_V2);     // CZy dwa wierzchołki sa połaczone
    InsertVertex(Typ Obiekt);                   // Dodaje wierzchołek o zawartosci obiekt
    InsertEdge(int index_V1,int index_V2,double w)  // Dodaje krawedz o wadze w
    RemoveVertex(int index_V);                  // Usuwa wierzchołek i jego krawedzie
    RemoveEdge(int index_V1,int index_V2);      // Usuwa krawedz
};

/* Konstruktor */





#endif
