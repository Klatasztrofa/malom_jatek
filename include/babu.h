#ifndef BABU_H_DEFINE
#define BABU_H_DEFINE

#include "widget.h"

class Babu : public Widget
{   
    bool egyikJatekose;
    bool jatekban;
    int kx, ky;

public:   
    Babu(int x, int y, bool egyikJatekose);

    void jatekba_helyez() { jatekban = true; }
    void kiut() { jatekban = false; }
    bool jatekban_e() { return jatekban; }
    bool ove_e(bool egyik) { return egyik == egyikJatekose; }
    int get_kx(){return kx; }
    int get_ky(){return ky; }  
  

    void kirajzol();
    void mozgat(int x, int y, int kx, int ky);
    void kezel(genv::event ev);

};


#endif