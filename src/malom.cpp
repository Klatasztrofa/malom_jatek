#include "malom.h"
#include <algorithm>

using namespace genv;
using namespace std;

Malom::Malom() : egyikJatekos(true)
{
    hatterrajzol(500);
    for (int i = 0; i < 9; i++)
    {
        Babu *b = new Babu(470,30+i*25,true);
        babuk.push_back(b);
        feltolt(b);

        b = new Babu(10,30+i*25,false);
        babuk.push_back(b);
        feltolt(b);
    }

    int a = 500;
    vector<float> aranyok = {0.1, 0.25, 0.4, 0.5, 0.6, 0.75, 0.9};
    for (int x = 0; x < 7; x++)
    {
        for (int y = 0; y < 7; y++)
        {
            if (tabla[x][y] == 0)
            {
                Csomopont *cs = new Csomopont(a*aranyok[x]-18, a*aranyok[y]-18, x, y, 
                    [=](int x, int y) { csomopont_visszajelzes(x, y); });
                    
                kattinthatok.push_back(cs);
                widgets.push_back(cs);
            }
        }
    }
}

Babu* Malom::jatekon_kivuli_babu()
{   
    auto talalat = std::find_if(babuk.begin(), babuk.end(), [=](Babu *b)
    {
        return b->ove_e(egyikJatekos) && !b->jatekban_e();
    });

    if (talalat != babuk.end())
    {
        return *talalat;
    }
    else
    {
        return nullptr;
    }
}

int Malom::babuk_jatekban(bool egyik)
{
    int db = std::count_if(babuk.begin(), babuk.end(), [egyik](Babu *b)
    {
        return b->ove_e(egyik) && b->jatekban_e();
    });
    return db;
}

void Malom::csomopont_visszajelzes(int x, int y)
{
    int a = 500;
    vector<float> aranyok = {0.1, 0.25, 0.4, 0.5, 0.6, 0.75, 0.9};

    if (allapot == felrakas && 
        (babuk_jatekban(true) < 9 || babuk_jatekban(false) < 9))
    {
        Babu *b = jatekon_kivuli_babu();
        if (tabla[x][y] == 0)
        {
            if (egyikJatekos)
            {
                tabla[x][y] = 1;
            }
            else
            {
                tabla[x][y] = 2;
            }
            b->mozgat(a*aranyok[x]-10, a*aranyok[y]-10);
            b->jatekba_helyez();
            egyikJatekos = !egyikJatekos;
        }
    }
    else
    {
        allapot = kivalasztas;
    }

    // kivalasztas
    // mozgatas
    
}


void Malom::hatterrajzol(int a)
{
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    hatter.open(a,a);
    hatter << color(255,253,208) << move_to(0,0) << box(a,a);
    hatter << color(75,45,42);
    
    int betolas = a*0.1;
    int hossz = a*0.8;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);
    
    betolas = a*0.25;
    hossz = a*0.5;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);

    betolas = a*0.4;
    hossz = a*0.2;
    hatter << move_to(betolas,betolas) << box(hossz, 5) << box(-5,hossz) << box(-hossz,-5) << box(5, -hossz);

    betolas = a*0.1;
    hossz = a*0.3;
    hatter << move_to(a*0.5-2,betolas) << box(5, hossz) 
           << move_to(a*0.5-2,a-betolas) << box(5,-hossz)
           << move_to(a-betolas-5,a*0.5-2) << box(-hossz, 5)
           << move_to(betolas,a*0.5-2) << box(hossz, 5); 
}


void Malom::handle()
{
    gout << stamp(hatter,0,0);

    for(Widget *w : widgets)
    {
        w->kirajzol();
    }
    gout << refresh;

    event ev;
    Widget *focus=nullptr;
    while(gin >> ev)
    {
        for(Widget *w : widgets)
        {
            if(w->folotte(ev.pos_x, ev.pos_y))
            {
                if(ev.button == btn_left)
                {
                    focus=w;
                }
            }
        }
        if (focus)
        {
            focus->kezel(ev);
        }
        gout << stamp(hatter, 0, 0);
        for (Widget *w : widgets)
        {
            w->kirajzol();
        }

        gout << color(255, 0 ,0);
        for (Csomopont *cs : kattinthatok)
        {
            cs->kirajzol();
        }
        gout << refresh;
    }
}

void Malom::futtatas()
{
    gout.open(500, 500);
    handle();
}