#include "gui_interface.h"
#include <sstream>
#include <iostream>


namespace  Graph {
}

//dyn_axis::dyn_axis(Orientation oor,Point xy,int len,int st,std::string s):orient{oor},length(len),step(st),lab{xy,s.c_str()}
//{ if(length<=0) return;
//   // scale=1.0;
//    Shape::add(xy); //
//      switch (oor)
//    {case none:
//          break;
//    case horisontal: // горизонтальная линия
//     lab.move(length,15);
//          Shape::add({xy.x()+length,xy.y()}); //зогружаем вторую точку
//        // строим деления
//        for(unsigned i=1;i<length/step;i++)
//        {
//          if((i )%10)
//            ls.add({xy.x()+i*step,xy.y()},{xy.x()+i*step,xy.y()+5}); //загружаем по 2 точки - линию
//         else
//          ls.add({xy.x()+i*step,xy.y()},{xy.x()+i*step,xy.y()+10}); //загружаем по 2 точки - линию

//        }
//        break;
//    case vertical:
//        //загрузим вторую точку
//          Shape::point(0)={xy.x(),xy.y()-length};
//          lab.move(-20,-length);
//    Shape::add({xy.x(),xy.y()});
//    // деления
//    for( unsigned i=1;i<length/step;++i)
//    {
//        if(i%10)
//            ls.add({xy.x()-5,xy.y()-i*step},{xy.x(),xy.y()-i*step});
//       else
//             ls.add({xy.x()-10,xy.y()-i*step},{xy.x(),xy.y()-i*step});
//    }

//        break;
//    }

//}
//void dyn_axis::draw_lines() const
//{ //double scale=0.02;
//   if(orient==none) return;

//   Shape::draw_lines();
//    lab.draw();
//    ls.draw();

//  // нужно пометить каждую линию,
//   std::stringstream ss ;
//    for(unsigned i=1;i<length/step-1;i++)
//    { ss.str("");

//    if((i+1)%10==0)
//      {
//          ss<<(i+1)*scale;
//          if(orient==horisontal){
//              //std::cout<<"Hello World\n";
//        fl_draw(ss.str().c_str(),ls.point(i*2 ).x(),ls.point((i)*2+1).y()+15);

//          }
//          if(orient==vertical){
//            int moving=ss.str().size()*10;
//              fl_draw(ss.str().c_str(),ls.point(i*2).x()-moving,ls.point((i)*2).y());
//          }
//        }
//    }

// }

//void dyn_axis::init(Orientation oor, Point px, int len, int st, std::string s)
//{
//    if(len<=0) return;

//    length=len;
//     // scale=1.0;
//    step=st;
//    lab.set_label(s);
//    lab.set_point(px);
//    Shape::add(px); //
//    orient=oor;
//    switch (oor)
//        {
//         case none:
//              return;
//        case horisontal: // горизонтальная линия
//         lab.move(length,15);
//              Shape::add({px.x()+length,px.y()}); //загружаем вторую точку
//            // строим деления
//            for(unsigned i=1;i<length/step;i++)
//            {
//              if((i )%10)
//                ls.add({px.x()+i*step,px.y()},{px.x()+i*step,px.y()+5}); //загружаем по 2 точки - линию
//             else
//              ls.add({px.x()+i*step,px.y()},{px.x()+i*step,px.y()+10}); //загружаем по 2 точки - линию

//            }
//            break;
//        case vertical:
//            //загрузим вторую точку
//              Shape::point(0)={px.x(),px.y()-length};
//              lab.move(-20,-length);
//        Shape::add({px.x(),px.y()});
//        // деления
//        for( unsigned i=1;i<length/step;++i)
//        {
//            if(i%10)
//                ls.add({px.x()-5,px.y()-i*step},{px.x(),px.y()-i*step});
//           else
//                 ls.add({px.x()-10,px.y()-i*step},{px.x(),px.y()-i*step});
//        }

//            break;
//        }
//draw();
//}}

// ********************************************************************************************
// методы Canvas






/*






Shape_t* Canvas::shape_on_move(Point pt) const
{
  // нужно проверять тип фигуры, простой или составной???
    //  составными могут быть типы lines, poly_lines(openLines,closedLines), и например ellipse(состоит из дуг окружности), трапеция
// для составных типов должны быть доступны изменения любой вершины,

    for(unsigned i=0;i<sh_t_vec.size();++i) // перебираем все фигуры
    {   // возможно следует сортировать вершины, и проверять, только те которые не меньше заданной точки, для фигур
      // для типа lines_t нужно перебирать линии
      //  for(unsigned j=1;j<sh_t_vec[i]->vertex_count();j++) // и все точки фигур
       //{
          //Shape_t*cur=nullptr;
          if(sh_t_vec[i]->contain(pt))
              return sh_t_vec[i];
          //if(cur!=nullptr)
            //  return cur;

      //   line_t ln(sh_t_vec[i]->point(j-1),sh_t_vec[i]->point(j));  // создаем линию
        // if(ln.normal(p)<6)  // если растояние до прямой меньше шести пикселей
         //{      // проверим, что точка лежит на отрезке, а не на прямой
         // Point pt=ln.getPoint(p);
          //  if(ln.get_side_ln(pt))
           // { return sh_t_vec[i];  // здесь нужно возвращать линию, а не фигуру lines
            //     }
        // }
       //}
    } return nullptr;   // если ненайдена, вернем null

}
int Canvas::handle(int e)
{

 bool fl_moving=false;
    std::stringstream ss;
    switch (e)
    {
   // данное событие нужно перенести на события окна, axis должен принадлежать окну
  case  FL_ENTER:
      std::cout<<"On Canvas\n";

        break;
  case FL_LEAVE:
       std::cout<<"Out Canvas\n";
        break;
    case FL_MOUSEWHEEL:
     { int div= Fl::event_dy();

      (div>0)?--index:++index;
       index=(index>0)?index:0;
       index=(index<4)?index:4;
}
     if(index>2)
     {
         ax_x.set_scale(diviration[index]);
        ax_y.set_scale(diviration[index]);

     } else
     {
         ax_x.set_scale(1.0/diviration[index]);
         ax_y.set_scale(1.0/diviration[index]);

     }

 // ax_x.draw();
// win->redraw();
  break;

   case FL_MOVE:
cur_mouse_point.x(Fl::event_x());
cur_mouse_point.y(Fl::event_y());

        break;

    case FL_DRAG:

 //cur_mouse_point={(Fl::event_x()),Fl::event_y()};
        break;


    case FL_PUSH:
//       cur_mouse_point={(Fl::event_x()),Fl::event_y()};


        break;
    case FL_RELEASE:



        break;



} // конец switch() для Canvas

   _tool->handle(e); // обработка событий инструмента

win->redraw();





r eturn e;
}

Shape_t * Canvas::set_focus()  // устанавливает фокус на фигуру
{
   //должна определить события  движения мыши и вернуть фигуру над которой курсор, или nullptr;

    return nullptr;
}

}

















*/







//*********************мусор

// if(div>0) // движение в низ уменьшаем масштаб
//     if(--index>0) // если есть куда уменьшать
//     {
//      ax_x.set_scale(1.0/diviration[index]);
//      ax_y.set_scale(1.0/diviration[index]);
//        }
//  if(div<0){
//      if(++index<4)
//      {
//          if(index>2)
//         {  ax_x.set_scale(diviration[index]);
//              ax_y.set_scale(diviration[index]);


//            } else {
//               ax_x.set_scale(1.0/diviration[index]);
//                ax_y.set_scale(1.0/diviration[index]);
//            }        }
//      }
