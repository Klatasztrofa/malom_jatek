#include "application.h"
#include "graphics.hpp"

using namespace genv;
using namespace std;

void Application::handle()
{
    for(Widget *w : widgets)
    {
        w->kirajzol();
    }
    gout << refresh;

    event ev;
    Widget *focus=nullptr;
    while(gin >> ev)
    {
        if(ev.button == btn_left)
        {
            for(Widget *w : widgets)
            {
                if(w->folotte(ev.pos_x, ev.pos_y))
                {
                    focus=w;
                }
            }
        }
        if (focus)
        {
            focus->kezel(ev);
        }
        for (Widget *w : widgets)
        {
            w->kirajzol();
        }
        gout << refresh;
    }


}