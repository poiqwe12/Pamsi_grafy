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
        char *a=(char*)"dane.txt";

    ListaSasiedztwa<double> v(0,1000);
    v.Inicjuj(0);
    //v.WczytajZPliku(a);
    //v.ShowTime();
       cout<<"aa1";
    
    algorytm_Dijkstery(v);  
       cout<<"aa2";
    while(1)
    {
        char a;
        cin>>a;
        if(a=='a') break;
    }
MacierzSasiedztwa<double> c(1,1000);
  //  char *a=(char*)"dane.txt";
    //c.WczytajZPliku(a);
    c.Inicjuj(0);
    //c.ShowTime();
    cout<<endl<<endl;
    algorytm_Dijkstery(c);
    //c.ShowTime();


    return 0;
}