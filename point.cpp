#include "point.h"

void Point::move(float dx, float dy)
{
    if(_x+dx>0)
        _x+=dx;
    else
        _x=0.0;
    if(_y+dy>0)
        _y+=dy;
    else
        _y=0.0;
}
