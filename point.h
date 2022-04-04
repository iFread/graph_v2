#ifndef POINT_H
#define POINT_H

#include <cmath>

 const float ftolerance =0.001f;
class Point
{
    float _x;
    float _y;
    // float_z;
public:
    Point()
    {_x=NAN;
      _y=NAN;    }
    Point (int x,int y):_x(x),_y(y){}
    Point (float x, float y):_x{x},_y{y}{}
   Point (const Point &p):_x(p.x()),_y(p.y()){}
    bool isEqual(const Point &p) const
    {
      if(fabs(_x-p._x)<ftolerance&&(fabs(_y-p._y)<ftolerance))
          return true;
      return false;
    }
    bool isValid()
    {
      if(_x==_x &&_y==_y)
          return true;
      return false;
    }
    float x() const {return _x;}
    float y()const {return _y;}
void x(float x)
{
   _x=x;
}
void y(float x)
{
_y=x;
}

    bool operator<(const Point &p)
    {
       if((_x<p._x) ||((_x==p._x)&& (_y<p._y )))
           return true;
       return false;
    }

    bool operator>(const Point &p) {return !((*this<p)&&isEqual(p));}
 void move(float dx,float dy); // изменение положения точки
 Point operator-(const Point &p) const
 {
     return {_x-p._x,_y-p._y};
 }
 Point operator+(const Point &p) const
 {
     return {_x+p._x,_y+p._y};
 }
};


#endif // POINT_H
