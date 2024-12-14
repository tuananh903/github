#include "pch.h"
#include "GachT.h"

void GachT::xoayhinh()
{
    switch (trangthai)
    {
    case 0: // Xoay t? tr?ng thái 0 sang tr?ng thái 1
        gach[2].x1 = gach[1].x1;
        gach[2].x2 = gach[1].x2;
        gach[2].y1 = gach[1].y1 - D;
        gach[2].y2 = gach[1].y2 - D;
        trangthai = 1;
        break;

    case 1: // Xoay t? tr?ng thái 1 sang tr?ng thái 2
        gach[3].x1 = gach[1].x1 + D;
        gach[3].x2 = gach[1].x2 + D;
        gach[3].y1 = gach[1].y1;
        gach[3].y2 = gach[1].y2;
        trangthai = 2;
        break;

    case 2: // Xoay t? tr?ng thái 2 sang tr?ng thái 3
        gach[0].x1 = gach[1].x1;
        gach[0].x2 = gach[1].x2;
        gach[0].y1 = gach[1].y1 + D;
        gach[0].y2 = gach[1].y2 + D;
        trangthai = 3;
        break;

    case 3: // Xoay t? tr?ng thái 3 tr? l?i tr?ng thái 0
        gach[2].x1 = gach[3].x1;
        gach[2].x2 = gach[3].x2;
        gach[2].y1 = gach[3].y1;
        gach[2].y2 = gach[3].y2;

        gach[3].x1 = gach[0].x1;
        gach[3].x2 = gach[0].x2;
        gach[3].y1 = gach[0].y1;
        gach[3].y2 = gach[0].y2;

        gach[0].y1 = gach[1].y1;
        gach[0].y2 = gach[1].y2;
        gach[0].x1 = gach[1].x1 - D;
        gach[0].x2 = gach[1].x2 - D;
        trangthai = 0;
        break;

    default:
        break;
    }
}

void GachT::traxoayhinh()
{
    // Xoay hình 3 l?n ?? quay tr? l?i tr?ng thái ban ??u
    xoayhinh();
    xoayhinh();
    xoayhinh();
}