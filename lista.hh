#include <iostream>
using namespace std;
template <typename Typ>
class Element
{

    Typ Zawartosc;
    Element<Typ> *Nastepny;
    Element<Typ> *Poprzedni;
    ///////////////////////////////////
  public:
    Element<Typ> *Get_Nastepny()
    {
        return Nastepny;
    }
    Element<Typ> *Get_Poprzedni()
    {
        return Poprzedni;
    }
    Typ &Get_Zawartosc()
    {
        return Zawartosc;
    }
    void Set_Zawartosc(Typ &zawar)
    {
        Zawartosc = zawar;
    }
    void Set_Nastepmny(Element<Typ> *wsk)
    {
        Nastepny = wsk;
    }
    void Set_Poprzedni(Element<Typ> *wsk)
    {
        Poprzedni = wsk;
    }
};
/////////////////////////////////////////////////////////////////
/*      Lista           */
/////////////////////////////////////////////////////////////////
template <typename Typ>
class Lista
{
    Element<Typ> *Start;
    int Ile;

  public:
    Lista();
    ~Lista();
    void Dodaj_Element(Typ T, int nr);
    Typ Usun_Element(int nr);
    void Show();
};

/*  Konstruktor */
template <typename Typ>
Lista<Typ>::Lista()
{
    Start = NULL;
    Ile = 0;
}

/*  Destruktor  */
template <typename Typ>
Lista<Typ>::~Lista()
{
    for(int i = Ile;i>0;--i)
    {
        Usun_Element(0);
    }
}

/*  Dodawanie elementów  */
template <typename Typ>
void Lista<Typ>::Dodaj_Element(Typ T, int nr)
{
    Element<Typ> *el = Start;
    Element<Typ> *nowy_el = new Element<Typ>();
    nowy_el->Set_Zawartosc(T);
    if(nr==0)
    {
    nowy_el->Set_Poprzedni(NULL);
    nowy_el->Set_Nastepmny(Start);
    if (Start != NULL)
    {
        Start->Set_Poprzedni(nowy_el);
    }
    Start = nowy_el;
    }
    else
    {
        if (nr > Ile)
        {
            cout << " za duzy nr do dodania \n";
        }
        else
        {
            for (int i = nr-1; i > 0; --i)
            {
                el = el->Get_Nastepny();
            }
            nowy_el->Set_Poprzedni(el);
            nowy_el->Set_Nastepmny(el->Get_Nastepny());
            if(el->Get_Nastepny()!=NULL)
            {
                el->Get_Nastepny()->Set_Poprzedni(nowy_el);
            }
            el->Set_Nastepmny(nowy_el);
        }

    }
    ++Ile;

}

/* Pokazanie zawartosci listy */
template <typename Typ>
void Lista<Typ>::Show()
{
    Element<Typ> *el = Start;
    while (el != NULL)
    {
        cout << " " << el->Get_Zawartosc();
        el = el->Get_Nastepny();
    }
}
/* Usun Element */
template <typename Typ>
Typ Lista<Typ>::Usun_Element(int nr)
{
    Element<Typ> *el = Start;
    Element<Typ> *el_poprzedni;
    Element<Typ> *el_nastepny;
    Typ T;
    if (nr == 0)
    {
        if(el!=NULL)
        {
           if (el->Get_Nastepny() == NULL) ///Sprawdzam czy nastepny element nie jest ostanim
            {
                Start=NULL;
                T = el->Get_Zawartosc();
                delete el;
            }
            else
            {
                  Start = el->Get_Nastepny();
                  Start->Set_Poprzedni(NULL);
                  T = el->Get_Zawartosc();
                delete el;
            } 
            --Ile;
        }
        else
        {
            cout<<"Lista pusta!!";
        }
    }
    else
    {

        if (nr >= Ile)
        {
            cout << " za duzy nr nie ma tyle el \n";
        }
        else
        {
            for (int i = nr; i > 0; --i)
            {
                el = el->Get_Nastepny();
            }
            if (el->Get_Nastepny() == NULL) ///Sprawdzam czy nastepny element nie jest ostanim
            {
                el_poprzedni = el->Get_Poprzedni();
                el_poprzedni->Set_Nastepmny(NULL);
                T = el->Get_Zawartosc();
                delete el;
            }
            else
            {
                el_poprzedni = el->Get_Poprzedni();
                el_nastepny = el->Get_Nastepny();

                el_nastepny->Set_Poprzedni(el_poprzedni);
                el_poprzedni->Set_Nastepmny(el_nastepny);

                T = el->Get_Zawartosc();
                delete el;
            }
            --Ile;
        }
    }
    return T;
}
