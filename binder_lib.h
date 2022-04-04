#ifndef BINDER_LIB_H
#define BINDER_LIB_H
#include <Fl/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>
#include "point.h"

/*
 * 1. в Window Shape_t  не нужны ? (либо нужны для отрисовки кнопок)
 *
 *
 *
 события:
    1.проверить что координаты мыши внутри виджета, при движении
    2. если так -при действии мыши передать событие виджету


*/

namespace Graph {
class Shape;
class Shape_t;
class Widget;

class Window:public Fl_Window
{
public:
  Window(int ww,int hh,const char *s);
  Window(Point xy,int ww,int hh,const char *s);
  int x_max(){return w;}
  int y_max(){return h;}                 //w=ww;h=hh;  size(w,h)
  void resize(int xx,int yy,int ww,int hh)  {w=ww;h=hh;Fl_Window::resize(xx,yy,w,h);redraw();}//for(unsigned i=0;i<shapes.size();++i) shapes[i]->resize();}
  void set_label(const char*s){label(s);}
  void set_label(const std::string &s) {label(s.c_str());}

  void attach(Shape &s);
  void attach(Shape_t& s);
  void detach(Shape_t &s);
  void detach(Shape&s);
   void attach(Widget &w);
  void detach(Widget &w);

  int handle(int event) override; // события для окна ограниченны проверкой

  virtual ~Window(){}
protected:
  void draw() override;
//virtual void redraw();

private:
int w;
int h;
std::vector<Shape*> shapes;
std::vector<Shape_t*> sh_t;
void init();

int handle_mouse(int event,int button);     // вспомогательная функция
//bool focus()
};


int gui_run();

class Color
{
public:
    enum Color_type
    {
  red        =FL_RED,
  blue       =FL_BLUE,
  black      =FL_BLACK,
  green      =FL_GREEN,
  yellow     =FL_YELLOW,
  white      =FL_WHITE,
  cyan        =FL_CYAN,
  magneta     =FL_MAGENTA,

  dark_red        =FL_DARK_RED,
  dark_blue       =FL_DARK_BLUE,
  dark_green      =FL_DARK_GREEN,
  dark_yellow     =FL_DARK_YELLOW,
  dark_cyan        =FL_DARK_CYAN,
  dark_magneta     =FL_DARK_MAGENTA
    };
    enum Transparency{invisible=0, visible=255};

    Color(Color_type cc):c(cc),v{visible}{}
    Color(Color_type cc, Transparency vv): c{cc},v(vv){}
    Color(int cc):c{Fl_Color(cc)},v{visible}{}
    Color(Transparency vv):c(Fl_Color()),v(vv){}

    int as_int() const {return c;}
    char visibility()const {return v;}
    void set_visibility(Transparency vv){v=vv;}

private:
   Fl_Color c;
unsigned char v;
};


class Line_style
{
public:
    enum Line_style_type
    {
      solid =  FL_SOLID,        //---------
      dash  =  FL_DASH,        // - - - -
        dot =  FL_DOT,         // .......
        dashdot = FL_DASHDOT,  // _._._.
       dashdashdot = FL_DASHDOTDOT // _.._..
    };
    Line_style(Line_style_type ss):s(ss),w(0){}
    Line_style(Line_style_type ss,int ww): s(ss),w{ww}{}
    Line_style (int ss):s{ss},w{0}{}
    int width()const {return w;}
    int style() const {return s;}

private:
    int s;
    int w;
};
 // скрытие представления fltk для шрифта
class Font
{ public:
    enum Font_type
    {
        helvetica = FL_HELVETICA,
        helvetica_bold= FL_HELVETICA_BOLD,
        helvetica_italic= FL_HELVETICA_ITALIC,
        helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,

      courier =    FL_COURIER,
      courier_bold= FL_COURIER_BOLD,
        courier_italic= FL_COURIER_ITALIC,
        courier_bold_italic= FL_COURIER_BOLD_ITALIC,

       times =  FL_TIMES,
        times_bold= FL_TIMES_BOLD,
        times_italic= FL_TIMES_ITALIC,
        times_bold_italic  = FL_HELVETICA_BOLD_ITALIC,
        symbol= FL_SYMBOL,
        screen = FL_SCREEN,
        screen_bold = FL_SCREEN_BOLD,
        zapf_dingbats= FL_ZAPF_DINGBATS
    };
    Font(Font_type ft):f{ft}{}
    Font(int ff):f{ff}{}
    int as_int() const {return f;}
private:
    int f;
};



};



#endif // BINDER_LIB_H
