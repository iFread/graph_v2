#include <iostream>
#include "point.h"
#include "binder_lib.h"
#include "base_gui_v2.h"
#include <fstream>
#include <sstream>
#include "gui_interface.h"
#include "base_graph.h"
 #include"gui.h"
#include "test_app.h"

using  std::cout;
using std:: endl;

void tst1()
{
   Graph::Window win(800,600,"Test");
   Graph::line_t ln( {200.0f,200.0f}, 300, 45);

    cout<< ln.angle()  <<endl;
  //  ln.change({100,30},{230,400});
cout<<ln.begin().x()<<" "<<ln.end().x()<<"\n";
    ln.angle(30)  ;
     //  cout<< ln.angle()  <<endl;
  ln.angle(60);
   //  ln.angle(180);
  ln.angle(45);
      cout<< ln.angle()  <<endl;

    win.attach(ln);
    Graph::gui_run();
 ;
}

void test1();
 void sub_func(Graph::area_t t);

 void test_polyline();
 void test_poly2();

 void test_polygon();

 void test_rect();

 void test_func();
   // функции для графиков:
 double one(double);
 double slope(double);
 double square(double);


 // рисование граффика из файла
 struct Distribution
 {
   int year,young,  middle, old;
 };

 std::istream & operator>>(std::istream & is,Distribution &d)
 {
     char ch1=0;
     char ch2=0;
     char ch3=0;
     Distribution dd;
     if(is>>ch1>>dd.year>>ch2>>dd.young>>dd.middle>>dd.old>>ch3)
     {
         if(ch1!='('||ch2!=':'||ch3!=')')
         {
           is.clear(std::ios_base::failbit);
           return is;
         }

     } else return is;
    d=dd;
    return is;
 }
// класс для преобразования координат
 // масштабирование для axis
class Scale
{
 int cbase;
 int vbase;
 double scale;
public:
 Scale(int b,int v,double s):cbase(b),vbase(v),scale(s){}
 int operator()(int v) const {return  cbase+(v-vbase)*scale;}
};
 // маркированные линии
// можно выбрать отображение в начале линии, или в конце
class mark_line:public Graph::Shape
{

public:
    mark_line( std::string s=""):label({0,0},s.c_str()){orig=nullptr; } // пустая линия
    mark_line(Point p1,Point p2,std::string s=""):label{p1,s.c_str()}
    {
        Shape::add(p1);
        Shape::add(p2);
        orig=&point(0);
    }
    void add(Point p1,Point p2) // добавить либо одну, либо две точки
    {

       Shape::add(p1);
       Shape::add(p2);
       orig=&point(0);
    }
void text_position(Point p)
{ int x_pos;
    int y_pos;
   //Point tp;//={p.x()-(label.label().size()/2*10),p.y() };
    x_pos=p.x()-label.label().size()/2*10;
  if(p.isEqual(begin()))
 {
    y_pos=p.y()-5;
   }
    //tp={tp.x(),p.y()-5};
    //tp.y()=p.y()-5;
  if(p.isEqual(end()))
{
  //x_pos=
  y_pos=p.y()-5;
  }
     // tp={tp.x() ,p.y()-5};
  label.set_point(Point(x_pos,y_pos));
    //label.Text{*orig,label}        //set_point(0,*orig);
}
Point begin(){return point(0);}
Point end(){return point(1);}

protected:
void draw_lines() const
{
  if(color().visible)  {
    for(int i=1;i<num_of_point();i+=2)
            {
               fl_line(point(i-1).x(),point(i-1).y(),point(i).x(),point(i).y());
            }
  }
label.draw();
}

    private:

Graph::Text label;
 Point * orig;
};

// сам dyn_axis может содержать основную линию
//  mark_line содержит нумерованные линии //



