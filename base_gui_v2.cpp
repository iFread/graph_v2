#include "base_gui_v2.h"
#include <iostream>
namespace Graph {


Shape::Shape()
{

}

void Shape::draw() const
{
    Fl_Color old=fl_color();
    fl_color(lcolor.as_int());
    fl_line_style(ls.style(),ls.width());
draw_lines();
fl_color(old);
fl_line_style(0);
}
Point Shape::point(int i) const
{
    if(i<0) return Point{}; // невалидная точка
   if(i<points.size())
    return points[i];
  else return points[points.size()-1];
}
Point& Shape::point(int i)
{ // уязвимость!!! если у фигуры нет точек,
    // нужно исключить фигуру без точек
    //if(i<0) return;// Point{}; // невалидная точка
   if(i<points.size())
    return points[i];
  else return points[points.size()-1];

}

void Shape::draw_lines() const
{
    if(color().visible && 1<points.size())
        for(unsigned i=1;i<points.size();++i)
        { //if(points[i-1].x()>0&&points[i-1].y()>0)
            fl_line(points[i-1].x(),points[i-1].y(),points[i].x(),points[i].y());
        }
}
// фигура состоит из граней и вершин, переносим по граням ?
void Shape::move(float dx, float dy)
{
   for(unsigned i=0; i<points.size();++i)
   {
      points[i].move(dx,dy);
   }
}
int Shape::num_of_point() const
{
    return points.size();
}

void Shape::set_point(int i, Point p)
{
   if(i<num_of_point())
    points[i]=p;
}

void Shape::clear()
{
  points.clear();
}


// Линия, бесконечная прямая
Line::Line(Point p1,Point p2)
{
  if(p1.isValid()&&p2.isValid())
  {
    a=p1.y()-p2.y();
    b=p2.x()-p1.x();
    c=p1.x()*p2.y()-p2.x()*p1.y();
    float min=((a<b)?(a<c)?a:c:(b<c)?b:c);
    if(min)
    {    a=a/min;
         b=b/min;
         c=c/min;
    }
//  add(p1);
 // add(p2);
  }
}
area_t Line::get_area(const Point &p) const
{float side=a*p.x()+b*p.y()+c;
    if(side>0.0+ftolerance*100)
        return  LEFT_SIDE;
    if(side>0.0-ftolerance*100)
       return INTER_SIDE;

        return RIGHT_SIDE;
}

bool Line::separates(const Point &p1, const Point &p2) const
{
    area_t side1=get_area(p1);
    area_t side2=get_area(p2);
    if(side1==INTER_SIDE||side2==INTER_SIDE)
        return false;
    return !(side1==side2);
}

bool Line::intersect(const Line &other) const
{
    return (std::abs(a*other.b-other.a*b)>=ftolerance);
}


// отрезок
Segment::Segment(Point p1,Point p2)
{
   add(p1);
   add(p2);
 _origin=&point(0);
}
// менять направление
void Segment::change_direct()
{  //
    if( _origin->isEqual(point(0))) _origin=&point(1);
    else _origin=&point(0);

}

Point Segment::get_origin() const
{
    return *_origin;
}

Point Segment::get_end() const
{
   if(_origin->isEqual(point(0))) return point(1);
   return point(0);
}

float Segment:: length() const
{
   // теорема пифагора :
    float x=point(0).x()-point(1).x();
    float y=point(0).y()-point(1).y();
    return sqrtf(x*x+y*y);
}

area_t Segment::get_area(const Point &p) const // вернем положение точки относительно отрезка
{
    Point a=get_end()-get_origin();
  Point b=p-get_origin();
  float sa=a.x()*b.y()-b.x()*a.y();
  if(sa>0.0) return LEFT_SIDE;
  if(sa<0.0) return RIGHT_SIDE;
  if(a.x()*b.x()<0.0||a.y()*b.y()<0.0) return BEHIND;
  if(get_origin().isEqual(p)) return ORIGIN;
  if(get_end().isEqual(p)) return DESTINATION;
  float alength=sqrt(a.x()*a.x()+a.y()*a.y());
  float blength=sqrt(b.x()*b.x()+b.y()*b.y());
  if(alength<blength) return BEYOND;
  return INTER_SIDE;

  //if(a.x()*a.x())
}

bool Segment::separates(const Point &p1, const Point &p2) const
{
  area_t side1=get_area(p1);
   area_t side2=get_area(p2);
 if(side1==INTER_SIDE||side2==INTER_SIDE) return false;
 else return !(side1==side2);
}


//*************************
//class Lines (Segments)

void Lines::draw_lines() const
{
    if(color().visibility())
    {
     if(line_type==Lines::SeparatesLines)
      { for(int i=1;i<num_of_point();i+=2)
        {
           fl_line(point(i-1).x(),point(i-1).y(),point(i).x(),point(i).y());
        }
     }
     else {// для связанных типов
//         for(int i=1;i<num_of_point() ;++i)
//         {
//           fl_line(point(i-1).x(),point(i-1).y(),point(i).x(),point(i).y());
//              }
       if(2>num_of_point()) return;
     Shape::draw_lines();
      if(line_type==Lines::ClosedLines) // если закрытый полигон, ресуем последнюю линию
           fl_line(point(num_of_point()).x(),point(num_of_point()).y(),point(0).x(),point(0).y());
     }
    }
}
void Lines::add(Point p1, Point p2)
{
  // для отдельных линий нельзя добавлять отдельные точки
 if(line_type==SeparatesLines&& !p2.isValid())
     return;
   Shape::add(p1);
   if(p2.isValid())
       Shape::add(p2);

}
void Lines:: set_point(int i,Point p)
{
  if(i>num_of_point()) return;

point(i)=p;
}







void Polygon::add(Point p1, Point p2)
{
    add(p1);
    add(p2);
}

void Polygon::add(Point p)
{
    // проверить что новая грань не пересекает существующие;
    if(num_of_point()<2) // если точек мало
     {   Lines::add(p); // добавляем
        return;
        }
   for(unsigned i=1;i<num_of_point()-1;i++)
   {
     Segment sg(point(i-1),point(i));
    if(sg.separates(point(num_of_point()),p))
        return;
    }
   Lines::add(p);

}


Rectangle::Rectangle(Point xy,float ww, float hh):w{ww},h{hh}
{
    if(h<=0||w<=0)
        return ;  // неположительная сторона, можем отрисовать зеркально
    add(xy);
}

Rectangle::Rectangle(Point p1,Point p2): w{p2.x()-p1.x()},h{p2.y()-p1.y()}
{ // нужна проверка, на верхнюю левую точку
  if(w<=0||h<=0)
      return; // error (первая точка не верхняя левая)
  add(p1);

}

void Rectangle::draw_lines() const
{
    // нужно проверить заполнение fill_color
    if(fillcolor().visible)
    {
      fl_color(fillcolor().as_int());
      fl_rectf(point(0).x(),point(0).y(),w,h);
    }
     //отобразить  рамку
    if(color().visible)
    { fl_color(color().as_int());
        fl_rect(point(0).x(),point(0).y(),w,h);
    }

}

// class Text

void Text::draw_lines() const
{ fl_font(Fl_Font(fn.as_int()),fnt_sz);
    fl_draw(lab.c_str(),point(0).x(),point(0).y());
}

Function::Function(Fct f, double r1,double r2, Point org, int cnt ,double xscl,double yscl)
{
 if(r2-r1<=0)  return; // error("bad graphing range")
 if(cnt<=0) return; // error ("non-positive graphing count")
double dist=(r2-r1)/cnt;
double r= r1;
for(int i=0;i<cnt;++i)
{
    //std::cout<<i<<"  : Y: "<<org.y()-int(f(r)*yscl)<<'\n';
    std::cout<<i<<" Point ("<<org.x()+int(r*xscl)<<", "<<org.y()- f(r)*yscl<<"\n";
if(org.y()-int(f(r)*yscl)>=0){
 add(Point(org.x()+int(r*xscl),org.y()-int(f(r)*yscl)));
r+=dist;} else break;
   }
 }

//void Function::draw_lines() const
//{
//   // if(color().visible && 1<points.size())
//        for(unsigned i=1;i<num_of_point();i++)
//        {
//            fl_line(point(i-1).x(),point(i-1).y(),point(i).x(),point(i).y());
//        }
//}

Axis::Axis(Orientation oor,Point xy,int length,int n,std::string lab):label(Point {0,0},lab)
{
    if(length<0)  return;//error
    switch (oor)
    {
    case horisontal:
        // добавить линию оси
        Shape::add(xy);
        Shape::add({xy.x()+length,xy.y()});

        if(0<n) // добавляем деления
        {
           int dist=length/n;
           int x=xy.x()+dist;
   for(int i=0;i<n;++i)
   {
       notchas.add({x,int(xy.y())},{x,int(xy.y()-5)});
       x+=dist;
    }
        }
     label.move(length/3,xy.y()+20);
         break;
    case vertical:
        Shape::add(xy);
        Shape::add({xy.x(),xy.y()-length});
    if(0<n) // если количество линий больше нуля
    {
      int dist=length/n;
      int y=xy.y()-dist;    // т.к. системное начало отчета y идет сверху
        for(int i=0;i<n;++i)
        {
            notchas.add({int(xy.x()),y},{int(xy.x()+5),y})  ;
            y-=dist;
        }
    }
        label.move(xy.x()-10,xy.y()-length-5);
        break;


    default:
        break;
    }

}
void Axis::draw_lines() const
{
    Shape::draw_lines();
    notchas.draw();
    label.draw();
}

void Axis::move(float dx, float dy)
{
    Shape::move(dx,dy);
    notchas.move(dx,dy);
    label.move(dx,dy);
}
void Axis::set_color(Color c)
{
    Shape::set_color(c);
    notchas.set_color(c);
    label.set_color(c);
}
}
