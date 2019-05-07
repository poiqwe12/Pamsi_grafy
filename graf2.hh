#ifndef GRAF2_HH
#define GRAF2_HH

#include <fstream>
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
    int max_V, start_V;                    // Maxmalna ilosc bez alkowania pamieci
    bool Skierowany;                       // Czy graf jest skierowanyc czy nie
    Lista<Wierzcholek<Typ> > L_Wierzcholek; // Lista przechowujaca wierzcholki

  public:
    MacierzSasiedztwa(bool S, int ile_wierz);
    ~MacierzSasiedztwa();
    void IncidentEdges(int index_V);                       // Literowanie poloczonych wierzchołków
    bool AreAdjacent(int index_V1, int index_V2);          // CZy dwa wierzchołki sa połaczone
    bool InsertVertex(Typ Obiekt);                         // Dodaje wierzchołek o zawartosci obiekt
    bool InsertEdge(int index_V1, int index_V2, double w); // Dodaje krawedz o wadze w
    bool RemoveVertex(int index_V);                        // Usuwa wierzchołek i jego krawedzie
    bool RemoveEdge(int index_V1, int index_V2);           // Usuwa krawedz
    void ShowTime();                                       // Wyswietla macierz sasiedztwa
    bool WczytajZPliku(char *nazwa_plik);                  // Wczytuje graf z pliku
    void Inicjuj(int index);                               // Inicjuje graf o okreslonej gestosci
    template <typename T>
    void friend algorytm_Dijkstery(MacierzSasiedztwa<T> &M);
};

