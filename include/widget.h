#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include "graphics.hpp"
#include "teglalap.h"
#include <string>

class Widget : protected teglalap
{
protected:
    bool fokuszban;
    
    Widget(int x, int y, int magassag, int szelesseg);

public:
    virtual void kirajzol() = 0;
    virtual void kezel(genv::event ev) = 0;
    virtual bool folotte(int egerX, int egerY);
};



#endif // WIDGET_H_INCLUDED
