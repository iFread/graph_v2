#ifndef GUI_INTERFACE_H
#define GUI_INTERFACE_H

#include "base_gui_v2.h"
#include <string>
#include <iostream>
#include "base_tool.h"
#include "base_graph.h"

//namespace Graph {
//class Tool;
//class dyn_axis:public Shape
//{
//public:
//    const int diviration[6]={100,10,1,5,10,100};

//    enum Orientation {none,horisontal,vertical};
//  dyn_axis(Orientation oor,Point xy,int len ,int st, std::string s="" );
//  dyn_axis(){}
// //void set_scale();
//  void set_scale(){scale=diviration[index];}
// void init(Orientation oor,Point px,int len,int st, std::string s="");  // должна вызвывать функцию redraw();
// void change_scale(int i){index=i;}
// virtual ~dyn_axis() {}
//private:
//    Orientation orient;
//    int  length;
//    int step;
////mark_line vec; //
//    Graph::Text lab{{0,0},""}; // для подписи основной линии
//    Graph::Lines ls {Graph::Lines::SeparatesLines} ; // предcтавляет деления
//    int scale; //
//    int index{2};   // ста
//protected:
//    void draw_lines() const;  // рисуем основную линию, рисуем деления, рисуем метки деления
//};


/*

class Canvas:public Fl_Widget
{
public:
    const int diviration[6]= {100,10,1,5,10,100}; // если меньше 2 scale = 1/div[i], если  больше div[i]
    Canvas(Window *wn, std::string  str=""): Fl_Widget( wn->x()+100, wn->y()+20, wn->x_max()-120, wn->y_max()-130,str.c_str()),win(wn) ,ax_x{}
    {
      ax_x.init(dyn_axis::horisontal,{win->x()+100,win->y()+win->y_max()-100},win->x_max()-130,10,"x_axis");
    //ax_x=new dyn_axis(dyn_axis::horisontal,{win->x()+100,win->y()+win->y_max()-100},win->x_max()-100,10,"x_axis");
   ax_y.init(dyn_axis::vertical, {win->x()+100,win->y()+win->y_max()-100},win->y_max()-130,10,"y_axis");
  index=2;
  ax_x.set_scale(diviration[index]);
  ax_y.set_scale(diviration[index]); // установим масштаб в единицу
 resize(wn->x()+100, wn->y()+20, wn->x_max()-120,wn->y_max()-120);
    }
void add(Shape *s){sh_vec.push_back(s);}
void add(Shape_t* s){sh_t_vec.push_back(s);}
  // обработка инструментов,
    class Fact;
   ////
   // void create(Tool* t); // создает новый объект Shape, и  добавляет его в вектор
    //void modify(Fact f,Tool *t); // модифицирует выбратнный объект Shape
                     // Tool *t - указывает на выбранный инструмент Pen, Brush, Shape(Rect, Circle, Ellipse, Polygon)
                        // Fact () ???

    void draw()   override
    {
     //
     //ax_x->draw();
     ax_x.draw();
     ax_y.draw();
     color(Fl_Color(FL_WHITE));
     fl_rect(this->x(),this->y(),this->w(),this->h());
     //Fl_Widget::draw();
     for(unsigned i=0;i<sh_vec.size();++i)
       {
        // if(sh_vec[i]) // tool имеет свой список фигур???
                        //не нравится мне это
          sh_vec[i]->draw();

        }
     for(unsigned i=0;i<sh_t_vec.size();++i)
       {
        // if(sh_vec[i]) // tool имеет свой список фигур???
                        //не нравится мне это
          sh_t_vec[i]->draw();

        }
      if(_tool)
         _tool->draw();




     if(cur_sh)
         cur_sh->draw();
    }


    int handle(int e) override;


  // проверить !!!!!

    virtual  ~Canvas()
    {
        //while (sh_vec.size())
        //{
         for(unsigned i= sh_vec.size();i>0;--i)
         {
             delete  sh_vec[i];
         }
          for(unsigned i=sh_t_vec.size();i>0;--i)
            {   delete sh_t_vec[i-1];//~Shape_t();

         // sh_t_vec.clear();
            }
         if(_tool!=nullptr)
             delete _tool;

        //}
    }
    Point get_mouse() {return cur_mouse_point;}//Fl::event_x(),Fl::event_y()};}
  Shape_t *set_focus();  // устанавливает фокус на фигуру
 int get_size() const {return  sh_t_vec.size();}
  void set_tool(Tool *tl){_tool=tl;}
  void clearTool(){if(_tool) delete _tool;_tool=nullptr; }
 Tool* tool() const{return _tool;}
    Shape_t* shape_on_move(Point p) const;  // определяет на какой фигуре находится курсор

private:
    Point cur_mouse_point{0,0};
   // copy ctor
    Canvas& operator=(const Canvas&)=delete;
    Canvas(const Canvas&)=delete;
    Canvas(const Canvas&&);

    //
 // - возвращает фигуру на которой курсор мыши,
// для этого нужно использовать Segment и определять что для всех вершин фигуры, переданная точка лежит внутри полигона, или нет
    // что бы определить лежит ли точка в полигоне, строим бесконечный луч в  одну из сторон, и проверяем пересечение луча со сторонами полигона :
        // если таких пересечений, четное число, то точка снаружи, если нечетное - то внутри,
  // при этом стоит учесть, является ли точка вершиной полигона, или может быть лежит на одной из его граней - тогда принадлежность точки полигону очевидна



   //
  Window *win;
  std::vector<Shape*> sh_vec; // вектор для хранения
  // либо хранить в динамической памяти, либо конструктор без аргументов
  // и последующее заполнение, в init()
dyn_axis  ax_x;//{Axis::horisontal};
dyn_axis ax_y;
int index;
Tool* _tool {nullptr} ;
Shape *cur_sh{nullptr};
std::vector <Shape_t*> sh_t_vec;
//Axis ax_y;
};


  */


