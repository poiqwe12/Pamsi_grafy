#ifndef GRAF_HH
#define GRAF_HH

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "lista.hh"
#include <fstream>
using namespace std;

template <typename Typ>
struct Wierzcholek2
{
    Typ zawartosc;
    int index;
};
template <typename Typ>
struct Krawedz2
{
    double waga;
    Wierzcholek2<Typ> *wsk;
    Wierzcholek2<Typ> *wsk2;
};

template <typename Typ>
class ListaSasiedztwa
{
    Lista<Wierzcholek2<Typ> > L_wierzcholek;
    Lista<Krawedz2<Typ> > L_krawedz;
    Lista<Krawedz2<Typ> *> *L_incydencji;
    int value_E, value_V, start_V;
    int max_V;
    bool Skierowany;

  public:
    ListaSasiedztwa(bool s, int V);
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
    template <typename T>
    void friend algorytm_Dijkstery(ListaSasiedztwa<T> &M);

};
/* Konstruktor */
template <typename Typ>
ListaSasiedztwa<Typ>::ListaSasiedztwa(bool s, int V)
{
    Skierowany = s;
    value_E = 0;
    start_V = 0;
    max_V = 2000;
     double a;
    for (int i = 0; i < V; ++i)
    {
        InsertVertex(a);
    }
    value_V = V;
    L_incydencji = new Lista<Krawedz2<Typ> *>[max_V];
}
/* Dekstruktor */
template <typename Typ>
ListaSasiedztwa<Typ>::~ListaSasiedztwa()
{
    delete[] L_incydencji;
}
/* Dodawanie wierzcholka */
template <typename Typ>
bool ListaSasiedztwa<Typ>::InsertVertex(Typ Objekt)
{
    Wierzcholek2<Typ> wierz; // Tworzy wierzcholek daje mu kolejny index
                             // oraz dodaje go do listy wierzchołków
    wierz.index = value_V++;
    wierz.zawartosc = Objekt;
    
    //cout<<" val: "<<value_V<<endl;
    //cout<<"L_wierzcholek: "<<L_wierzcholek.Ile<<endl;
        L_wierzcholek.Dodaj_Element(wierz, L_wierzcholek.Ile);
    
    return true;
}
/* Dodawanie krawedzi */
template <typename Typ>
bool ListaSasiedztwa<Typ>::InsertEdge(int index_V1, int index_V2, double w)
{
    Krawedz2<Typ> *K = new Krawedz2<Typ>;
    K->wsk = &L_wierzcholek[index_V1];
    K->wsk2 = &L_wierzcholek[index_V2];
    K->waga = w;
    L_krawedz.Dodaj_Element(*K, 0);

    if (Skierowany)
    {
        L_incydencji[index_V1].Dodaj_Element(K, 0);
    }
    else
    {
        L_incydencji[index_V1].Dodaj_Element(K, 0);
        L_incydencji[index_V2].Dodaj_Element(K, 0);
    }
}

template <typename Typ>
void ListaSasiedztwa<Typ>::Inicjuj(int index)
{
    bool tab[max_V][max_V];
    for(int i =0;i<max_V;++i)
    {
        for(int j =0;j<max_V;++j)
        {
            tab[i][j]=0;
        }
    }
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
    bool ok =1;
    while (E > 0)
    {
        k = rand() % value_V; /// Losowanie miejsca na krawedz
        l = rand() % value_V;
        m = rand() % value_V + 1;
        if (l != k)
        {
            if (tab[l][k] == false)
            {   
                tab[l][k] =true;
                InsertEdge(l, k, m);
                E--;
            }
        }
    }

    
    
}

/* Wyswietlanie reprezantacji grafu */
template <typename Typ>
void ListaSasiedztwa<Typ>::ShowTime()
{
    L_wierzcholek.Show();
    cout<<endl<<endl;
    for(int i =0;i<max_V;++i)
    {
        cout<<i<<"|  ";
        L_incydencji[i].Show();
        cout<<endl;
    }

}
template <typename Typ>
std::ostream &operator<<(std::ostream &stream, Wierzcholek2<Typ> &W)
{
    stream << W.index << " " << W.zawartosc << " ";
    return stream;
}
template <typename Typ>
std::ostream &operator<<(std::ostream &stream, Krawedz2<Typ> *W )
{
    stream << W->wsk2->index<<"|";
    return stream;
}
template <typename Typ>
void algorytm_Dijkstery_zapisz_do_pliku(ListaSasiedztwa<Typ> &M)
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
        for (int k = 0; k < M.L_incydencji[korzen].Ile; ++k) // lece po wszystkich wierzcholkach
        {     
                if (!zbior_S[ M.L_incydencji[korzen][k]->wsk2->index]) // Jezeli nalezy do zbioru   Q
                {
                    if (koszty_dojscia[ M.L_incydencji[korzen][k]->wsk2->index] > koszty_dojscia[korzen] + ( M.L_incydencji[korzen][k]->waga))
                    {
                        koszty_dojscia[ M.L_incydencji[korzen][k]->wsk2->index] = koszty_dojscia[korzen] +  M.L_incydencji[korzen][k]->waga;
                        poprzednicy[ M.L_incydencji[korzen][k]->wsk2->index] = korzen;
                    }
                }           
        }
    }
 std::fstream plik;
    plik.open( "wynik_lista.txt", std::ios::in | std::ios::out );
    if( plik.good() == true )
    {
    plik << "------------------------------" << endl;
    int dl = 0;
    for (int i = 0; i < M.value_V; ++i)
    {
        dl = 0;
        for (int q = i; q >= 0; q = poprzednicy[q])
        {
            dl++;
            Stos.Dodaj_Element(q, 0);
        }
        plik << "Nr wierz: " << i << "|\tKoszt dojscia: ";
        if (koszty_dojscia[i] != nieszkonczonosc)
        {
            plik  << koszty_dojscia[i] << "\t\tkolejnosc ";
        }
        else
        {
            plik << "inf" << "\t\tkolejnosc: ";
        }
        for (int s = dl; dl > 0; --dl)
        {
            plik << "" << Stos.Usun_Element(0) << "  ";
        }
        plik<<endl;
        
    }
            plik.close();

    }
}
/* Wczytywanie danych z pliku */
template <typename Typ>
bool ListaSasiedztwa<Typ>::WczytajZPliku(char *nazwa_pliku)
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




template <typename Typ>
void algorytm_Dijkstery(ListaSasiedztwa<Typ> &M)
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
        for (int k = 0; k < M.L_incydencji[korzen].Ile; ++k) // lece po wszystkich wierzcholkach
        {     
                if (!zbior_S[ M.L_incydencji[korzen][k]->wsk2->index]) // Jezeli nalezy do zbioru   Q
                {
                    if (koszty_dojscia[ M.L_incydencji[korzen][k]->wsk2->index] > koszty_dojscia[korzen] + ( M.L_incydencji[korzen][k]->waga))
                    {
                        koszty_dojscia[ M.L_incydencji[korzen][k]->wsk2->index] = koszty_dojscia[korzen] +  M.L_incydencji[korzen][k]->waga;
                        poprzednicy[ M.L_incydencji[korzen][k]->wsk2->index] = korzen;
                    }
                }           
        }
    }
}
#endif
