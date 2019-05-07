#ifndef GRAF_HH
#define GRAF_HH


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "lista.hh"
using namespace std;

template<typename Typ>
struct Wierzcholek2
{
    Typ zawartosc;
    int index;

};
template<typename Typ>
struct Krawedz2
{
    double waga;
    Wierzcholek2<Typ> *wsk;
    Wierzcholek2<Typ> *wsk2;
};

template<typename Typ>
class ListaSasiedztwa
{
    Lista<Wierzcholek2<Typ> > L_wierzcholek;
    Lista<Krawedz2<Typ> >     L_krawedz;
    Lista<Lista<Krawedz2<Typ>*> >     L_incydencji;
    int value_E,value_V,start_V;
public:
    ListaSasiedztwa(int V);
    ~ListaSasiedztwa();
    void IncidentEdges(int index_V);                       // Literowanie poloczonych wierzchołków
    bool AreAdjacent(int index_V1, int index_V2);          // CZy dwa wierzchołki sa połaczone
    bool InsertVertex(Typ Obiekt);                         // Dodaje wierzchołek o zawartosci obiekt
    bool InsertEdge(int index_V1, int index_V2, double w); // Dodaje krawedz o wadze w
    bool RemoveVertex(int index_V);                        // Usuwa wierzchołek i jego krawedzie
    bool RemoveEdge(int index_V1, int index_V2);           // Usuwa krawedz
    void ShowTime();                                       // Wyswietla macierz sasiedztwa
    bool WczytajZPliku(char *nazwa_plik);                  // Wczytuje graf z pliku
    void Inicjuj(int index);                               // Inicjuje graf o okreslonej gestosci
};
/* Konstruktor */
template<typename Typ>
ListaSasiedztwa<Typ>::ListaSasiedztwa(int V)
{   
    value_V=V;
    value_E=0;
    start_V=0;
}
/* Dekstruktor */
template<typename Typ>
ListaSasiedztwa<Typ>::~ListaSasiedztwa()
{   
   
}
/* Dodawanie wierzcholka */
template <typename Typ>
bool ListaSasiedztwa<Typ>::InsertVertex(Typ Objekt)
{
    Wierzcholek2<Typ> wierz; // Tworzy wierzcholek daje mu kolejny index
                            // oraz dodaje go do listy wierzchołków
    wierz.index = value_V++;
    wierz.zawartosc = Objekt;
    L_wierzcholek.Dodaj_Element(wierz, 0);
    Lista<Krawedz2<Typ>* > w;
    L_incydencji.Dodaj_Element(w,value_V);
    return true;
}
/* Dodawanie krawedzi */
template <typename Typ>
bool ListaSasiedztwa<Typ>::InsertEdge(int index_V1, int index_V2, double w)
{
    Krawedz2<Typ> K;
    K.wsk=&L_wierzcholek[index_V1];
    K.wsk2=&L_wierzcholek[index_V2];
    K.waga=w; 
     
}
    

#endif
