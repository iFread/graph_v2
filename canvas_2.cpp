#include "canvas_2.h"
namespace Graph {


canvas_2::canvas_2(int xx,int yy,int ww,int hh,const std::string &s): Fl_Scroll(xx,yy,ww,hh)//Fl_Widget(xx,yy,ww,hh,s.c_str())
{
   _tool=nullptr;
Fl_Widget::type(Fl_Scroll::BOTH);
}

void canvas_2::draw()
{
    Fl_Scroll::draw();
// color(Fl_Color(FL_WHITE));
 fl_rectf(this->x(),y(),w(),h(),FL_WHITE);



 for(unsigned i=0;i<sh_t_vec.size();++i)
 {
     sh_t_vec[i]->draw();
 }
 if(_tool)
     _tool->draw();
 // рисуем линии координат курсора
 Fl_Color old=fl_color();
 fl_color(FL_GRAY);
    fl_line(cur_mouse_point.x(),this->y(),cur_mouse_point.x(),y()+h()) ;
    fl_line(x(),cur_mouse_point.y(),x()+w(),cur_mouse_point.y());
    //std::cout<<x()<<" "<<this->y()<<"\n";
fl_color(old);

}
void canvas_2::set_tool(Tool *tl)
{  std::cout<<"Tool create\n";
    if(_tool)
      delete _tool;

    _tool=tl;
}

int canvas_2::handle(int event)
{
    switch (event)
    {

     case FL_MOUSEWHEEL:

     break;
     case FL_DRAG:

     break;
    case FL_MOVE:

        cur_mouse_point.x(Fl::event_x() );   //
        cur_mouse_point.y(Fl::event_y() );
       break;
    case FL_PUSH:
        std::cout<<cur_mouse_point.x()-x()<<" "<<cur_mouse_point.y()-y()<<"\n";

        break;
    }
if(_tool!=nullptr)
    _tool->handle(event); // передаем событие инструменту
    this->redraw();
    return event;
}
Shape_t* canvas_2::move_to_shape()

{
 for(unsigned i=0;i<sh_t_vec.size();++i)
 {
   if(sh_t_vec[i]->contain(cur_mouse_point))
       return sh_t_vec[i];
    }
 return nullptr;
}

// Canvas создавать здесь !!!
//  и все объекты связанные с ним должны быть определены сдесь

Canvas::Canvas(Point xy,int ww,int hh): Fl_Group(xy.x(),xy.y(),ww,hh)//Fl_Scroll(xy.x(),xy.y(),ww,hh)
{    //
   // canvas_2 *
    //scroll =new Fl_Scroll(xy.x(),xy.y(),ww,hh ,"");

            cnv_ptr=new canvas_2(xy.x()+width_axis ,xy.y()+hight_axis,ww-2*width_axis,hh-4*hight_axis,"");
    // scroll->
             add(cnv_ptr);
   // dynamic_axis*
            dyn_x=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww-2*width_axis,10,"axis_x");
   // scroll->
            add(dyn_x);
   // dynamic_axis*
            dyn_y=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh-4*hight_axis,10,"axis_y");
   //scroll->
           add(dyn_y);

  // add(scroll);
}
void Canvas::resize(int x, int y, int w, int h)
{ //iwtolerance=w/40;
    Fl_Widget::resize(x,y,w,h);
    // ihtolerance=h/30;
//Fl_Group::resize(x,y,w,h);
    cnv_ptr->resize(this->x()+width_axis,this->y()+hight_axis,this->w()-2*width_axis,this->h()-4*hight_axis);
    dyn_x->resize(this->x()+width_axis,this->y(),this->w()-2*width_axis,hight_axis);
    dyn_y->resize(this->x(),this->y()+hight_axis,width_axis,this->h()-4*hight_axis );

}
void Canvas::draw()
{
  Fl_Group::draw_children();
}
int Canvas::handle(int ev)
{

if(ev==FL_MOUSEWHEEL)
{
    dyn_x->handle(ev);
    dyn_y->handle(ev);

   }

//}

    Fl_Group::handle(ev);
    return ev;
}


}
