#pragma once
#include "Hcn.h"
class Hcnmau :
    public Hcn
{
public:
    int r, g, b;
    Hcnmau() :Hcn()
    {
        r = 500;
        g =900;
        b =250;
    }
    Hcnmau(int mx1, int my1, int mx2, int my2, int mr, int mg, int mb) :Hcn(mx1, my1, mx2, my2)
    {
        r = mr;
        g = mg;
        b = mb;
    }
    void vehinh(CClientDC* pdc);
};
