#include "canvas_2.h"
#include <Fl/Fl.H>

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

 Point cnvs_beg={x(),y()};
 Fl_Color old=fl_color();

 for(unsigned i=0;i<sh_t_vec.size();++i)
 {
    //sh_t_vec[i]->set_color(Fl_Color(FL_BLACK));
     //sh_t_vec[i]->set_style(ls.style(),ls.width());
     // для изображения фигур на canvas нужен свой метод
       //sh_t_vec[i]->draw_with_coord({x(),y()});
  // либо изображаем фигуры здесь
  fl_color(FL_BLACK);
     for(unsigned j=0;j<sh_t_vec[i]->vertex_count()-1;j+=1)
   {
         Point beg=sh_t_vec[i]->point(j)/scale()+cnvs_beg;//get_mouse();
     Point _end=sh_t_vec[i]->point(j+1)/scale()+cnvs_beg;//get_mouse();
//  fl_line(beg.x()*cur_scale,beg.y()*cur_scale,_end.x()*cur_scale,_end.y()*cur_scale);
 fl_line(beg.x(),beg.y(),_end.x(),_end.y());
   }
    //sh_t_vec[i]->set_color(old);
fl_color(old);
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

void canvas_2:: resize(int x,int y,int ww,int hh) {
   // double wid=cur_scale*w;
   // double hig=cur_scale*h;
//std::cout<<"resize canvas_2 with ="<<ww<<"  "<<hh<<"\nand w =" <<this->w()<<"\n";
//if(ww!=this->w()||hh!=this->h())
//Fl_Widget::resize(x,y,ww*cur_scale,hh*cur_scale);
//else
    std::cout<<"resize for canvas_2 : "<<w()<<"  "<<h()<<"\n";
   Fl_Widget::resize(x,y,ww,hh);

//redraw();
}


void canvas_2::set_scale(int s)
{

    std::cout<<"cur_width = "<<widht_field/s<<"\n";
 size(widht_field/s,hight_field/s);
   cur_scale=s;///cur_scale;
}

int canvas_2::handle(int event)
{
    switch (event)
    {

     case FL_MOUSEWHEEL:

     break;
     case FL_DRAG:

     break;
    case FL_PUSH:
       // координаты относительно начала canvas_2

//std::cout<<" Canvas x,y "<<x()<<", "<<y()<<" Mouse pos :"<<Fl::event_x()<<" "<<Fl::event_y()<<"\n";
    case FL_MOVE:

      //  cur_mouse_point.x(Fl::event_x() -x());   //
       // cur_mouse_point.y(Fl::event_y() -y());
    //   break;
       // std::cout<<"canvas_2: pos "<<cur_mouse_point.x()<<" "<<cur_mouse_point.y()<<"\n";
       //

        break;
    }
if(_tool!=nullptr)
    _tool->handle(event); // передаем событие инструменту
   //this->redraw();

return event;
}

void canvas_2::set_mouse_position(const Point &p)
{ //переданная точка лежит в пределах окна скролинга,
    //менять положение текущей точки для canvas_2 нужно, если эта точка лежит в пределах canvas_2 т.е.
   // переданную точку устанавливаем в положение относительно начала canvas
    // она смещена относительно курсора на cvns->x(),y() на координаты начальной точки canvas

   // текущая позиция - абсолютные координаты [0-3000]

    cur_mouse_point={(p.x()-x())*scale()  ,(p.y()-y())*scale()} ;
 //std::cout<<"cur_mouse_point canvas {"<<cur_mouse_point.x()<<" "<<cur_mouse_point.y()<<"}\n";
//  std::cout<<"cur_begin_point {"<< x()<<" "<< y()<<"}\n";
  //std::cout<<"cur__point {"<< p.x()<<" "<< p.y()<<"}\n";

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
    ptr=new canvas_2(xy.x(),xy.y(),widht_field/scale ,hight_field/scale ,"");
//    x_axis=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww*10-2*width_axis,20,"");//ww-2*width_axis,20,"axis_x");
 //   y_axis=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh*10-4*hight_axis,20,"");//hh-4*hight_axis,20,"axis_y");
     add(ptr);
  //   x_axis=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww-2*width_axis,20,"axis_x");
   //   y_axis=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh-4*hight_axis,20,"axis_y");
  // add(x_axis);
  // add(y_axis);

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

 // std::cout<<"resize scroll with : "<<this->w()<<" "<<this->h()<<"\n";
    Fl_Scroll::resize(x,y,w,h);
   // Fl_Widget::resize(x,y,w,h);

   //  ptr->resize(x,y,w ,h );

  }

int Scroll::handle(int ev)
{

        Fl_Scroll::handle(ev);
     //  std::cout<<xposition()<<"\t"<<yposition()<<"\n";
//    in_box box= inside_box();
 //  if((ev==FL_MOUSEWHEEL) &&  (Fl::event_inside(box.x,box.y,box.w,box.h)))



    return ev;
}
// изменение размера окна, и позиционирование
void Scroll::set_scale(int s)
{
 Point cur=ptr->get_mouse();
 Point _to{xposition(),yposition()};
 //scale=s;
   //ptr->set_scale(s);
//std::cout<<"set scale "<<s<<" w= "<<w()*s<<" h = "<<h()*s<<"\n";
 ptr->set_scale(s);
 // возвращает в масштабе canvas
//std::cout<<"sscrolbar position :" <<xposition()<<" "<<yposition()<<"\n";


// нужно определить перемещение
//std::cout<<"point in canvas: "<<ptr->get_mouse().x()<<" "<<ptr->get_mouse().y()<<"\n";
//if(scale>1){
 _to.x(_to.x()*s/scale);//+w()/2);
_to.y(_to.y()*s/scale);//+h()/2);
std::cout<<"cur scale _to "<<_to.x()<<" "<<_to.y()<<"\n";
// cur.x( cur.x()-ptr->x());
 //cur.y(cur.y()-ptr->y());
 //cur.x(((cur.x()-w()/2)>0)?cur.x()-w()/2:0);
 //cur.y(((cur.y()-h()/2)>0)?cur.y()-h()/2:0);
//cur.x()
//}
 //else

 //if((cur.x()>w()/2)|| (cur.y()>h()/2))
 scroll_to(_to.x()  ,_to.y());
//else scroll_to(0,0);

 scale=s;

 std::cout<<"canas mouse posirion  "<<cur.x()<<" "<<cur.y()<<" with "<<1.0/s<<"\n";
std::cout<<"begin canvas is "<<ptr->x()<<" "<<ptr->y()<<"\n";
//std::cout<<"scroll_to "<<cur.x()-w()/2<<" "<<cur.y()-h()/2<<" with "<<s<<"\n";
//}
//else
  //  scroll_to(0,0);
// Fl_Scroll::redraw();
}

  in_box Scroll::inside_box()
{ //in_box _box;
    in_box box;
     bbox(box.x,box.y,box.w,box.h); // получить текущее
    // box= {box.x+width_axis,box.y+hight_axis,box.w-width_axis,box.h-hight_axis};
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
          dyn_x=new dynamic_axis(Axis_pos::horisontal,{xy.x()+width_axis, xy.y() },ww-2*width_axis,10,"axis_x");
           add(dyn_x);
           dyn_y=new dynamic_axis(Axis_pos::vertical,{xy.x(),xy.y()+hight_axis},hh-4*hight_axis,10,"axis_y");
         add(dyn_y);

  // add(scroll);
}
void Canvas::resize(int x, int y, int w, int h)
{ //iwtolerance=w/40;
   Fl_Widget::resize(x,y,w,h);
 // перерисовка при изменении размера окна
     s_ptr->resize(this->x()+width_axis,this->y()+hight_axis,this->w()-2*width_axis,this->h()-4*hight_axis);
     dyn_x->resize(this->x()+width_axis,this->y(),this->w()-2*width_axis,hight_axis);
     dyn_y->resize(this->x(),this->y()+hight_axis,width_axis,this->h()-4*hight_axis );

  //перерисовка при изменении масштаба
      // изменяет размер canvas_2

 //Fl_Group:: draw();
}
void Canvas::draw()
{
  Fl_Group::draw_children();


 //cnv_ptr->redraw();
}
int Canvas::handle(int ev)
{
   Fl_Group::handle(ev);

 //  s_ptr->handle(ev);
cnv_ptr->set_mouse_position({Fl::event_x(),Fl::event_y()});

    in_box box=s_ptr->inside_box();
 if((ev==FL_MOUSEWHEEL) &&  (Fl::event_inside(box.x,box.y,box.w,box.h)))
 {

    dyn_x->handle(ev);
    dyn_y->handle(ev);
 s_ptr->set_scale(dyn_x->scale());
  }


//}
  // s_ptr->handle(ev);
   //
//    cnv_ptr-> redraw();
    // Fl_Group:: redraw();
    return ev;
}


}
