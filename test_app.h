#ifndef TEST_APP_H
#define TEST_APP_H

#include "binder_lib.h"
#include "gui_interface.h"
#include "gui.h"
#include "canvas_2.h"
#include "base_tool.h"

using namespace Graph;

/*
 *  1. Canvas и dyn_axis должны как то обмениваться координатами
      При клике мыши на Canvas, координаты вершины сохраняются как some_axis.getf(int coord);
     Таким же образом, при canvas.draw_lines()
        для каждой координаты фигуры в shape_t, должна вызываться обратная функция  some_axis.geti(float coord)
        функции преобразования учитывают коэфициент, на dyn_axis,начальную точку canvas и размеры canvas

   2. функции преобразования как методы canvas:  в этом случае в dyn_axis, есть метод возвращающий коэфициент для axis, текущее_начало отсчета axis, (ширину деления в пикселях )
      При добавлении вершины: 1. Получаем данные axis, вычисляем координаты по холсту,
        При рисовании вершины обратные вычисления
*/
 class test_window:public Graph::Window
 {
 public:
   test_window(Point xy,int ww,int hh,const std::string & title); //: Window(xy,ww,hh,title.c_str())


   ~test_window(){}
 private:

  Cnvs_grp grp;
   // Scrollbar scrll;
  //Canvas scrll;
  // canvas cnvs;
 // dyn_axis x_ax;
  //dyn_axis y_ax;
// кнопки - группировать в меню
  Button tool;
// axis x_ax;
 //axis y_ax;


  Button poly_line; // lines
  // Button shapes
  // Button transform;

  // Button convert; // преобразовывает координаты в код для передачи станку


  // индикаторы для отображения координат
  Out_box in_window;

  //Out_box in_canvas;


// вспомогательные функции (функции обратного вызова)
// void redraw();
  };

 void cb_gtPens(Fl_Widget*,void* data);
// {
//   Graph::Canvas* cn=  reinterpret_cast<Graph::Canvas*>(data);

//  if((cn->tool()!=nullptr))

//  cn->clear_tool();

//    //  Graph::Pen* pn=new Graph::Pen (cn);
//  Graph::Poly_line*pn=new Graph::Poly_line(cn->get_canvas());
//  cn->set_tool(pn); //static_cast<Graph::Tool*>(data));
// }


// void cb_gtTool(Fl_Widget*,void* data)
// {
//  Graph::Canvas*cn=reinterpret_cast<Graph::Canvas*>(data);
//  if(cn->tool()!=nullptr)
//      cn->clearTool();
//  Graph::Tool* tl=new Graph::Tool(cn);
// cn->set_tool(tl);

// }

#endif // TEST_APP_H
