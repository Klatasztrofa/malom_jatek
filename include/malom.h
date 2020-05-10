#ifndef MALOM_H_DEFINE
#define MALOM_H_DEFINE

#include "application.h"
#include "babu.h"
#include "csomopont.h"
#include "allapotjelzo.h"

class Malom : public Application
{
    enum allapot
    {
        felrakas,
        kivalasztas,
        mozgatas,
        utes,
        vege
    };

    std::vector<std::vector<int>> tabla = 
    {{ 0,-1,-1, 0,-1,-1, 0 },
     {-1, 0,-1, 0,-1, 0,-1 },
     {-1,-1, 0, 0, 0,-1,-1 },
     { 0, 0, 0,-1, 0, 0, 0 },
     {-1,-1, 0, 0, 0,-1,-1 },
     {-1, 0,-1, 0,-1, 0,-1 },
     { 0,-1,-1, 0,-1,-1, 0 }}; 

    const int babuk_szama = 9;
    bool egyikJatekos;
    allapot allapot = felrakas;

    Allapotjelzo *all_jelzo;
    genv::canvas hatter;
    void handle();
    void hatterrajzol(int a);
    std::vector<Babu *> babuk;
    std::vector<Csomopont *> kattinthatok;
    Csomopont* kivalasztott_csp;

    void csomopont_visszajelzes(int x, int y, Csomopont *cs);
    void ujra();
    Babu* jatekon_kivuli_babu();
    int babuk_jatekban(bool egyik);
    Babu* babu_kereses(int x, int y);
    bool tud_e_mozogni(int x, int y);
    int osszeg(int x, int y, bool sor);
    bool malom_e(int x, int y);
    Csomopont* csp_kereses(int x, int y);

public:
    Malom();
    void futtatas();
};

#endif