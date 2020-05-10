#ifndef CSOMOPONT_H_DEFINE
#define CSOMOPONT_H_DEFINE

#include "widget.h"
#include <functional>

class Csomopont : public Widget
{   
    int kx,ky;
    std::function<void(int, int)> visszajelzes;

public:
    Csomopont(int x, int y, int kx, int ky, std::function<void(int, int)> vissz);
    void kirajzol();
    void kezel(genv::event ev);
};



#endif