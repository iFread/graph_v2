#include "base_tool.h"
#include "gui_interface.h"
#include "gui.h"
#include "canvas_2.h"
namespace Graph
{
 // изменяем отображение переданной фигуры
// ps:: так же следует предусмотреть группу фигур


// redraw() -  помечает виджет как нуждающийся в перересовке, значит нужно либо перерисовывать весь холст,
 // либо создавать отдельный виджет,
/*

 вызов функции selection() должен изменять отображение переданной фигуры???
  перирисовка окна

*/


Shape_t* Tool::selecting(Shape_t *sh)
{
 // как перерисовать линию ?
 //sh->draw();  // нарисует ту же линию?

 // --->>   // в цикле пройтись по вершинам, и по каждой точке нарисовать окружность, радиусом 2 пик,
  //  нарисовать линию, толшиной два пикселя, для каждой вершины
    // при этом можно исключить отрисовку этой линии в основном отображении, используя invisible()
//if(active_shape.size())
    return sh;
}

void Tool::add( Shape_t * sp)
{
 sp->set_style(Line_style(Line_style::solid,2));
    active_shape.push_back(sp);
}

void Tool::remove(Shape_t *sh)
{
   for(unsigned i=0;i<active_shape.size();++i)   // erase() работает с итераторами   //unsigned i=0;i<active_shape.size();++i)
   {
     if(active_shape[i]==sh) // если совпадают адреса
     {
         Shape_t* ptr=active_shape[i];
         active_shape.erase(active_shape.begin()+i-1); // удаляется ли из Canvas
        // return ptr;
     }
   } //return nullptr;
}

void Tool:: clear()
{
   for(unsigned i=0;i<active_shape.size();++i)
   {
     active_shape[i]->set_style(Line_style(Line_style::solid,0));
   }
  active_shape.clear();
}

int Tool::division(Shape_t* sp,int e)
{ clear();

        for(unsigned j=1;j<sp->vertex_count();++j) //j<sh_t_vec[i]->vertex_count();++j)
        {


          line_t ln(sp->point(j-1),sp->point(j));
         // std::cout<<"YES\n";
          //float nrm=ln.normal(cur_mouse_point); // нормаль к прямой
         // найти точку на прямой, основание нормали
    Point cur_mouse=Point{Fl::event_x(),Fl::event_y()};
      if(ln.normal(cur_mouse )<6) {
         Point pt=ln.getPoint(cur_mouse);

         if(ln.get_side_ln(pt)) {

           add(sp);
           return 1;

            }
           }

        }


  return 0;

    }



void Tool::draw() // базовая отрисовка выделенной линии
{
    for(unsigned i=0;i<active_shape.size();++i) // для каждой вершины рисуем окружность и линию толшиной больше чем данная
    {
    //    active_shape[i]->set_style(Line_style(Line_style::solid,2));

       for(unsigned j=0; j<active_shape[i]->vertex_count() ;++j)
       {
          Point p=active_shape[i]->point(j);
         fl_color(35);
          fl_pie(p.x()-3,p.y()-3,6,6,0,360); // рисуем окружность, для каждой вершины
   //fl_line(active_shape[i]->point(j).x(),active_shape[i]->point(j).y(),active_shape[i]->point(j+1).x(),active_shape[i]->point(j+1).y());

       } // для каждой фигуры рисуем линию
//active_shape[i]->draw();

    }

}

int Tool::handle(int e)
{ // базовая обработка события

    bool hand_make=false; // если событие не обработано, вернуть 0, иначе 1
   switch (e)
  {
   case FL_MOVE:

       // std::cout<<"cur on move :: "<<cnvs->get_mouse().x()<<" "<<cnvs->get_mouse().y()<<"\n";
       break;
   case FL_PUSH:
       if(Fl::event_button1())
        {  // проверить на наличие фигуры, если нет проверяем, что нажатие было в окрестности фигуры,
     //   std::cout<<"Shape_t vec size = "<<cnvs->get_size()<<"\n";
       Shape_t *pt=cnvs->move_to_shape();//shape_on_move();//cnvs->get_mouse());
    std::cout<<"cur ::: "<<cnvs->get_mouse().x()<<" "<<cnvs->get_mouse().y()<<"\n";
    clear();
       if(pt!=nullptr)
        {  add(pt);
         std::cout<<"new shape_t add in active \n";
       } }
       else if(Fl::event_button3())
         {
           if(!empty())
               clear();  // удаляем выделенные фигуры
          }
             hand_make=true;      //return 1; //
       break;
   case FL_RELEASE:

       break;



    }
   if(hand_make) return 1;
   return 0;
}
void Tool::change(Point p)
{
   // подумать над аргументами фигуры
// для линии менять последнюю точку, для фигуры правую нижнюю либо левую верхнюю

 active_shape[size()-1]->change(active_shape[size()-1]->point(active_shape[size()-1]->vertex_count()-1),p);
}
 //_____________________________________________________________

void Creating_tool::modify_base(Point p)
{
Tool::change(p);
}

int Creating_tool::handle(int e)
{
/*
   bool fl_work=false;
    switch (e)
    {
    case FL_PUSH:
  {
   if(Fl::event_button1()){
       clear();
   // curr_shape=
            create(cnvs->get_mouse()); //создаем фигуру, и добавляем в active
     std::cout<<"Add new shape_t\n";
   //  cnvs->add(sh); // добавляем ее в список
     //   add(sh);
    active(true);
    fl_work=true;
   } else if(Fl::event_button3())
   {
    //  clear();
   }
    }
        break;
    case FL_MOVE:

        break;
    case FL_DRAG:   //движение с нажатой клавишей
     if(Fl::event_button1()) //
     {
         modify_base(cnvs->get_mouse()); // обновляем
    fl_work=true;
     }

     break;

    case FL_RELEASE:
            // если есть модифицируемая фигура(или фигуры), нужно добавить ее в Shape_t canvas
        //  для этого перебрать список фигур canvas, и список active_shape,
    if(active())
    {
      cnvs->add(active_shape[0]);
    //  remove(curr_shape);
   //  curr_shape=nullptr;
    clear();
       active(false);
    }
     // сбрасываем инструмент
        fl_work=true;
        break;
    }
   if(fl_work) return 1;


*/
     return 0;
}




Shape_t * Pen:: create(Point p)
{   // создаем
    Shape_t * ln=new line_t(p,{p.x()+1,p.y()+1});
    add(ln);    // добавить в список инструмента
    return ln;  // опасность утечки памяти, т.к. нельзя возвращать адрес в никуда
         // возможно продумать  удаление созданных фигур,
}   //

int Pen::handle(int e) // перегружает handle для Pen
{
    static  bool pushed=false;

    switch (e)
    {
// для каждого case нужен switch(Fl::event_buttons())

    // нажатие лкм должно добавлять новую вершину к фигуре,
    case FL_PUSH:
    if(Fl::event_button1())
       { pushed=true;}
   // нажатие правой кнопки должно добавлять фигуру, без последней вершины

    if(Fl::event_button3())
    {
       for(auto &el:active_shape)
           delete el;
       active_shape.clear();
     pushed=false;
    active(false);
   }
        break;

    case FL_DRAG:

        break;
    case FL_MOVE:

     if(active())
         modify_base(cnvs->get_mouse());
        break;
    case FL_RELEASE: // по Release производим захват точек.
    //  event_buttons() не может обработать этот случай,

        if(pushed) {
  if(active()) // если линия уже создается загрузим ее в вектор
   {
     cnvs->add(active_shape[0]);
     active_shape.clear();
     active(false); //

  } else    // иначе создаем новую фигуру
    {      create(cnvs->get_mouse());  // захватываем точку
     active(true);
    }
    pushed=false;
    }
        break;

    default: break;


    }
    return 0;
}
// *********************************************
//методы Poly_line

Shape_t* Poly_line::create(Point p)
{

    poly_lines_t* pl=new poly_lines_t(poly_lines_t::openLines,p,p);
  // add(pl);
   active(true); // устанавливаем активное состояние
   return pl;
}

void Poly_line::modify_base(Point p)
{
Tool:: change(p);
}


int Poly_line::handle(int e)
{
    static bool pushed=false;

    switch (e)
    {
    case FL_PUSH:
 if(Fl::event_button1()) //
     pushed=true;

 if(Fl::event_button3()) // при нажатии ПКМ меняем состояние active - false, заканчиваем фигуру и добавляем ее в sh_t_vec
   {
//   if(active()){

//      poly_lines_t* ln=static_cast<poly_lines_t*>(active_shape[0]);
//        ln->remove();
//     // проверка на наличие вершин, если удаляется предпоследняя вершина, должна удаляться вся фигура

//     if(ln->vertex_count()==1)
//        active_shape.clear();
//    }


   //active(false);     //
   //cnvs->add(active_shape[0]);
   //clear();
 }
        break;
    case FL_MOVE:
if(active()) // если активна меняем последнюю точку
   modify_base(cnvs->get_mouse());
// std::cout<<"Active yes\n";
        break;
     case FL_DRAG:

        break;
     case FL_RELEASE: // загружаем новые вершины, по отжатию кнопки

     switch (Fl::event_button())
        {
         case FL_LEFT_MOUSE: // отпустив лкм, нужно добавить новую вершину,
if(active()) // если фигура уже созданна
     {      active_shape[0]->add_vertex(cnvs->get_mouse());
       //std::cout<<"Left button up\n";
      }
  else
 {
 add(create(cnvs->get_mouse()));
 //add(pl);
   }
       break;
        case FL_RIGHT_MOUSE:     // перенос из секции Fl_PUSH
            if(active()) // если линия уже создается загрузим ее в вектор, если будет что загружать
             {  // нужно удалить последнюю вершину, т.к. не предполагается ее загружать
               poly_lines_t* ln=static_cast<poly_lines_t*>(active_shape[0]);
               ln->remove();

               if(Fl::get_key(FL_Control_L))
                 { if(ln->vertex_count()==1)
                   { active_shape.clear();
                     active(false);
                   }
                 }
          else {
                cnvs->add(active_shape[0]);
               active_shape.clear();
               active(false); //
               }
             }
            break;
        case FL_MIDDLE_MOUSE:
            break;
        }

        break;

    default:

        break;
    }

    return 0;
}
 // отрисовать жирным выделенную линию, и выделить вершины
void Poly_line::draw()
{
    for(unsigned i=0;i<active_shape.size();++i) // для каждой вершины рисуем окружность и линию толшиной больше чем данная
    {
    //    active_shape[i]->set_style(Line_style(Line_style::solid,2));

       for(int j=0; j<active_shape[i]->vertex_count()-1;++j)
       {
          Point p=active_shape[i]->point(j);
         fl_color(35);
          fl_pie(p.x()-3,p.y()-3,6,6,0,360); // рисуем окружность, для каждой вершины
   // каждая линия рисуется отдельно, нужно определить где указатель мыши
          fl_line(active_shape[i]->point(j).x(),active_shape[i]->point(j).y(),active_shape[i]->point(j+1).x(),active_shape[i]->point(j+1).y());

       } // для каждой фигуры рисуем линию
//active_shape[i]->draw();

    }
}


}
