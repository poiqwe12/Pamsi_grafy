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
    int max_V,start_V;                             // Maxmalna ilosc bez alkowania pamieci
    bool Skierowany;                       // Czy graf jest skierowanyc czy nie
    Lista<Wierzcholek<Typ> > L_Wierzcholek; // Lista przechowujaca wierzcholki

  public:
    MacierzSasiedztwa(bool S);
    ~MacierzSasiedztwa();
    void IncidentEdges(int index_V);                       // Literowanie poloczonych wierzchołków
    bool AreAdjacent(int index_V1, int index_V2);          // CZy dwa wierzchołki sa połaczone
    bool InsertVertex(Typ Obiekt);                         // Dodaje wierzchołek o zawartosci obiekt
    bool InsertEdge(int index_V1, int index_V2, double w); // Dodaje krawedz o wadze w
    bool RemoveVertex(int index_V);                        // Usuwa wierzchołek i jego krawedzie
    bool RemoveEdge(int index_V1, int index_V2);           // Usuwa krawedz
    void ShowTime();                                       // Wyswietla macierz sasiedztwa
    bool WczytajZPliku(char *nazwa_plik);
};

/* Konstruktor */
template <typename Typ>
MacierzSasiedztwa<Typ>::MacierzSasiedztwa(bool S)
{
    max_V = 15;
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
    if (Skierowany)                     // Jezeli graf jest skierowany to zwalniam pamiec
        for (int i = 0; i < max_V; i++) // z całej macierzy
        {
            for (int j = 0; j < max_V; j++)
            {
                delete tab[i][j];
            }
        }
    else
    {
        for (int i = 0; i < max_V; i++)     // Jezeli graf jest nieskierowany to zwalniam pamiec
        {                                   // Z polowy macierzy bo druga polowa wskazuje na to samo
            for (int j = i; j < max_V; j++) // a dwa razy nie moge zwolnic pamieci
            {
                delete tab[i][j];
            }
        }
    }
    for (int i = 0; i < max_V; ++i)
    {
        delete[] tab[i];
    }
    delete[] tab;
}
/* Dodawanie wierzcholka */
template <typename Typ>
bool MacierzSasiedztwa<Typ>::InsertVertex(Typ Objekt)
{
    Wierzcholek<Typ> wierz; // Tworzy wierzcholek daje mu kolejny index
                            // oraz dodaje go do listy wierzchołków
    wierz.index = value_V++;
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
        tab[index_V1][index_V2] = new Krawedz<Typ>;                    // Tworzenie krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V1]); // Dodanie łączących wierzchołków do krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V2]);
        (tab[index_V1][index_V2])->waga = w;
    }
    else // Procedura dla grafu nieskierowanego
    {
        tab[index_V1][index_V2] = new Krawedz<Typ>;                    // Tworzenie krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V1]); // Dodanie łączących wierzchołków do krawedzi
        (tab[index_V1][index_V2])->wsk_1 = &(L_Wierzcholek[index_V2]); // Jak jest nieskierowany dodaje ten sam wskaznik
        tab[index_V2][index_V1] = tab[index_V1][index_V2];             // krawedzi do drugiej pozycji w macierzy
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
        cout << setw(5) << i;
    }
    cout << endl
         << endl;
    for (int i = 0; i < max_V; i++)
    {
        cout << setw(2) << i << "|";
        for (int j = 0; j < max_V; j++)
        {
            if (tab[i][j] == NULL)
            {
                cout << setw(5) << "NULL";
            }
            else
            {
                cout << setw(5) << (tab[i][j])->waga;
            }
        }
        cout << endl;
    }
}
/* Wczytywanie danych z pliku */
template<typename Typ>
bool MacierzSasiedztwa<Typ>::WczytajZPliku(char *nazwa_pliku)
{
    /*
    fstream plik;
    plik.open(nazwa_pliku,std::ios::in|std::ios::out);
    if(plik.good()==true)
    {
        //Typ a;
        plik>>value_E>>value_V>>start_V;
        for(int i =0;i<value_V;++i)
        {
           // InsertVertex(a);
        }

        plik.close();
    }
    */
    return true;
}




/* Przeciazenie operatora wyswietlania dla Wierzcholka */
template<typename Typ>
std::ostream &operator<<(std::ostream &stream, Wierzcholek<Typ> &W)
{
    stream<<W.index;
    return stream;
}





#endif
