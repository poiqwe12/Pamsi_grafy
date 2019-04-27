#include <iostream>

#include "graf.hh"

int main()
{
    for (int j = 7; j < 10; j++)
    {
        Graf G(j);
        for (int i = 0; i < 4; i++)
        {
            G.Zeruj();
            G.Stworz_Graf(i);

            cout << G;
        }
    }
    return 0;
}