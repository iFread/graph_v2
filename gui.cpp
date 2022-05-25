#include "gui.h"
#include <FL/Fl.H>
#include <Fl/Fl_Button.H>
#include "base_tool.h"
#include "canvas_2.h"
#include <Fl/Fl_Input.H>
#include <Fl/Fl_Output.H>
#include<Fl/Fl_Scroll.H>

#include <sstream>


namespace Graph {


void Button::attach(Window &win)
{
    pw=new Fl_Button(position().x(),position().y(),width(),hight(),label.c_str());

  if(do_it )
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it),&win); // pass window
 //  pw->when(FL_WHEN_CHANGED);
  own=&win;

}

void Button::callback(Callback cb, void *data1)
{
     do_it=cb;
 pw->callback(reinterpret_cast<Fl_Callback*>(do_it),data1);
// pw->callback(do_it, data1);
// cb((Fl_Widget*)data1,data2);
}

int Button::handle(int e)
{
   if( pw->active())
    unsigned int pe=pw->changed();

  {

  }
   return 0;}


int In_box::get_int()
{
  Fl_Input &pi= reference_to<Fl_Input>(pw);
const char *p=pi.value();
if(!isdigit(p[0])) return -99999;
return atoi(p);
}

string In_box::get_string()
{
  Fl_Input&pi =reference_to<Fl_Input>(pw);
  return string(pi.value());
}

void In_box::attach(Window &w)
{
  pw=new Fl_Input(loc.x(),loc.y(),width(),hight(),label.c_str());
  own=&w;
}

void Out_box::put(int i)
{
    Fl_Output & po=reference_to<Fl_Output>(pw);
    std::stringstream ss;
    ss<<i;
    po.value(ss.str().c_str());
}

void Out_box::put(const string &s)
{
   reference_to<Fl_Output>(pw).value(s.c_str());
}

void Out_box::attach(Window &w)
{
    pw=new Fl_Output (loc.x(),loc.y(),width(),hight(),label.c_str());
    own=&w;
}
//*******************************************
void Scrollbar::attach(Window &w)
{
   pw=new Fl_Scroll(loc.x(),loc.y(),width(),hight(),label.c_str());
   pw->type(Fl_Scroll::BOTH_ALWAYS);
   own=&w;
}



// ***********************************
void canvas::attach(Window &w)
{
  pw=new canvas_2(loc.x(),loc.y(),width(),hight(),label.c_str());
own=&w;
}
void canvas::add(Shape_t *ptr)
{
    canvas_2 &cv=reference_to<canvas_2>(pw);
  cv.add(ptr);
}

Point canvas::get_mouse()
{
 canvas_2 &cv=reference_to<canvas_2>(pw);
 return cv.get_mouse();

}

Shape_t* canvas::shape_on_move()
{
  canvas_2 &cv=reference_to<canvas_2>(pw);
  return cv.move_to_shape();
}

int canvas::handle(int e)
{
    canvas_2 &cv=reference_to<canvas_2>(pw);
    return cv.handle(e);

}

// axis
void axis::attach(Window &w)
{
    pw=new dynamic_axis(placement,loc,length,step,txt.label());

    own=&w;

}
void axis::set_scale(int sc)
{
  dynamic_axis& da=reference_to<dynamic_axis>(pw);
da.change_scale(sc);
}

//************************************************************************

Cnvs_grp::Cnvs_grp(Point xy,int ww,int hh,const string& s):Widget(xy,ww,hh,s,0)
{
   }

void Cnvs_grp::attach(Window & w)
{ // loc - верхняя левая точка canvas
 Canvas* p_cnw=new Canvas(loc,width(),hight());
 //Fl_Scroll*scr=new Fl_Scroll(loc.x(),loc.y(),width(),hight());
//scr->add(p_cnw);
 own=&w;
// canvas_2 * c_ptr=new canvas_2(loc.x()+20,loc.y(),width()-20,hight()-40,"");
// p_cnw->add(c_ptr);
// dynamic_axis* ax_ptr=new dynamic_axis(Axis_pos::horisontal,{loc.x()+20,loc.y()+(hight()-40)},width()-20,10,"axis_x");
// p_cnw->add(ax_ptr);
// dynamic_axis* ay_ptr=new dynamic_axis(Axis_pos::vertical,{loc.x()+20,loc.y()+(hight()-40) },hight()-40,10,"axis_y");
// p_cnw->add(ay_ptr);
 pw=p_cnw;
}

//void Cnvs_grp:: draw()
//{
////  Fl_Group:: draw_children();
//   // Canvas &gr=reference_to<Canvas>(pw);
//  Fl_Scroll &sc=reference_to<Fl_Scroll>(pw);
//  std::cout<<"draw begin\n";
//  sc.child(0)->draw();
//}

int Cnvs_grp::handle(int e)
{
 // Canvas &gr=reference_to<Canvas>(pw);
   Fl_Scroll &sc=reference_to<Fl_Scroll>(pw);
    return sc.handle(e);
}
Canvas* Cnvs_grp::canvas()
{
  Canvas &ptr=reference_to<Canvas>(pw);
  // Fl_Scroll &sc=reference_to<Fl_Scroll>(pw);
return &ptr;
  // return &ptr;
}

}
