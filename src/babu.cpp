#include "babu.h"

using namespace genv;
using namespace std;

Babu::Babu(int x, int y, bool egyikJatekose)
        :Widget(x,y,20,20), egyikJatekose(egyikJatekose), jatekban(false)
{
}

void Babu::kirajzol()
{
    if(egyikJatekose)
    {
        gout << color(255,0,250);
    }
    else
    {
        gout << color(0,255,255);
    }
    
    gout << move_to(x, y) << box(sz,m);
    
}

void Babu::mozgat(int x_, int y_, int kx_, int ky_)
{   
    x=x_;
    y=y_;
    kx=kx_;
    ky=ky_;
}

void Babu::kezel(event ev)
{
}