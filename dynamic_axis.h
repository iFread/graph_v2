#ifndef DYNAMIC_AXIS_H
#define DYNAMIC_AXIS_H
#include <Fl/Fl_Widget.H>
#include "base_gui_v2.h"
#include <string>
#include<iostream>

#include "point.h"

namespace Graph {
/*
 представляет область (прямоугольник) в который помещается шкала с делениями, и маркировкой
длина будет устанавливаться в зависимости от размера виджета.
*/


enum Axis_pos{none,horisontal,vertical};
class dynamic_axis:public Fl_Widget
{
    const int diviration[6]={100,10,1,5,10,100}; //
public:

 //dynamic_axis():Fl_Widget(0,0,0,0,""){}     // создает пустой виджет Fl_Widget(0,0,0,0,"");
    dynamic_axis(Axis_pos pos,Point xy,int len,int st, std::string s):Fl_Widget(xy.x(),xy.y(),len,20,""),placement{pos},step{st},length{len},lab{xy,s}
 {
    init(xy,length,step);
 }
 //void init(Axis_pos pos,Point xy,int len,int st,  std::string s); // инициализация происходит от типа- горизонтально или вертикально
 void init(Point xy,int len,int st);
    void change_scale(int i){index=i; }
 int scale();
    void update(Point xy,int len); // установить новые размеры
  void resize(int xx,int yy,int ww,int hh);
 void draw() ; // отрисовка линий
 int handle(int e);
 ~dynamic_axis(){}
private:
 Axis_pos placement;
 int step{40};
 int length{0};
 int index=2;

 int scale_t{100};  //массштаб от 1 до 100

 Text lab{{0,0},""}; // отображение текста
 Lines ls{Lines::SeparatesLines};   // отображение линии
// double scale(){return diviration[index];}
 int default_width {30};
 int default_hight{30};

};

}
#endif // DYNAMIC_AXIS_H