/* Konstruktor */
template <typename Typ>
MacierzSasiedztwa<Typ>::MacierzSasiedztwa(bool S, int ile_wierz)
{
    max_V = 2000;
    value_V = 0;
    Skierowany = S;
    start_V = 0;
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
    double a;
    for (int i = 0; i < ile_wierz; ++i)
    {
        InsertVertex(a);
    }
    value_V = ile_wierz;
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
/* Swap dwoch elementow */
void Swap(int &T1, int &T2)
{
    int T3 = T1;
    T1 = T2;
    T2 = T3;
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
template <typename Typ>
bool MacierzSasiedztwa<Typ>::WczytajZPliku(char *nazwa_pliku)
{
    double a; // Cos co przechowuje wierzchołek
    int V, E, start;
    int krawedz_1, krawedz_2, waga_s;
    fstream plik;
    plik.open(nazwa_pliku, std::ios::in | std::ios::out);
    if (plik.good() == true)
    {
        plik >> E >> V >> start;
        //cout << " " << E << "   " << V << " " << start;
        for (int i = 0; i < V; ++i)
        {
            InsertVertex(a); // Dodawanie wierzchołków do listy
        }
        for (int i = 0; i < E; ++i) // Dodawanie krawedzi do macierzy
        {
            plik >> krawedz_1 >> krawedz_2 >> waga_s;
            InsertEdge(krawedz_1, krawedz_2, waga_s);
        }
        value_E = E;
        value_V = V;
        start_V = start;
        //cout << endl;
        // L_Wierzcholek.Show();
        plik.close();
    }
    return true;
}

/* Przeciazenie operatora wyswietlania dla Wierzcholka */
template <typename Typ>
std::ostream &operator<<(std::ostream &stream, Wierzcholek<Typ> &W)
{
    stream << W.index;
    return stream;
}

/* Inicjajcja grafu */
template <typename Typ>
void MacierzSasiedztwa<Typ>::Inicjuj(int index)
{
    srand(time(NULL));
    int E;
    int k, l, m;
    switch (index)
    {
    case 0:
        value_E = value_V * (value_V - 1) ;
        break;
    case 1:
        value_E = value_V * (value_V - 1) /2;
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
    if(Skierowany)   
    {
        E = value_E; /// Ilosc krawedzi wyznaczona z gestosci
    }
    else
    {
        E=value_E/2;
    }
    while (E > 0)
    {
        k = rand() % value_V; /// Losowanie miejsca na krawedz
        l = rand() % value_V;
        m = rand() % value_V + 1;
        if (l != k)
        {
            if (tab[l][k] == NULL)
            {
                InsertEdge(l, k, m);
                E--;
            }
        }
    }
}
/* Kopcowanie */
void Shift_Down(int *koszty, int *kopiec, int *pol_wierz, int index_parent, int size)
{
    int index_L = 2 * index_parent + 1;
    int index_R = 2 * index_parent + 2;
    int index_Swap = index_parent;

    if (index_R < size)
    {
        if (koszty[pol_wierz[index_R]] < koszty[pol_wierz[index_L]])
        {
            index_Swap = index_R;
        }
        else
        {
            index_Swap = index_L;
        }
    }
    else
    {
        if (index_L < size)
            index_Swap = index_L;
    }

    if (koszty[pol_wierz[index_Swap]] < koszty[pol_wierz[index_parent]])
    {
        Swap(kopiec[index_Swap], kopiec[index_parent]);
        Swap(pol_wierz[index_Swap], pol_wierz[index_parent]);
        Shift_Down(koszty, kopiec, pol_wierz, index_Swap, size);
    }
}

/*  Algorytm Dijkstery   */
template <typename Typ>
void algorytm_Dijkstery(MacierzSasiedztwa<Typ> &M)
{
    Lista<int> Stos;               // Potrzebny do wyswietlania
    bool zbior_S[M.value_V];       // Jesli true to nalezy do Q, jesli false to do S
    int koszty_dojscia[M.value_V]; // wiadomo
    int poprzednicy[M.value_V];    // Przechowouje index poprzednika wierzcholka
                                   // o najmniejszym koszcie, jezelirowna sie -1 to nie ma drogi
    int dlugosc = M.value_V;
    int nieszkonczonosc = 10000000;
    int korzen, cos; // inne mao znaczace zmienne
    for (int i = 0; i < M.value_V; ++i)
    {
        zbior_S[i] = false;
        koszty_dojscia[i] = nieszkonczonosc;
        poprzednicy[i] = -1;
    }
    koszty_dojscia[M.start_V] = 0; // Wierzchołek startowy ma koszt dojscia 0
    for (int i = 0; i < M.value_V; ++i)
    {
        cos = nieszkonczonosc;
        for (int q = 0; q < M.value_V; q++)
        {
            if ((zbior_S[q] == false) && (koszty_dojscia[q] < cos))
            {
                korzen = q;
                cos = koszty_dojscia[q];
            }
        }
        zbior_S[korzen] = true;
        for (int k = 0; k < M.value_V; ++k) // lece po wszystkich wierzcholkach
        {
            if (M.tab[korzen][k] != NULL) // jezeli jest sasiadem
            {
                if (!zbior_S[k]) // Jezeli nalezy do zbioru   Q
                {
                    if (koszty_dojscia[k] > (koszty_dojscia[korzen] + (M.tab[korzen][k])->waga))
                    {
                        koszty_dojscia[k] = koszty_dojscia[korzen] + (M.tab[korzen][k])->waga;
                        poprzednicy[k] = korzen;
                    }
                }
            }
        }
    }
    cout << "------------------------------" << endl;
    int dl = 0;
    for (int i = 0; i < M.value_V; ++i)
    {
        dl = 0;
        for (int q = i; q >= 0; q = poprzednicy[q])
        {
            dl++;
            Stos.Dodaj_Element(q, 0);
        }
        cout << "Nr wierz: " << i << "|\tKoszt dojscia: ";
        if (koszty_dojscia[i] != nieszkonczonosc)
        {
            cout  << koszty_dojscia[i] << "\t\tkolejnosc ";
        }
        else
        {
            cout << "inf" << "\t\tkolejnosc: ";
        }
        for (int s = dl; dl > 0; --dl)
        {
            cout << "" << Stos.Usun_Element(0) << "  ";
        }
        cout<<endl;
        
    }
}

#endif
