#include "widget.h"

using namespace std;
using namespace genv;

Widget::Widget(int x_, int y_, int m_, int sz_)
    :teglalap(x_, y_, m_, sz_), fokuszban(false)
{
}

bool Widget::folotte(int egerX, int egerY)
{
    fokuszban = benne(egerX,egerY);
    return fokuszban;
}

