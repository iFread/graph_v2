#include "binder_lib.h"
#include "base_gui_v2.h"
#include "base_graph.h"
#include "gui.h"
namespace Graph {


Window::Window(Point xy,int ww,int hh,const char *s):Fl_Window(xy.x(),xy.y(),ww,hh,s),w(ww),h(hh)
{
 init();
}

Window::Window(int ww,int hh,const char *s):Fl_Window(ww,hh,s),w(ww),h(hh){init();}

void Window::init()
{
  resizable(this); // изменяет группу виджетов
show();
}
void Window::draw()
{
    Fl_Window::draw();
for(unsigned i=0;i<shapes.size();++i)
    shapes[i]->draw();
for(unsigned i=0;i<sh_t.size();++i)
    sh_t[i]->draw();


}

void Window::attach(Shape &s)
{
  shapes.push_back(&s);
}
void Window::attach(Shape_t &s)
{
  sh_t.push_back(&s);
}


void Window::detach(Shape &s)
{
    for(unsigned i=shapes.size();0<i;--i)
    {
       if(shapes[i-1]==&s)
           shapes.erase(shapes.begin()+(i-1));
    }

}
void Window::detach(Shape_t &s)
{
  for(unsigned i=sh_t.size();0<i;--i)
  {if(sh_t[i-1]==&s)
          sh_t.erase(sh_t.begin()+(i-1));   // erase - принимает итератор

  }
}

// Widget
void Window::attach(Widget &w)
{
  begin();
 w.attach(*this);
 end();

}

void Window::detach(Widget &w)
{
 w.hide();
}

int Window::handle(int event)
{
   int index=children(); // количество виджетов
  Fl_Widget* wgt=nullptr;   //   передаем событие виджетам
   for(int i=0;i<index;i++)
   {
      wgt=child(i);

      if(Fl::event_inside(wgt))//wgt->x(),wgt->y(),wgt->w(),wgt->h()))
       wgt->handle(event);//
redraw();
   }

// if(Fl::event()==FL_SCREEN_CONFIGURATION_CHANGED)
 //
   return event;
}
//void Window::redraw()
//{
//   // std::cout<<"Redraw Window\n";
// }

int gui_run(){return Fl::run();}

}
