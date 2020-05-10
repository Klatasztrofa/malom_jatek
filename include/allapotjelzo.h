#ifndef ALLAPOTJELZO_H_DEFINED
#define ALLAPOTJELZO_H_DEFINED

#include "widget.h"

class Allapotjelzo : public Widget
{
    std::string szoveg;

public:
    Allapotjelzo(int x, int y, std::string szoveg);

    void set_szoveg(std::string uj_szoveg) { szoveg = uj_szoveg; }
    void kirajzol();
    void kezel(genv::event ev);
};

#endif