/*
нужна функция масштаба, которая для каждой точки в пределах axis возвращает координаты точки в окне,
Point p;
p.x= begin+cnt_div*scale;
    // начало отсчета (начало шкалы)
    // количество делений* scale // // scale=0.1, div =10; //
    // begin=5.0;
        // по шкале точка расположена по x=6.0
     на экране точка расположена
        // point(0).x -начало объекта axis,
        // +количество делений *step
        // 50 +10*5= 100 pix

 Таким образом точки должны храниться по координатам axis,
 а отображаться по координатам экрана

1. представить shape интерфейсом,
2. унаследованные от shape фигуры имеют свои данные (вершины, направления обхода)
3. предоставляют window данные для отображения фигур,
    ...
 4 фигуры сохраняются как double, значения x,y привязаны к шкале axis, а не положению на экране,
   при отрисовке draw_lines()  класс vertex должен предоставлять данные точки (point - положение на экране)



*/

//    using ptrFunc = bool(*)(int,int);
 // аналагично
       //typedef bool(*ptrFunc)(int,int);


void test_popul_yapan();// построение графиков
void test_gui_interfase();
void test_dyn_axis();
using ptr11=void(*)();



void simpleFun(ptr11 ptr)
{


std::cout<<"foood\n";
ptr();

}

void test_fu()
{
std::cout<<"test fu\n";
}

class a{
ptr11 pt;
public:
 a(ptr11 pp) {pt=pp;}
 void setFunc(ptr11 pp){pt=pp;}
 void call(){pt();}
};

typedef void(a::*ptr)() ;
class b
{
 //void (a::*ptr)(); // указатель на метод класса a
ptr  pp;
a* ar;
public:
b(a* aa,ptr p1){ar=aa;pp=p1;}
 void test_1(){ pp;}





};
//************************************************************************************


 int main ()
{
  //   Graph::axis(Axis_pos::horisontal,{0,9},100,10,"");

 //    test_gui_interfase();
     using namespace  Graph;
     test_window win({100,100},950,640,"test_window");
     return gui_run();
     //return 0;
}

/*

void cb_gtPens(Fl_Widget*,void* data)
{
  Graph::Canvas* cn=  reinterpret_cast<Graph::Canvas*>(data);

 if((cn->tool()!=nullptr))

 cn->clearTool();

   //  Graph::Pen* pn=new Graph::Pen (cn);
 Graph::Poly_line*pn=new Graph::Poly_line(cn);
 cn->set_tool(pn); //static_cast<Graph::Tool*>(data));
}

void cb_gtTool(Fl_Widget*,void* data)
{
 Graph::Canvas*cn=reinterpret_cast<Graph::Canvas*>(data);
 if(cn->tool()!=nullptr)
     cn->clearTool();
 Graph::Tool* tl=new Graph::Tool(cn);
cn->set_tool(tl);

}

 void test_gui_interfase()
 {
     using namespace Graph;

     Graph::Window win(800,600,"Test interfase");
   using namespace Graph;
     Canvas cnvs(&win,"test");
     Out_box crd_bx({100,550},100,20,"coord XY:");

     //   t_line l_tool ;
  //   rect_tool rtl;
 //  Tool tl(&cnvs);
  // Pen pen(&cnvs);
    cnvs.set_tool(new Tool(&cnvs)); //&tl);
     // cb_tools(&pen,&cnvs);
     Button gtPen({10,10},70,20,"Pen");//,[](Address1,Address aadr ){std::cout<<"Calback\n";Canvas* cn=static_cast<Canvas*>(aadr); cn->set_tool((new Pen(cn)));});// cb_tools(&tl,&cnvs));//[ &pen](Address, &cnvs){static_cast<Canvas*>(&cnvs)->set_tool(&pen);});
     Button gtTool({10,40},70,20,"Tool");

     win.attach(gtTool);
     win.attach(gtPen);
   //  crd_bx.attach(win);
    win.attach(crd_bx);
     gtPen.callback(cb_gtPens, &cnvs);
    gtTool.callback(cb_gtTool,&cnvs);
    //
    crd_bx.put("Hello World");


     win.position(100,100);
//win.attach(cnvs);
win.add(cnvs);

  gui_run();
 // std::cout<<"End\n";
 }
*/

// void test_dyn_axis()
// {
//     Graph::Window win(640,480,"Test axis 2");
//     using namespace Graph;
//     win.position(100,100);
//     dyn_axis x_ax(dyn_axis::horisontal,{50,430},500,10,"x_coord");

