#include <iostream>
#include "graf.hh"
#include "graf2.hh"
#include <time.h>
#include <fstream>

void badania();

int main()
{
    char *b="dane.txt";
    char a='a';
    MacierzSasiedztwa<double> v(1, 0);
    // v.~ListaSasiedztwa();
    // ListaSasiedztwa<double> vb(0,5);
     v.Inicjuj(3);
    cout << "a";

    while (a != '3')
    {
        cout << " \n --Grafy--  \n";
        cout << "  Menu:      \n";
        cout << "  1- Wykonaj badania \n";
        cout << "  2- Wykonaj algorytm dla grafu z pliku \n";
        cout << "  3- Koniec\n";
        cout << "  Twoj wybor:";
        cin >> a;
        switch (a)
        {
        case '1':
            cout << "\n  aad\n";
            badania();
            break;
        case '2':
            cout << "\n  ---\n";

           
            v.WczytajZPliku(b);
            v.ShowTime();
            algorytm_Dijkstery_zapisz_do_pliku(v);
            cout << "    ";
            break;
        case '3':
            cout << " \n Koniec";
            break;
        default:
            break;
        }
    }

    return 0;
}

void badania()
{
    char *tab[4] = {
        (char *)"100%",
        (char *)" 75% ",
        (char *)" 50% ",
        (char *)" 25% ",
    };
    double srednia, wartosc_min = 1000, wartosc_max = 0;
    srednia = 0;
    int tab2[5] = {10, 50, 100, 500, 1000};
    for (int g = 0; g < 5; ++g)
    {
        for (int i = 0; i < 4; ++i)
        {
            wartosc_min = 1000;
            wartosc_max = 0;
            srednia = 0;
            for (int j = 0; j < 100; ++j)
            {
                clock_t start, stop;
                ListaSasiedztwa<double> M(1, tab2[g]);
                M.Inicjuj(i);
                start = clock();
                algorytm_Dijkstery(M);
                stop = clock();
                double czas = (double)(stop - start) / CLOCKS_PER_SEC;
                srednia = srednia + czas;
                if (wartosc_max < czas)
                    wartosc_max = czas;
                if (wartosc_min > czas)
                    wartosc_min = czas;

                cout << czas << endl;
            }
            std::ofstream plik("Lista.csv", std::ios_base::app);
            if (plik.good() == true)
            {
                if (i == 0)
                    plik << "Graf " << tab2[g] << " wierzcholkow" << std::endl;
                if (i == 0)
                    plik << " Gestosc grafu \t średnia \t min \t max" << endl;
                plik << tab[i] << "\t" << srednia / 100 << "\t" << wartosc_min << "\t" << wartosc_max << endl;
                plik.close();
            }
        }
    }
}
