#include "teglalap.h"

teglalap::teglalap(int x, int y,int m, int sz)
    :x(x),y(y),m(m),sz(sz)
{
}

bool teglalap::benne(int a, int b) const
{
    return a > x && a < x+sz && b > y && b < y+m;
}
