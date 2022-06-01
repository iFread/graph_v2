#ifndef CANVAS_2_H
#define CANVAS_2_H
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Scroll.H>
#include <Fl/Fl_Box.H>



#include "point.h"
#include "base_graph.h"
#include "base_tool.h"
#include "dynamic_axis.h"


  namespace Graph{

#define  width_axis 30
#define hight_axis 30
const int widht_field =30000; //
const int hight_field =30000 ;// Ширина и высота рабочего поля в мм


  struct in_box
  {
    int x;
    int y;
    int w;
    int h;
     };


class canvas_2:public Fl_Box
{
    Tool* _tool {nullptr} ;
 //   Shape *cur_sh{nullptr};
    std::vector <Shape_t*> sh_t_vec;
    //Axis ax_y;
    Point cur_mouse_point{}; //точка в пределах canvas
 int cur_scale {100};

public:     // создаем новый виджет в позиции x,y
    canvas_2(int x_pos, int y_pos, int ww,int hh,const std::string &s);
    Point get_mouse(){return cur_mouse_point;}//{cur_mouse_point.x()+x(),cur_mouse_point.y()+y()};}
    void set_tool(Tool* tl) ;      // if(_tool) {delete _tool; _tool=tl;} else _tool=tl;
    Tool * tool() const {return  _tool;}
    void set_scale(int );
    float scale(){return cur_scale;}
     void draw_cursor(in_box);
      void set_mouse_position(const Point & );
    Shape_t * move_to_shape();    // определяем, что курсор мыши содержится на фигуре из вектора Shape_t
   int count()const {return sh_t_vec.size();} // размер вектора
  // загрузка фигуры в вектор
  void add(Shape_t* st){sh_t_vec.push_back(st);}
  void clear_tool(){if(_tool) {delete _tool; _tool=nullptr;std::cout<<"clear_tool 1 2 3\n";}}
//  метод отрисовки и метод взаимодействия с пользователем
  void draw();
  int handle(int event);
  void resize(int x,int y,int w,int h);// {Fl_Widget::resize(x,y,w,h);}


  //void resize(int x,int y,int w,int h);
  // удаление фигур из вектора,

  ~canvas_2()
 {
      for(unsigned i=sh_t_vec.size();i>0;--i)
      {
      delete sh_t_vec[i-1];
      }
      if(_tool)
          delete _tool;
  }
};
class Scroll:public Fl_Scroll
{ public:

    Scroll(Point xy,int ww,int hh) ;//:Fl_Scroll(xy.x(),xy.y(),ww,hh,""){}
    int handle(int ev);
    void draw();

    ~Scroll(){}
  void resize(int x,int y,int w,int h);
  canvas_2* canvas(){return ptr;}
 in_box inside_box();
 void set_scale(int s);
private:
  canvas_2*ptr{nullptr};
  int scale{100};

  //dynamic_axis* x_axis {nullptr};
  // dynamic_axis*y_axis{nullptr};
};

// группа виджетов, включает canvas(холст) и шкалы размеров , отвечает за их взаимодействие

class Canvas:public    Fl_Group
{public:
    Canvas(Point xy,int ww,int hh);//:Fl_Group(xy.x(),xy.y(),ww,hh){}

    int handle(int ev);
    ~Canvas(){}
 void draw();
 void resize(int x,int y,int w,int h);
// дублируют функции, чтобы из группового виджета был доступ
// Функции canvas
 Tool* tool(){return cnv_ptr->tool();}
 void clear_tool(){cnv_ptr->clear_tool();}
 void set_tool(Tool* tl){   cnv_ptr->set_tool(tl);}
 canvas_2* get_canvas(){return cnv_ptr;}
private:
 Scroll *s_ptr{nullptr};
 canvas_2 *cnv_ptr {nullptr};
 dynamic_axis *dyn_x{nullptr};
 dynamic_axis* dyn_y{nullptr};
// Fl_Scroll *scroll{nullptr};
// т.к. canvas отвечает за отоброжение классов,
 //ему нужно отслеживать их размер
// int iwtolerance{40};
// int ihtolerance{30};

};

  }
#endif // CANVAS_2_H