//     dyn_axis y_ax(dyn_axis::vertical,{50,430},400,10,"y_coord");
//x_ax.set_scale(0.01);
//y_ax.set_scale(0.01);
//     win.attach(x_ax);
//     win.attach(y_ax);
//     Graph::gui_run();

// }

 void test_rect()
 { using namespace Graph;
     Graph::Window win(640,480,"Test Rectangle");
 win.position(100,200);
     Rectangle rec1({150,100},200,100);
    Rectangle rec2({50,50},{250,150});
    mark_line ln({100,300},{300,100},"10");
    ln.text_position(ln.begin());
 //   rec2.add({300,300});

//    rec1.set_fill_color(Color::blue);
//  rec2.set_fill_color(Color(25));
//win.attach(rec1);
//win.attach(rec2);
//Text txt{{300,250},"Hello_World!"};
//txt.set_label("Hello, New Brave World ");
//txt.set_font_size(15);
//win.attach(txt);
//rec2.move(400,0);
win.attach(ln);
    gui_run();
 }




 void test_popul_yapan()// построение графиков
 {
     constexpr int xmax=600;
     constexpr int ymax=400;
      // расстояние до левого и нижнего края
     constexpr int offset_x=100; // от левого края до y
     constexpr int offset_y=60; // от нижнего края до x
     // пространство за осями
     constexpr int xspace=40;
     constexpr int yspace=40;
      // длины осей
     constexpr int xlength=xmax-offset_x-xspace;
     constexpr int ylength=ymax-offset_y-yspace;

     constexpr int base_year=1960;
     constexpr int end_year=2040;

     constexpr double xscale= double(xlength)/(end_year-base_year);
     constexpr double yscale= double (ylength)/100.0;
Scale xs(offset_x,base_year,xscale);
Scale ys(ymax-offset_y,0,-yscale);
Graph::Window win({100,100},xmax,ymax,"Aging Japan");

using namespace Graph;
Axis x(Axis::horisontal,{offset_x,ymax-offset_y},xlength,(end_year-base_year)/10, "year 1960      1970      1980      1990      2000      2010      2020      2030      2040");
 x.label.move(-100,0);
 Axis y(Axis::vertical,{offset_x,ymax-offset_y},ylength,10,"% of population");

 Lines children{Lines::OpenLines};
 Lines adults{Lines::OpenLines};
 Lines aged {Lines::OpenLines};
 //открытие файла
 std::ifstream ifs;
 ifs.open("japanece-age-data.txt");
 if(!ifs.is_open()) return;
    for(Distribution d;ifs>>d;)
    {
        //if(d.year<base_year||d.year>end_year) return;
        //if(d.year+d.middle+d.old!=100) return;
        const int x=xs(d.year);
    //   children.add((x,ys(d.young)));
     //   adults.add({x,ys(d.middle)});
      //  aged.add({x,ys(d.old)});
    }

win.attach(x);
win.attach(y);

win.attach(children);
win.attach(adults);
win.attach(aged);
gui_run();

 }
 void test_func()
 {
     constexpr int xmax=640;
     constexpr int ymax=480;

     constexpr int x_orig=xmax/2;
     constexpr int y_orig=ymax/2; // центр окна
      Point orig{x_orig,y_orig};
      // диапазон [-10, 11]
      constexpr int r_min=-10;
      constexpr int r_max=11;
      constexpr int n_points=400; // количество точек
       // масштабные множители
       constexpr int x_scale=30;
       constexpr int y_scale=30;

      Graph::Window win(Point{100,100},xmax,ymax,"Function graphics");
      using namespace Graph ;
     Function s1(one,r_min,r_max,orig,n_points,x_scale,y_scale);
     Function s2(slope,r_min,r_max,orig,n_points,x_scale,y_scale);
//     Function s3(square,r_min,r_max,orig,n_points,x_scale,y_scale);
//   Function s4(cos,r_min,r_max,orig,n_points,x_scale,y_scale);
//   Function s5(sin,r_min,r_max,orig,n_points,x_scale,y_scale);
//   Function s6([](double x){return cos(x)+slope(x);},r_min,r_max,orig,n_points,x_scale,y_scale);
   //     Text ts1(Point{100,y_orig-40},"one");
//     Text ts2({100,y_orig+y_orig/2-20 },"x/2");
//     Text ts3({x_orig-100,20},"x*x");

     Function s7(exp,-10,10,orig,200,x_scale,y_scale);
     constexpr int xlength =xmax-40;
     constexpr int ylength=ymax-40;

     Axis x(Axis::horisontal,{20,y_orig},xlength,xlength/x_scale,"one notch==1");

     Axis y(Axis::vertical,{x_orig,ylength+16},ylength,ylength/y_scale,"one notch==1");

x.set_color(Color::red);
y.set_color(Color::red);
//s5.set_color(Color::green);
//s4.set_color(Color::magneta);
//s6.set_color(Color::dark_red);
s7.set_color(Color::magneta);

win.attach(x);
win.attach(y);


win.attach(s1);
win.attach(s2);
win.attach(s7);
//win.attach(s3);
//win.attach(s4);
//win.attach(s5);
//win.attach(s6);
//     win.attach(ts1);
//     win.attach(ts2);
//      win.attach(ts3);
     win.set_label("Function graphing: label functions");
     gui_run();


 }
 double one(double){return 1;}
 double slope(double xx)
 {
     return xx/2;
 }
 double square(double xx)
 {
     return xx*xx;
 }


 void test_polygon()
 {
     using namespace Graph ;
     Graph::Window win(640,480,"Test polylyne2");

       Polygon ln;//(Lines::ClosedLines);
       ln.add({100,100},{150,200});
       ln.add({250,250},{300,200});
      ln.add({ 270,100});
       win.attach(ln);



     gui_run();


 }

