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
Point Point::operator*(const Point &p) const
{ if(p.isValid()&&isValid())
       return Point{this->_x*p._x,this->_y*p._y};
    return {};
}

Point Point::operator/(const Point &p) const
{
  if(!(p.isValid() && isValid()))
         return {};

   if(p._x!=0 && p._y!=0)
       return {this->_x/p._x,this->_y/p._y};
   return {};
}

Point Point::operator*(float f) const
{
    if(isValid())
        return {_x*f,_y*f};
    return {};
}

Point Point::operator/(float f) const
{
   if(isValid()&&(f>ftolerance))
       return {_x/f,_y/f};
   return {};
}
