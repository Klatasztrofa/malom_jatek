#include "csomopont.h"

using namespace genv;

Csomopont::Csomopont(int x, int y, int kx, int ky, std::function<void(int, int, Csomopont*)> vissz)
    : Widget(x, y, 35, 35), kx(kx), ky(ky), visszajelzes(vissz)
{
}

void Csomopont::kirajzol()
{
    gout << color(255, 0, 0);
    if (fokuszban)
    {
        gout << move_to(x, y) << line(sz, 0) << line(0, m) << line(-sz, 0) << line(0, -m);
    }
}

void Csomopont::kezel(genv::event ev)
{
    if (ev.button == btn_left)
    {
        visszajelzes(kx, ky, this);
    }
}