void test_poly2()
{ using namespace Graph ;
    Graph::Window win(640,480,"Test polylyne2");

 Lines ln (Lines::ClosedLines);
  ln.add({100,100},{150,200});
  ln.add({250,250},{300,200});

win.attach(ln);



gui_run();
}

 void test_polyline()
{ using namespace Graph;
  Graph::Window win(640,480,"PolyLines");

  Lines ln ;// {Lines::ClosedLines};
int wx=640;
int wy=480;
int x_grid=80;
int y_grid=40;
ln.set_color(Color(99));

for(int x=x_grid;x<wx;x+=x_grid)
{
    ln.add(Point{x,0},Point{x,wy});
}
for(int y=y_grid;y<wy;y+=y_grid)
{
    ln.add(Point{0,y},Point{wx,y});
}
 win.attach(ln);
 gui_run();

}


void test1(){
    //using    Graph::Window;
    //using Graph::Line ;
    using namespace Graph;

    Graph::Window win(600,400,"Hello");

  Segment ln(Point(100,100),Point(200,200));
 // ln.move(-20,-50);
  ln.set_color(Color(30));
  //ln.change_direct();
Point p1{300,300};
//std::srand(time(0));
//  for(int i=0;i<400;i++)
// {  float xx= float (std::rand()%200+30) ;
//     float yy=float(std::rand()%200+50);
//   std::cout<<"Point ("<<xx<<","<<yy<<") =";

//     sub_func(ln.get_area({xx,yy}));
// }
sub_func(ln.get_area({150,150}));
sub_func(ln.get_area({250,250}));
sub_func(ln.get_area({50,50}));
sub_func(ln.get_area({150,200}));
sub_func(ln.get_area({200,150}));
sub_func(ln.get_area({199,199}));
sub_func(ln.get_area({200,200}));
//sub_func(ln.get_area(p1));
  std::cout<<ln.length()<<std::endl;
win.attach(ln);
 gui_run();
}


void sub_func(Graph::area_t t)
{  using namespace Graph ;
    switch (t)
    { case INTER_SIDE:
            std::cout<<"INTER_SIDE\n";
            break;
      case LEFT_SIDE:
         std::cout<<"LEFT_SIDE\n";
         break;
      case RIGHT_SIDE:
        std::cout<<"RIGHT_SIDE\n";
        break;
    case BEYOND:  // впереди
        std::cout<<"BEYOND\n";
        break;
    case BEHIND: // позади
        std::cout<<"BEHIND\n";
        break;
    case ORIGIN:
        std::cout<<"ORIGIN\n";
        break;
    case DESTINATION:
        std::cout<<"DESTINATION\n";
        break;
    }

}
