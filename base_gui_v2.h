#ifndef BASE_GUI_V2_H
#define BASE_GUI_V2_H

#include "point.h"
#include <vector>
#include <FL/Fl.H>
#include <Fl/fl_draw.H>
#include "binder_lib.h"
#include <string>


namespace Graph {
 // положение точки относительно вектора
enum area_t{ LEFT_SIDE, RIGHT_SIDE,INTER_SIDE,BEHIND,BEYOND,ORIGIN,DESTINATION};


class Shape
{
  std::vector<Point> points;
  Color lcolor{Fl_Color()};
  Line_style ls{0};
  Color fcolor{Color::invisible};

public:

 void draw() const;



 void set_color(Color col){lcolor=col;}
 void set_style(Line_style st){ls=st;}
 void set_fill_color(Color col){fcolor=col;}

Color color()const{return lcolor;}
Line_style style()const{return ls;}
Color fillcolor() const{return  fcolor;}

Point point(int i) const;
Point &point (int i);

int num_of_point() const;
 virtual void move(float dx, float dy);
 void clear();
 virtual ~Shape() {}
protected:
  Shape();
   void add(Point p){points.push_back(p);}
   void set_point(int i,Point p); // если есть такая точка установить ее в p, иначе установить последнюю точку как p
   virtual void draw_lines() const;


private:
  Shape(const Shape &sh)=delete;
  Shape& operator=(const Shape& )= delete;
};

class Text:public Shape
{           // Точка определяет нижний угол первой буквы
public:
    Text(Point px,const std::string &s):lab{s}{ add(px);}

void set_label(const std::string &s){lab=s;}
std::string label() const{return lab;}

void set_font(Font ff){fn=ff;}
Font font() const{return fn;}
//std::string text() {return lab;}
void set_point(Point p){ point(0)=p;}
void set_font_size(int fz){fnt_sz=fz;}
int font_size() const {return fnt_sz;}
protected:
void draw_lines()const;

private:
std::string lab;
Font fn {fl_font()};
int fnt_sz {(fl_size()<14)?14:fl_size()}; // шрифт по умолчанию
};


/*
 на прямой следует учитывать точки, являющиеся отрезком, т.к. прямая бесконечна
направление отрезка?,отсчитывается от нуля, таким образом больше та точка, значение любой из координат которой больше
*/


/*ориентация отрезков относительно точки
 пара векторов называется положительно ориентированной если кратчайщий поворот от первого вектора ко второму осуществляется против часовой стрелки,
 в классе отрезка имеем направление,- от начальной точки до конечной, при этом направление можно  менять,
изменение направления не должно затрагивать другие фигуры,
 фигура (НЕ?) представлена набором векторов,
   но отдельную грань фигуры можно рассматривать как вектор

*/
/* класс линии не должен быть привязан к графическому интерфейсу, т.к. линия бесконечна, а gui оперирует отрезками


*/
class Line
{ float a;
  float b;
  float c;

public:
    Line(Point p1,Point p2);//{add(p1);add(p2);} // p1,p2 - определяют конец отрезков
   area_t get_area(const Point &p) const;  // опеределяет положение точки относительно линии

   bool separates(const Point &p1, const Point& p2) const; // определяет разделены точки данной линией
   bool intersect(const Line & other) const;  // определяет пересечение линий,
   // следует учитывать длину отрезков,
   Point point_of_intersect(const Line &other) const; // возвращает точку пересечения линий

};

// класс Segment должен содержать вершины Vertex, а не Point, и соответственно принимая точки инициализирующие вершины,


class Segment:public Shape
{
   Point *_origin; //указатель на начальную точку, определяет направление отрезка

public:
    Segment(Point p1,Point p2);
   void  change_direct(); // меняет направление на противоположное
   Point get_origin() const; // начало отрезка
   Point get_end() const;
   float  length()const;
   area_t get_area(const Point &p) const;
   // так же пересечение отрезков,
  bool separates(const Point &p1,const Point &p2) const ;// определяем, разделяет ли отрезок две точки
};

class Lines:public Shape // Segments
{
public:
    enum Lines_type{SeparatesLines,OpenLines,ClosedLines};
    Lines(Lines_type ln=SeparatesLines):Shape(), line_type{ln} {}
    Lines(Lines_type ln,Point p1,Point p2) :line_type{ln}
    {
        Shape::add(p1);
        Shape::add(p2);
    }
void set_point(int i,Point p);
    void add(Point p1,Point p2={}); // позволяет присвоить одну точку для типов PolyLines, ClosedLynes
    //void add(Segment ln);
  //  Point point(int i) {if(i<num_of_point())return Shape::point(i); return {};}
protected:
     void draw_lines() const;
private:
      Lines_type line_type;


};

 //**********************************************
// Polygon  - унаследован от Lines {Lines_type==ClosedLine}
// но в отличие от Lines не имеет пересекающихся сторон, т.е. представляет выпуклый многоугольник

// стоит определить класс вершины, Vertex, -как связный список узлов?
// Node{} имеющих координаты
// добавить конструкторы полигона по количеству вершин, см sfml
/* Определенные классы подходят для рисования на экране,
 *  для чпу необходимы классы Vertex(вершина), Segment(направленный отрезок)
 Polygon - список связанных вершин, связанные вершины определяют направление граней(Segment)
  таким образом определяем проход станка

*/
class Polygon:public Lines
{ public:
    Polygon () :Lines{Lines::ClosedLines}{} //  наследуемся от типа Lines_type==ClosedLines
 // при загрузки точки нужно проверить, что она не пересекает существующие грани
   void add(Point p1,Point p2);
    void add(Point p); // позволяет добавить одну точку

};

// Прямоугольник
 // Функциональные объекты следует наследовать от Fl_Widget

class Rectangle:public Shape
{
public:
    Rectangle(Point xy,float ww, float hh);
    Rectangle(Point lv,Point rb);

    void resize(float x, float y){w=x;h=y;}
float width();
 float height();
 Point begin(){return point(0);}
protected:
  void draw_lines() const override;
private:
   float w;
    float h;

};

typedef double Fct(double);


class Function:public Shape
{ public:
 Function(Fct f, double r1, double r2,Point orig, int count=100,double xscale=25,double yscale=25);
protected:
 //void draw_lines() const;
};
// не определены классы Circle, Ellipse, Marks, Image


class Axis:public Shape
{
public:
    enum Orientation { horisontal,vertical };
    Axis(Orientation oor, Point xy,int length,int num_of_notches=0, std::string lab ="");
  void draw_lines() const override;
  void move(float dx,float dy) override;
  void set_color(Color c);

  Text label;
  Lines notchas{Lines::SeparatesLines}; // инициализируем различными линиями
};


};
#endif //  BASE_GUI_V2_H
