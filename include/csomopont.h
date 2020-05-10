#ifndef CSOMOPONT_H_DEFINE
#define CSOMOPONT_H_DEFINE

#include "widget.h"
#include <functional>
#include <set>

class Csomopont : public Widget
{   
    int kx,ky;
    std::set<Csomopont*> szomszedok;
    std::function<void(int, int, Csomopont*)> visszajelzes;

public:
    Csomopont(int x, int y, int kx, int ky, std::function<void(int, int, Csomopont*)> vissz);

    int get_kx(){ return kx; }
    int get_ky(){ return ky; } 
    void szomszed_hozzaad(Csomopont* cs) { szomszedok.insert(cs); cs->szomszedok.insert(this); }
    std::set<Csomopont*> get_szomszedok() { return szomszedok; }
    bool szomszedja_e(Csomopont *cs) { return szomszedok.find(cs) != szomszedok.end(); }

    void kirajzol();
    void kezel(genv::event ev);
};



#endif