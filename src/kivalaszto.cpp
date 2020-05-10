#include "kivalaszto.h"
#include <sstream>
#include "teglalap.h"
#include "graphics.hpp"

using namespace std;
using namespace genv;

Kivalaszto::Kivalaszto(int x_, int y_, int m_, int sz_,vector<string> elemek_, int db_)
    : Widget(x_, y_, m_, sz_),
      nyil(x_+sz_-(sz_/4),y_,m_*0.9,sz_/4), elem(x_,y_,m_,sz_),
      elemek(elemek_),kinyitva(false),kivalasztva(false),becsukva(false),db(db_),kivalasztott(0),kijelolt(-1)

{
}

void Kivalaszto::kirajzol()
{

    gout << color(253, 253, 150);
    gout << move_to(x,y) << box(sz,m);
    gout << color(95, 2, 146);
    gout << move_to(nyil.x,nyil.y) << line(0,m);
    gout << move_to(nyil.x+nyil.sz/2,nyil.y+nyil.m/2)
         << genv::move(-gout.twidth("v")/2, gout.cdescent())
         << text("v");
    gout << move_to(x+2,y+m/2+gout.cascent()/2)
         << text(elemek[kivalasztott]);

    if(kinyitva)
    {

        for(size_t i=0; i<db; i++)
        {
            gout << color(253, 253, 150);
            gout << move_to(x,y+m*(i+1)+2) << box(sz,m) ;
            gout << color(95, 2, 146);
            gout << move_to(x,y+m*(i+1)+2)  << line(sz,0);


            if(i==kijelolt)
            {
                gout << color(255,0,0);
                gout << move_to(x,y+m*(i+1)+2) << box(sz,m) ;
            }
        }

        for(size_t i=0; i<db; i++)
        {
            gout << color(95, 2, 146);
            gout << move_to(x,y+m*(i+1)+i+gout.cascent()) << text(elemek[i]);
        }
    }

}

void Kivalaszto::kezel(event ev)
{

   /* if (ev.type ==ev_mouse && ev.button == btn_wheeldown)
    {
        leg�rget;
    }
    if (ev.type ==ev_mouse && ev.button == btn_wheelup)
    {
        felg�rget;
    }*/
    if(ev.button == btn_left)
    {
        if (nyil.benne(ev.pos_x,ev.pos_y))
        {
            kinyitva=true;
            kivalasztva=false;
        }
        for(size_t i=1; i<=db; i++)
        {
            if(ev.pos_x>x and ev.pos_x < x+sz and ev.pos_y>y+m*i and ev.pos_y < y+m*(i+1)+i)
            {
                kijelolt=i-1;
            }
        }

    }
    if(ev.button == btn_right)
    {
        kivalasztott=kijelolt;
        kinyitva=false;

    }


}