#ifndef BASE_GRAPH_H
#define BASE_GRAPH_H
#include "base_gui_v2.h"
#include "point.h"
#include <iostream>
#include <exception>
namespace Graph
{
const float fl_eps=0.002;





class Node // узел для хранения вершин полигона
{ static int cnt_node ;
protected:
    Node * _prev;
    Node *_next;
public:
    Node():_prev(this),_next(this){cnt_node++;} // узел на самого себя
    Node * next(){return _next;}
    Node *prev(){return _prev;}
    Node* insert(Node*) ;
    Node * remove();
   ~Node(){--cnt_node;}
    void splice(Node*) ;// слияние списков
    int count(){return Node::cnt_node;}
};


class Vertex: public Node, public Point // вершина
{
 public:
    Vertex(float xx,float yy):Point{xx,yy} {}   // нужно проверить что точки валентны
    Vertex (int xx,int yy):Point{xx,yy}{}      //
    Vertex(Point p):Point{p}{}       //

    Vertex *cw(){return  (Vertex*) this->next();} // последователь
    Vertex *ccw(){return (Vertex*) this->prev(); } // предшественник



    Point point()   {return *((Point*)this);}  //

    bool operator==(Vertex &ver) const
    {
        return  (*(Point*) this).isEqual((const Point)ver);
    }

    float x(){return this->point().x();}
    float y(){return this->point().y();}

    void add(Vertex* p)
    {
      Node::insert(p);
    }
  Vertex* remove()
    {
      return (Vertex*) Node::remove();
    }

  void change(Point p)
  {
   Point::x(p.x());
   Point::y(p.y());

  }
//private:
//    Vertex* next;
//    Vertex *prev;

};

class Shape_t
{
    Vertex *v;//
    int size; //
    // для отображения
    Color lcolor{Fl_Color()};
    Line_style ls{0};
    Color fcolor{Color::invisible};
public:
    void draw ()const;

    virtual ~Shape_t();


    void set_color(Color col){lcolor=col;}
    void set_style(Line_style st){ls=st;}
    void set_fill_color(Color col){fcolor=col;}

   Color color()const{return lcolor;}
   Line_style style()const{return ls;}
   Color fillcolor() const{return  fcolor;}


    virtual int vertex_count() const {return size;}

    virtual  Point point(int i) const;

   virtual bool contain(Point p)  =0; //возвращает сегмент содержащий точку
   // для простых классов возвращается this, для составных - сегмент фигуры, который содержит точку
   // например, отрезок ломанной или грань сложной фигуры


protected:
    virtual void draw_lines() const;
  Shape_t():v{nullptr},size{0}
   {
   //    std::cout<<"Shape construct\n";
  }



inline void add(Point p)
    { if(size==0)
            v=new Vertex(p);
       else //нужно добавлять в конец, а не во вторую позицию
         v->ccw()->insert(new Vertex(p));

      std::cout<<v->ccw()->x()<<" "<<v->ccw()->y()<<"\n";
      size++;

    }

    void rotate(Point p,double an); // повотор всех точек, относительно точки p
    void remove(int n)
    {
       //if(n==size)
        //   v->ccw()->remove();
      Vertex* w=v;
      int i=0;
     while(w!=v->ccw())
      {if(i++==n) break;
         w=w->cw();

      }

      w->remove();
    size--;
    }
public:
    virtual void change(Point p1,Point p2); // переместить вершину из  p1 в p2


public:
    // сравнение фигур происходит путем сравнения их размеров и вершин,(возможно сравнивать направления граней)
    bool compare(const Shape_t* tr) const;
virtual void add_vertex(Point p);
};
// линия формируется по двум точкам, либо по точке и длине
// представляет отрезок,
class line_t:public Shape_t
{
    float a,b,c;
public:

   line_t(Point p1,Point p2);

   line_t(Point p,float len,float an=0);

 // положение точек и прямых
 bool get_side_ln(const Point &p)const; // определяет лежит ли точка на прямой, или в левой или правой полуплоскости
  area_t get_side_area(const Point &p) const;                // определяет положение точки относительно отрезка
 bool separates(const Point &p1,const Point &p2) const;    // определяет разделены ли переданные  точки данным отрезком
bool intersect(const line_t& other) const;                 // определяет есть ли пересечение с переданным отрезком
 void change(Point p1,Point p2);
Point point_intersect(const line_t& other) const;     // не реализована     // определяет точку пересечения с переданным отрезком


Point begin() const { return point(0);}
Point end() const {return point(1);}
float normal(Point p) const;//{return {a,b};}
Point getPoint(Point &p) const; // точка на прямой по длине вектора

float length() const;
    void draw_lines()const;

    double angle(){return angle_rot;}
void angle(float an);

bool contain(Point p)  ;

~line_t(){}
private:
// double length;  // длина
double angle_rot; // поворот относительно начального положения,
double angle_by_x;//  поворот относительно оси x

};

// класс линий, представляет множество линий, могут быть связанны между собой или независимые
// для программы представлены просто набором вершин,
// в случае необходимости нужные вершины интерпретируются как line_t

// вынести separates в отдельный класс , представить как vector<line_t>
 // типы openLines, closedLines

// ломанную так же можно представить как вектор линий,

class poly_lines_t:public Shape_t
{
public:
    enum line_type{openLines,closedLines};
 // по умолчанию ломанная
    poly_lines_t(line_type lt=openLines):type{lt}{}

    poly_lines_t(line_type lt,Point p1,Point p2={}):type{lt}
    {
      add(p1,p2);
    }

 void add_vertex(Point p); // добавить новую вершину

    void add(Point p1,Point p2={})
    {
       // if((!p2.isValid())&&type==separates) // тип separates позволяет добавлять только две точки
        //    return;
       if(p1.isValid())
            Shape_t::add(p1);

       if(p2.isValid())
          Shape_t::add(p2);
        else std::cout<<"not Valid\n"; //
       }
    void remove()
    {
  if(0<vertex_count())
       Shape_t::remove(vertex_count());
   std::cout<<" vertex:: "<<vertex_count()<<"\n";
    }
bool contain(Point p)  ;
    ~poly_lines_t() {} // деструктор

protected:
    void draw_lines() const;

private:
     line_type type;
};

/*
1
  разделить классы на простые и составные
    в  составных классах возвращать не весь объект Shape_t* а сегмент объекта (который так же представляет отрезок(Shape_t*))



*/

class lines_t:public Shape_t
{
 std::vector<Shape_t*> lines;

public:
  lines_t(){}
void add(Point p1,Point p2);    // формируем линию
void add(const line_t &ln);
Point point(int i) const; // перегрузим точку для возвращения вершины
int vertex_count() const;
~lines_t()
{
    for(unsigned i=0;i<lines.size();++i)
     static_cast<line_t*>(lines[i])->line_t::~line_t();
   lines.clear();
}
bool contain(Point p)  ;
protected:
 void draw_lines() const;
};


class Vector
{

};



}




#endif // BASE_GRAPH_H
