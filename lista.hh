#include <iostream>

template<typename Typ>
class Element
{
   Typ T;
   *Element Nastepny;
   *Element Poprzedni;
};


template <typename typ>
class Lista 
{
    *Element<typ> Start;
};