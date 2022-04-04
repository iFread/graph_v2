#ifndef CANVAS_2_H
#define CANVAS_2_H
#include <Fl/Fl_Widget.H>
#include <Fl/Fl_Group.H>
#include <Fl/Fl_Scroll.H>



#include "point.h"
#include "base_graph.h"
#include "base_tool.h"
#include "dynamic_axis.h"


  namespace Graph{

class canvas_2:public Fl_Widget
{
    Tool* _tool {nullptr} ;
 //   Shape *cur_sh{nullptr};
    std::vector <Shape_t*> sh_t_vec;
    //Axis ax_y;
    Point cur_mouse_point{};

public:     // создаем новый виджет в позиции x,y
    canvas_2(int x_pos, int y_pos, int ww,int hh,const std::string &s);

    Point get_mouse(){return cur_mouse_point;}
    void set_tool(Tool* tl) ;      // if(_tool) {delete _tool; _tool=tl;} else _tool=tl;
    Tool * tool() const {return  _tool;}
   Shape_t * move_to_shape();    // определяем, что курсор мыши содержится на фигуре из вектора Shape_t
  int count()const {return sh_t_vec.size();} // размер вектора
  // загрузка фигуры в вектор
  void add(Shape_t* st){sh_t_vec.push_back(st);}
  void clear_tool(){if(_tool) {delete _tool; _tool=nullptr;std::cout<<"clear_tool 1 2 3\n";}}
//  метод отрисовки и метод взаимодействия с пользователем
  void draw();
  int handle(int event);

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

// группа виджетов, включает canvas(холст) и шкалы размеров , отвечает за их взаимодействие

class Canvas:public    Fl_Scroll// Fl_Group
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
 canvas_2 *cnv_ptr {nullptr};
 dynamic_axis *dyn_x{nullptr};
 dynamic_axis* dyn_y{nullptr};
// Fl_Scroll *scroll{nullptr};

};

  }
#endif // CANVAS_2_H
