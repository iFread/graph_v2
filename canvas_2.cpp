#include "canvas_2.h"
namespace Graph {


canvas_2::canvas_2(int xx,int yy,int ww,int hh,const std::string &s): Fl_Box(xx,yy,ww,hh,"")//Fl_Widget(xx,yy,ww,hh,s.c_str())
{
   _tool=nullptr;
//Fl_Widget::type(Fl_Scroll::BOTH);
}

void canvas_2:: draw()
{
  //  Fl_Widget::draw();
// color(Fl_Color(FL_WHITE));
 fl_rectf(this->x(),y(),w(),h(),FL_WHITE);



 for(unsigned i=0;i<sh_t_vec.size();++i)
 {
     sh_t_vec[i]->draw();
 }
 if(_tool )
     _tool->draw();
 // рисуем линии координат курсора
 // если в пределах canvas




}
void canvas_2::set_tool(Tool *tl)
{  std::cout<<"Tool create\n";
    if(_tool)
      delete _tool;

    _tool=tl;
}

void canvas_2:: resize(int x,int y,int w,int h) {
   // double wid=cur_scale*w;
   // double hig=cur_scale*h;

    Fl_Widget::resize(x,y,w,h);
}


void canvas_2::set_scale(double d){cur_scale=d;}
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
   //this->redraw();

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

Scroll::Scroll(Point xy,int ww,int hh):Fl_Scroll (xy.x(),xy.y(),ww,hh,"")
{
    ptr=new canvas_2(xy.x(),xy.y(),ww*10,hh*10,"");
//    x_axis=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww*10-2*width_axis,20,"");//ww-2*width_axis,20,"axis_x");
 //   y_axis=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh*10-4*hight_axis,20,"");//hh-4*hight_axis,20,"axis_y");
     add(ptr);
   end();
}



void Scroll::draw()
{
 //Fl_Group::draw();
Fl_Scroll::draw ();
Point cur={Fl::event_x(),Fl::event_y()};//cnv_ptr->get_mouse();
in_box box= inside_box();

if((cur.x()>box.x && cur.x()<box.w+box.x) &&(cur.y()>box.y && cur.y()<box.y+box.h))
{ Fl_Color old=fl_color();
fl_color(FL_GRAY);
   fl_line(cur.x(),box.y,cur.x(), box.h+box.y) ;
   fl_line(box.x,cur.y(),box.x+box.w,cur.y());
// std::cout<<"Drawing coord "<<cur.x()<<" "<<cur.y()<<"\n";
fl_color(old);
}


//canvas()-> redraw();

}

void Scroll::resize(int x, int y, int w, int h)
{

    Fl_Scroll::resize(x,y,w,h);
    Fl_Group::resizable(ptr);//resizeble(*ptr);//(x,y,w,h);

  // ptr->resize(this->x()+width_axis,this->y()+hight_axis,this->w()-2*width_axis,this->h()-4*hight_axis);


    // x_axis->resize(this->x()+width_axis,this->y(),this->w()-2*width_axis,hight_axis);
  // y_axis->resize(this->x(),this->y()+hight_axis,width_axis,this->h()-4*hight_axis );

  //Fl_Scroll(x,y,w,h);
   // canvas()->resize(x,y,w-20,h-20);
 // Fl_Scroll:: redraw();
}

int Scroll::handle(int ev)
{

       Fl_Scroll::handle(ev);


    return ev;
}

  in_box Scroll::inside_box()
{ //in_box _box;
    in_box box;
     bbox(box.x,box.y,box.w,box.h);
    return box;//   in_box(in_box.x,in_box)


}
// Canvas создавать здесь !!!
//  и все объекты связанные с ним должны быть определены сдесь

Canvas::Canvas(Point xy,int ww,int hh): Fl_Group(xy.x(),xy.y(),ww,hh)//Fl_Scroll(xy.x(),xy.y(),ww,hh)
{    //
   // canvas_2 *
      s_ptr =new Scroll({xy.x()+width_axis,xy.y()+hight_axis} ,ww-2*width_axis,hh-4*hight_axis);

          //  cnv_ptr=new canvas_2(xy.x()+width_axis ,xy.y()+hight_axis,10000,10000,"");//ww-2*width_axis,hh-4*hight_axis,"");
    cnv_ptr= s_ptr->canvas();
         add(s_ptr);
          dyn_x=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww-2*width_axis,20,"axis_x");
            add(dyn_x);
            dyn_y=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh-4*hight_axis,20,"axis_y");
          add(dyn_y);

  // add(scroll);
}
void Canvas::resize(int x, int y, int w, int h)
{ //iwtolerance=w/40;
   Fl_Widget::resize(x,y,w,h);
    // ihtolerance=h/30;
 //Fl_Group::resize(x,y,w,h);
    s_ptr->resize(this->x()+width_axis,this->y()+hight_axis,this->w()-2*width_axis,this->h()-4*hight_axis);
    dyn_x->resize(this->x()+width_axis,this->y(),this->w()-2*width_axis,hight_axis);
    dyn_y->resize(this->x(),this->y()+hight_axis,width_axis,this->h()-4*hight_axis );

 //Fl_Group:: draw();
}
void Canvas::draw()
{
  Fl_Group::draw_children();


 //cnv_ptr->redraw();
}
int Canvas::handle(int ev)
{
 //  Fl_Group::handle(ev);

 //   s_ptr->handle(ev);

    in_box box=s_ptr->inside_box();
if((ev==FL_MOUSEWHEEL) &&  (Fl::event_inside(box.x,box.y,box.w,box.h)))
{

    dyn_x->handle(ev);
    dyn_y->handle(ev);
//s_ptr->canvas()->set_scale(dyn_x->scale());

//dyn_x->redraw();

//dyn_y->redraw();
}

//}
   s_ptr->handle(ev);
   //
//    cnv_ptr-> redraw();
     Fl_Group:: redraw();
    return ev;
}


}
