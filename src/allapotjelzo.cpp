#include "allapotjelzo.h"

using namespace std;
using namespace genv;

Allapotjelzo::Allapotjelzo(int x, int y, std::string szoveg)
    : Widget(x, y, gout.cascent()+gout.cdescent(), gout.twidth(szoveg)), szoveg(szoveg)
{
}

void Allapotjelzo::kirajzol()
{
    gout << color(0, 0, 0) << move_to(x-gout.twidth(szoveg)/2, y+gout.cascent()) << text(szoveg);
}

void Allapotjelzo::kezel(event ev)
{

}