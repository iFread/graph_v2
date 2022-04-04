#ifndef GUI_H
#define GUI_H
#include <FL/Fl.H>
#include <Fl/Fl_Widget.H>
#include "point.h"
#include <string>
#include "binder_lib.h"
#include "gui_interface.h"
#include<typeinfo>
#include <iostream>
#include "dynamic_axis.h"
#include "canvas_2.h"

typedef void* Address ;
typedef Fl_Widget* Address1 ;
typedef void (*Callback)(Address1,Address) ; // Callback - указатель на функцию принимающюю (Address,Address)



namespace  Graph
{

template<typename W> W& reference_to(Address pw)
{ //treat an address as a reference to a W
    return  *static_cast<W*>(pw);
 }


 using std::string;
 class Widget
 {
 public:
     Widget(Point p,int ww,int hh,const string &s,Callback cb=nullptr)
         : loc{p},_width{ww},_hight{hh},label(s),do_it(cb)  {}

     virtual void hide(){pw->hide();}
     virtual void show(){pw->show();}
     virtual void attach(Window &)=0; // each Widget define at least one action a window

// доступ к приватным методам
     Point position() const {return loc;}
     int width() const {return _width;}
     int hight()const {return _hight;}
   //  string label(){return lab;}

 virtual ~Widget()
     { if(pw)
        { std::cout<<"delete widget:"<<typeid(*pw).name()<<std::endl;
         delete pw;
            }
     }

 private:

 protected:
     Point loc;   // определяет положение в окне
    int _width;
    int _hight;




 protected:
     Window *own;
     Fl_Widget *pw{nullptr}; // указатель на виджет (на кнопку, поле ввода, слидер и т.д.)
    // void * data;
 string label;
 Callback do_it{nullptr}; //указатель на функцию принимающую (void* ,void*)

        // поля класса

 private:                           // запрещаем коприрование
    Widget &operator=(const Widget&);
    Widget(const Widget&);

 };

 class Button:public Widget
 {
 public:
     Button(Point xy,int ww,int hh,const string &s,Callback cb=nullptr):Widget(xy,ww,hh,s.c_str(),cb){}

     void attach(Window &w);
     //void attach(Window &w, void* data);
 void callback(Callback cb,void *data1);
 int handle(int e);
 // void when(unsigned char e);
 };


 class In_box:public Widget
 {
 public:
     In_box(Point xy,int ww,int hh,const string &s):Widget(xy,ww,hh,s,0)
        {  }

    int get_int();
    string get_string();

void attach(Window &w);
 };

 class Out_box:public Widget
 {
 public:
     Out_box(Point xy,int ww,int hh,const string &s):Widget(xy,ww,hh,s,0) {}
     void put(int);
     void put(const string &s);
     void attach(Window &w);
 };
// canvas как виджет окна

class Scrollbar:public Widget
{ public:
    Scrollbar(Point xy,int ww,int hh,const string& s):Widget(xy,ww,hh,s,0){}

 void attach(Window &w);

};


 class canvas:public Widget
 {
 public:
     canvas(Point xy,int ww,int hh,const string &s):Widget(xy,ww,hh,s,0){}
 void add(Shape_t*ptr);
   void attach(Window &w);
   Point get_mouse();
 Shape_t* shape_on_move();
  int handle(int e);
 };

 class axis:public Widget
  {

 public:
 //    enum Axis_pos {horisontal,vertical};

     axis(Axis_pos ax,Point xy, int len, int st, const std::string &s): Widget(xy,len,20,s,0),placement{ax},step{st},length{len},txt{xy,s.c_str()}{}
   void set_scale(int sc);
   double scale();  // вернуть дробное значение для координаты
  void attach(Window &w);
// void resize(int x,int y,int ww,int hh);
~axis(){}
 private:
   Axis_pos placement;
   int step;
   int length;
   Text txt{{0,0},""};
   //length - будет задана окном
 };

class Cnvs_grp:public Widget
{ public:
    Cnvs_grp(Point xy,int ww,int hh,const string& s);
 void attach(Window &w);
 Canvas* canvas();
 int handle(int e);
 ~Cnvs_grp()
 { //Fl_Scroll &sc=reference_to<Fl_Scroll>(pw);
    // sc.clear();
    // sc.~Fl_Scroll();
  //clear()
 }
  //void draw();
private:
 // Scrollbar *scrl;
//  Canvas *cnvs;
};



}



#endif // GUI_H
