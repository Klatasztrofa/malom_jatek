#ifndef SZAMBEALLITO_H_INCLUDED
#define SZAMBEALLITO_H_INCLUDED

#include "widget.h"

class Szambeallito : public Widget
{
    int ertek;
    int alsoHatar;
    int felsoHatar;

    teglalap balGomb;
    teglalap jobbGomb;

    void ertekValtoztat(int p);

public:
    Szambeallito(int x, int y, int magassag, int szelesseg, int ertek, int alsoHatar, int felsoHatar);

    void kirajzol() override;
    void kezel(genv::event ev) override;
};


#endif // SZAMBEALLITO_H_INCLUDED