// как ??????
/*
 * при движении мыши нужно сохранять точку на canvas где движение закончилось,
    и по окончании движения проверять находится ли точка (курсор) в пределах какого нибудь объекта shape или нет, см выше...
      .. ЗЫ : подумать над возвращением группы фигур, (получается типа подмассив, или вектор),
            : так же над возможностью вставлять этот подмассив, в любую точку вектора
            // может использовать список? или hash ()


*/

/*class Tool
{

  //
public:

    enum tools_type {none,creating, modifing};
    Tool(tools_type tp):_type{tp}{}
    virtual Shape* create()=0;// создает фигуру
    virtual void modify(Shape*){} // возвращаем ссылку
    tools_type type() const {return _type;}
    ~Tool() {}
private:
    tools_type _type;
};*/

//class t_line:public Tool
//{
//   //

//public:
//     t_line():Tool{creating}{}
//    Shape* create()override//нужны данные положения курсора
//    {
//     // std::cout<<"create tool\n";
//        Lines* ptr=new Lines{Lines::SeparatesLines};
//        Point beg {Fl::event_x(),Fl::event_y()};
//        Point end={beg.x()+1,beg.y()+1};
//         ptr->add(beg,end);
//         return ptr;
//    }

//    void modify(Shape* sh) override// Lines
//    {//std::cout<<"tool modify\n";
//       Lines* ptr= static_cast<Lines*>(sh);
//       ptr->set_point(1,{Fl::event_x(),Fl::event_y()});
//   // ptr->draw();
//    }


//  ~t_line(){}

//};


//class rect_tool:public Tool
//{
//public:
//    rect_tool():Tool{creating}{}

//   Shape* create(){
//    Rectangle *rct=new Rectangle({Fl::event_x(),Fl::event_y()},1,1);
//    return rct;
//   }


//   void modify(Shape *sh) // modify_type??
//   {
//      Rectangle* rct= static_cast<Rectangle*>(sh);
//      rct->resize(Fl::event_x()-rct->begin().x(),Fl::event_y()-rct->begin().y());


//   }
//   ~rect_tool(){}
//};

//}

#endif // GUI_INTERFACE_H
