#include "test_app.h"
using namespace Graph;

test_window::test_window(Point xy,int ww,int hh,const string &s):Graph::Window(xy,ww,hh,s.c_str()),

    grp({100,20},x_max()-120,y_max()-20,"canvas"),
   // scrll({100,10},x_max()-120,y_max()-30),
    //{grp.position().x(),grp.position().y()},grp.width()+20,grp.hight(),"scroll"),
    tool(Point(15,10),70,20,"tool"),
    poly_line(Point(15,35),70,20,"Poly_line"),in_window(Point(int(120),int(y_max()-20)),100,20,"cur_coord")
{


 // attach(scrll);
  attach(grp);
   attach(tool);
   attach(poly_line);
    poly_line.callback(cb_gtPens,(void*)&grp);
   attach(in_window);
}



void cb_gtPens(Fl_Widget*,void* data)
 {
    Cnvs_grp *gr=reinterpret_cast<Cnvs_grp*>(data);

    Canvas* cn=gr->canvas(); // reinterpret_cast<Canvas*>(data);

  if(cn->tool())
 {     cn->clear_tool();
      std::cout<<"tool is good\n";
          }
    //  Graph::Pen* pn=new Graph::Pen (cn);
 Poly_line*pn=new  Poly_line(cn->get_canvas());

 cn->set_tool(pn); //static_cast<Graph::Tool*>(data));

}

//void test_window::redraw()
//{ std::cout<<"Here is resize shape\n";
//   // this->redraw();
// grp.redraw();
// Window::redraw();

////}
// x_ax.init(dyn_axis::horisontal, Point(120,int(y_max()-40)),x_max()-130,10,"x_coord");
// x_ax.set_scale(1);

//y_ax.init(dyn_axis::vertical, Point(120,int(y_max()-40)),y_max()-50,10,"y_coord");
// y_ax.set_scale(1);
//  attach(cnvs);
//   attach(x_ax);
 //  attach(y_ax);
//x_ax{Axis_pos::horisontal,Point{120, y_max()-40},x_max()-130,10,"x_coord"},
// y_ax{Axis_pos::vertical,Point{120, y_max()-40},y_max()-50,10,"y_coord"},
//  cnvs(Point{120, 10},x_max()-130,y_max()-50,""),
