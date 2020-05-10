#include "szambeallito.h"
#include <sstream>
#include "teglalap.h"

using namespace std;
using namespace genv;

Szambeallito::Szambeallito(int x_, int y_, int m_, int sz_, int ertek_, int alsoHatar_, int felsoHatar_)
    : Widget(x_, y_, m_, sz_), ertek(ertek_), alsoHatar(alsoHatar_), felsoHatar(felsoHatar_),
      balGomb(x_,y_+m_*0.7,m_*0.3,sz_/2), jobbGomb(x_+sz_/2,y_+m_*0.7,m_*0.3,sz_/2)
{
}

void Szambeallito::ertekValtoztat(int p)
{

    if(ertek+p <= felsoHatar and ertek+p >= alsoHatar)
    {
        ertek+=p;
    }
    if (ertek+p>felsoHatar)
     {
          ertek=felsoHatar;
     }
    if (ertek+p<alsoHatar)
     {
         ertek=alsoHatar;
     }

}

void Szambeallito::kirajzol()
{
    stringstream ss;
    ss << ertek;
    string szam = ss.str();

    gout << color(255,182,193);
    gout << move_to(x,y) << box(sz,m);
    gout << color(25,25,112);
    gout << move_to(x+sz/2,y+(m-balGomb.m)/2) << genv::move(-gout.twidth("000")/2, gout.cdescent())
         << text(szam);
    gout << move_to(x,y+m*0.7) << line(sz,0);
    gout << move_to(x+sz/2,y+m*0.7) << line(0,m*0.3);
    gout << move_to(balGomb.x+balGomb.sz/2,balGomb.y+balGomb.m/2)
         << genv::move(-gout.twidth("-")/2, gout.cdescent())
         << text("-");
     gout << move_to(jobbGomb.x+jobbGomb.sz/2,jobbGomb.y+jobbGomb.m/2)
         << genv::move(-gout.twidth("+")/2, gout.cdescent())
         << text("+");
}

void Szambeallito::kezel(event ev)
{
    switch(ev.keycode)
    {
        case key_down: ertekValtoztat(-1); break;
        case key_up: ertekValtoztat(1); break;
        case key_pgdn: ertekValtoztat(-10); break;
        case key_pgup: ertekValtoztat(10); break;
    }

    if (ev.type ==ev_mouse && ev.button == btn_wheeldown)
    {
        ertekValtoztat(-1);
    }
    if (ev.type ==ev_mouse && ev.button == btn_wheelup)
    {
        ertekValtoztat(1);
    }
    if (ev.button == btn_left)
    {
        if (jobbGomb.benne(ev.pos_x,ev.pos_y))
        {
            ertekValtoztat(1);
        }
        if (balGomb.benne(ev.pos_x,ev.pos_y))
        {
            ertekValtoztat(-1);
        }
    }

}
