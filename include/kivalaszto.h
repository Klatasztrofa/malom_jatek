#ifndef KIVALASZTO_H_INCLUDED
#define KIVALASZTO_H_INCLUDED

#include "widget.h"
#include <vector>
#include <string>
#include "graphics.hpp"

class Kivalaszto : public Widget
{
protected:
    std::vector<std::string> elemek;
    int db;
    int kivalasztott;
    int kijelolt;
    teglalap nyil;
    teglalap elem;
    bool kivalasztva;
    bool kinyitva;
    bool becsukva;

public:
    Kivalaszto(int x, int y, int magassag, int szelesseg,std::vector<std::string> elemek, int db);

    void kirajzol() override;
    void kezel(genv::event ev) override;
};


#endif // KIVALASZTO_H_INCLUDED
