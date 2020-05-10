#ifndef APPLICATION_H_DEFINED
#define APPLICATION_H_DEFINED    

#include "widget.h"
#include <vector>

class Application
{
protected:
    std::vector<Widget *> widgets;
public:   
    virtual void handle();
    void feltolt(Widget *w)
    {
        widgets.push_back(w);
    }
};


#endif