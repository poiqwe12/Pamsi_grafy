#include <iostream>
#include "graf.hh"
#include "graf2.hh"
int main()
{
    // for (int j = 7; j < 10; j++)
    // {
    //     Graf G(j);
    //     for (int i = 0; i < 4; i++)
    //     {
    //         G.Zeruj();
    //         G.Stworz_Graf(i);

    //         cout << G;
    //     }
    // }
    // {
    // Lista<int> a;
    // for (int i = 0; i < 10; ++i)
    // {
    //     a.Dodaj_Element(i,0);
    //     a.Show();
    //     cout<<endl;
    // }
    //  for (int i = 9; i > 0; --i)
    // {
    //     a.Usun_Element(i);
    //     a.Show();
    //     cout<<endl;
    // }
    // }
    double w =1.12;
    Krawedz<double> a;
    Wierzcholek<double> b;
    MacierzSasiedztwa<double> c(0);
   for (int i = 0; i < 10; ++i)
     {
     c.InsertVertex(7.2);
    c.InsertVertex(1.2);
     }
   c.InsertVertex(7.2);
    c.InsertVertex(1.2);
    c.InsertEdge(3,0,w);
    c.ShowTime();



    return 0;
}