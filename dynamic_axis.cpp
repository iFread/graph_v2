#include "dynamic_axis.h"
#include <Fl/fl_draw.H>
#include <iostream>
#include <sstream>

namespace Graph {



void dynamic_axis::init(Point xy,int len,int st)
{
    length=len;
    step=st;
    lab.set_point(xy);
 ls.clear(); // очистить прежниие вершины
 // следует предусмотреть возможность откладывать начало как с низу поля, так и сверху
     ls.add({xy.x(),xy.y()+length}); // первая точка, начальная
     switch (placement)
     {
       case none:
         return;
       case horisontal:
           Fl_Widget::resize(xy.x(),xy.y(),length,default_hight); // высота виджета по умолчанию
          lab.move(length-50,default_hight+5); //
         ls.add({xy.x()+length,xy.y()});
         // рисуем линии с шагом step;
         for(int i=1;i<length/step;++i)
         { if(i%10)
                 ls.add({xy.x()+i*step,xy.y()+5},{xy.x()+i*step,xy.y()});
             else
                  ls.add({xy.x()+i*step,xy.y()+10},{xy.x()+i*step,xy.y()});
         }

         break;
     case vertical:
     { // верхняя левая точка должна быть правой нижней (в дальнейшем возможно правой верхней)
         // видимо здесь наоборот передается правая нижняя точка
       xy.x(xy.x()-default_width);
       xy.y(xy.y()-length); // получили левую верхнюю точку
       Point beg={xy.x() ,xy.y()+length}; //для отсчета с низу
        Fl_Widget::resize(xy.x(),xy.y(),default_width,length);
        // переместить подпись, т.к lab установлена относительно начала отсчета
        lab.move(-default_width,-(length+10));
        // т.к. первая точка была внизу участка, вторая вверху
        ls.add({xy.x(),xy.y()});
        for( unsigned i=1;i<length/step;++i)
        {
            if(i%10)
                ls.add({beg.x()+15,beg.y()-i*step},{beg.x()+20,beg.y()-i*step});
           else
                ls.add({beg.x()+10,beg.y()-i*step},{beg.x()+20,beg.y()-i*step});
        }
           break;


         }
}
redraw();
}

//void  dynamic_axis::init(Axis_pos pos,Point xy,int len,int st,  std::string s)
//{ //if(len<0) return; //возможно откладывать в обратную сторону
//    length=len;
// // точка xy - нулевая точка шкалы, виджет будет строиться от нее
// placement=pos;
//step=st ;

//// располагаем виджет в
//  lab.set_label(s);

//lab.set_point(xy);
//// теперь перерисовать линии
//ls.add({xy.x(),xy.y()+length}); // первая точка в низу
//switch (placement)
//{
// case none:
//    return;
// case horisontal:
//   // xy.x(xy.x()+20);
//    Fl_Widget::resize(xy.x() ,xy.y(),len,20); // 20, для того чтобы поместить деления и подписи
// lab.move(len-50,25); // переместить текст в конец шкалы
//  ls.add({xy.x()+len,xy.y()}); // вторая точка общей линии
//    // рисуем линии с шагом step; // в draw()?

//  for(unsigned i=1;i<length/step;i++)
//  {
//    if((i )%10)
//      ls.add({xy.x()+i*step,xy.y()+5},{xy.x()+i*step,xy.y()}); //загружаем по 2 точки - линию

//   else
//    ls.add({xy.x()+i*step,xy.y()+10},{xy.x()+i*step,xy.y()}); //загружаем по 2 точки - линию

//  }
//    break;
//case vertical:
//{    xy.x(xy.x()-20);
//    xy.y(xy.y()-length);
//    Point beg={xy.x(),xy.y()+length};
//    Fl_Widget::resize(xy.x() ,xy.y(),20,length);
// lab.move(-20,xy.y()-length-10); // в верх линии
// ls.add({xy.x(),xy.y()}); // вторая вверху
//  // линии рисуем в draw();
// for( unsigned i=1;i<length/step;++i)
// {
//     if(i%10)
//         ls.add({beg.x()+15,beg.y()-i*step},{beg.x()+20,beg.y()-i*step});
//    else
//         ls.add({beg.x()+10,beg.y()-i*step},{beg.x()+20,beg.y()-i*step});
// }
//    break;
//    }
//}

//redraw();
//}

void dynamic_axis::draw()
{
  // Рисуем контур
    if(placement==vertical)
    fl_rectf(x(),y(),20,length,FL_DARK1);
    else
      fl_rectf(x(),y(),length,20,FL_DARK1);

        ls.draw();
       lab.draw();
  //рисуем подписи делений
std::stringstream ss;
Fl_Color old=fl_color();
fl_color(FL_BLACK);

for(unsigned i=2;i<ls.num_of_point();i+=2) // перебираем вершины со второй, т.к. [0-1] - основная ось
  {

  ss.str("");
if((i/2)%10==0){
    double value=1.0;
    value=(index<2)?1.0/diviration[index]:1.0*diviration[index];
 ss<<(i/2)*value;              //2-1,4 -2, 6 -3 ,8 -4
    if(placement==horisontal)
    fl_draw(ss.str().c_str(),ls.point(i-2).x(),ls.point(i-2).y()+15);
  if(placement==vertical)
      fl_draw(ss.str().c_str(),ls.point(i-2).x()-15,ls.point(i-2).y());
}
}
fl_color(old);

}
void dynamic_axis::update(Point xy, int len)
{
  length=len;
  ls.clear();
  // if(placement==vertical) xy.x(xy.x()-20);
// init(placement,xy,len,step,lab.label());
 //Fl_Widget::redraw();
init(xy,len,step);
}

void dynamic_axis::resize(int xx, int yy, int ww, int hh)  // x, y - верхняя левая точка
{

 std::cout<<"X ="<<xx<<" Y= "<<yy<<" W = "<<ww<<" H = "<<hh<<"\n";
   if(placement==vertical){
   update({xx+ww,yy+hh },hh);
std::cout<<"vertical\n";
    }
 if(placement==horisontal)
     update({xx,yy},ww);
  //Fl_Widget::resize(xx,yy,ww,hh);
}


int dynamic_axis::handle(int e)
{

    switch (e)
    {
    case FL_MOUSEWHEEL:
    { int div= Fl::event_dy();

     (div>0)?--index:++index;
      index=(index>0)?index:0;
      index=(index<4)?index:4;
}
//    if(index>2)
//    {
//         set_scale(diviration[index]);
//       ax_y.set_scale(diviration[index]);

//    } else
//    {
//        ax_x.set_scale(1.0/diviration[index]);
//        ax_y.set_scale(1.0/diviration[index]);

//    }



        break;

    }
  redraw();
  return 0;
}

}
