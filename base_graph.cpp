#include "base_graph.h"
namespace Graph {



int Graph::Node::cnt_node=0;
Node* Node::insert(Node* n)
{
   cnt_node++;
   Node* c=_next; //   ука  n->_next=_next; // установить следующим для нового узла,следующий узел конечного элемента
   n->_next=c;
   n->_prev=this; // установили предыдущий для нового элемента (текущий элемент)
    _next=n;      //
    c->_prev=n;
   return n;
}

Node* Node:: remove() // удаляет текущий узел
{
    cnt_node--;
    _prev->_next=_next;
    _next->_prev=_prev;
    _prev=_next=this;
    return this;
}

//**************************Shape_t
 //рисует координаты относительно точки p
void Shape_t::draw_with_coord(Point p)
{
    Fl_Color old=fl_color();
    fl_color(lcolor.as_int());
    fl_line_style(ls.style(),ls.width());
  // рисование линии
    Vertex *w=v;
    //Point beg=v->point();

    for(;w->cw()!=v;w=w->cw())
    { Point beg=w->point()+p;
      Point end=w->cw()->point()+p;
      fl_line(beg.x(),beg.y(),end.x(),end.y());
    }
    fl_color(old);
    fl_line_style(0);
}

void Shape_t::draw() const
{
   Fl_Color old=fl_color(); // сохранить текуший цвет
   fl_color(lcolor.as_int());
   fl_line_style(ls.style(),ls.width());
    draw_lines();
   fl_color(old);
   fl_line_style(0);
}

void Shape_t::draw_lines() const
{
    // взять вершину
  Vertex *w=v;
  for(;w->cw()!=v;w=w->cw())
  {
   fl_line(w->point().x(),w->point().y(),w->cw()->point().x(),w->cw()->point().y());
  }

}

Shape_t::~Shape_t()
{ // удаляем по next() пока не дайдем до конца кольцевого списка
   // std::cout<<"Shape destruct\n";
    if(v!=nullptr) // если есть
    {
      Vertex *w=v->cw(); // на последователя
      while(w!=v)
      {
          delete w->remove();
          w=v->cw();
      }
      delete v;
    }
}

void Shape_t::rotate(Point p, double an)

    {Vertex*w=v;
    // вычисления угла в радианах
        double angle=an*3.1415/180;

        for(;;w=w->cw())
        {
            float x_rot= p.x()+(w->point().x()-p.x())*cos(angle)-(w->point().y()-p.y())*sin(angle);
            float y_rot= p.y()+((w->point().x()-p.x())*sin(angle))+((w->point().y()-p.y())*cos(angle));
            w->change({x_rot,y_rot});
            std::cout<<"rotate() :"<<w->point().x()<<" "<<w->point().y()<<" \n";
           if(w->cw()==v)
            break;
        }
    }
void Shape_t::change(Point p1, Point p2) //заменяет точку p1 точкой p2 если есть
{
try{
  Vertex cv(p1);
  Vertex *w=v->cw();
  while (w!=v)
  {
  if(*w==cv)
  {
   // Vertex * newVer=new Vertex(p2);
//std::cout<<"Yes\n";
      w->ccw()->insert(new Vertex(p2)); // w->ccw() вернет указатель на предыдущую вершину,
      delete w->remove();
     break;
  }
  w=w->cw();
  }
    }
   catch(std::exception ex)
    {
      std::cout<<"Error\n";
    }
}

void Shape_t::add_vertex(Point p)
{
 add(p);
}
Point Shape_t::point(int i) const
{
    int num_point=(i<size)?i:size;
Vertex* cur=v;
    for(int i=0;i<num_point;++i)
{
    cur=cur->cw();
}
    return cur->point();
}


bool Shape_t::compare(const Shape_t *tr) const
{
   if(size !=tr->size) return false;
// если размеры совпадают, сравниваем точки

   Vertex *cur=v; // текущая фигура
   Vertex* cmp=tr->v; // сравниваемая фигура
   for(;;cur=cur->cw(),cmp=cmp->cw())
   {
     if( cur!=cmp) return false;
   }
   return true;

}





// конструктор должен вычислять коэффициенты уравнения ax+by+c=0

line_t::line_t(Point p1,Point p2)
{
    a=p1.y()-p2.y();
    b=p2.x()-p1.x();
    c=p1.x()*p2.y()-p2.x()*p1.y();
    float min=10.0;
    while (min>1.0||min<-1.0)
    {
      min=(a<b)?((a<c)?a:c):((b<c)?b:c);
      if(min<fl_eps && min>-fl_eps) break;
        a/=min;
        b/=min;
        c/=min;
    }


  Shape_t::add(p1);
  Shape_t::add(p2);
 //вычислить длину и поворот по x
// длинна - избыточная информация, ее всегда можно вычислить

  float x_len=abs(p1.x()-p2.x());
  float y_len=abs(p1.y()-p2.y());
if(x_len==0||y_len==0)
{angle_rot=0;
} else
angle_rot=atan2(y_len,x_len);
}


line_t::line_t(Point p,float len,float an) :line_t(p,{float(p.x()+(len*cos(3.1415*(90-an)/180))),float(p.y()+len*cos(an*3.1415/180))})
   {
     // Shape_t::add({p.x()+0.5f,p.y()+0.5f});

     //вычисление угла
//      double angle=an*3.1415/180;

      angle_rot=an;

//      float y=len*cos(angle);
//      float x=len*cos(3.14*(90-an)/180);
//      Point end_p{p.x()+x,p.y()+y};

//  line_t(p,end_p);

     // Shape_t::add({p.x()+x+0.5f, p.y()+y+0.5f});


}


float line_t::length() const
{
    float x_len=point(1).x()-point(0).x();
    float y_len=point(1).y()-point(0).y();
    return sqrt(x_len*x_len+y_len*y_len);
}

void line_t::draw_lines() const
{
   Shape_t::draw_lines();
}


float line_t::normal(Point p) const
{
    return std::abs(a*p.x()+b*p.y()+c)/sqrt(a*a+b*b);
}

Point line_t::getPoint(Point &p) const
{ // найти длину нужна точка от которой отложен вектор len

 Point p1=begin();
 Point p2=end();

 float x4=((p2.x()-p1.x())*(p2.y()-p1.y())*(p.y()-p1.y())+p1.x()*pow(p2.y()-p1.y(),2)+p.x()*pow(p2.x()-p1.x(),2))/(pow(p2.y()-p1.y(),2)+pow(p2.x()-p1.x(),2));
 float y4=(p2.y()-p1.y())*(x4-p1.x())/(p2.x()-p1.x())+p1.y();

 std::cout<<"x4: "<<x4<<", y4: "<<y4<<"\n";
 //************

 float vec=normal(p);
    line_t ln(point(0),p);
    float len=ln.length();// line_t(point(0),p).length(); // отрезок из точки
   len=sqrt(len*len+vec*vec);
    float k=len/length();

//    std::cout<<"normal: "<<vec<<"\n";
//    std::cout<<"len_vect: "<<len<<"\n";

    // point =A+(B-A)*len/length;
    Point pt=end()-begin();
    pt={pt.x()*k,pt.y()*k};
    pt=begin()+pt;
    //Point p= Point {begin()+{pt.x()*k,pt.y()*k}} ;
    return pt;
}

void line_t::angle(float an)
{
  // изменить точку
     float beg_x=(begin().x()<end().x())?begin().x():end().x();
     float beg_y=(begin().y()<end().y())?begin().y():end().y();
Point rot { beg_x+std::abs(begin().x()-end().x())/2,beg_y+std::abs(begin().y()-end().y())/2}; //dx, dy
// установить все вершины относительно точки:
//  std::cout<<"Rotation point:"<<rot.x()<<" "<<rot.y()<<"\n";
//  std::cout<<"Begin "<<begin().x()<<" "<<begin().y()<<"\n";
//  std::cout<<"End "<<end().x()<<" "<<end().y()<<"\n";

rotate(rot,an);
angle_rot+=an;
angle_rot=(angle_rot<360)?angle_rot:(angle_rot-360);

  }

// положение точки и прямой

/*
   теория :
    операция Point1-Point0  возвращает разницу между точками, пару чисел на которые нужно изменить Point0 чтобы получить Point1 (т.к. Привыкли от большего отнимать меньшее)
   полагаем что p0 начальная точка, и находится ближе к началу координат, но в данном случае, какая из них ближе к началу координат неважно

  1. Получаем разницу между данными тремя точками, (в нашем случае между точками отрезка (1), и началом отрезка и третей точкой(2) )
  2. sa=ax*by-bx*ay    ??? непонятная величина
       НУЖНО УЧИТЬ ВЕКТОРЫ

если sa>0 точка расположена слева
если меньше справа,
  для дальнейших
*/

bool line_t:: get_side_ln(const Point &p) const
{
area_t art=LEFT_SIDE;//=get_side_area(p);
 float ofs=a*p.x()+b*p.y()+c;
if(ofs>0.0+fl_eps) art=LEFT_SIDE;
if(ofs>0.0-fl_eps) art=INTER_SIDE;
 else art=RIGHT_SIDE;
  // art содержит отношение прямой и переданной точки
if(art==INTER_SIDE) // проверяем сумму
{
    line_t l1{begin(),p};
    line_t l2{p,end()};
   if(((length()-(l1.length()+l2.length()))>-fl_eps) && (length()-(l1.length()+l2.length())<fl_eps))
    {  std::cout<<p.x()<<" "<<p.y()<<'\n';
       std::cout<<length()<<"\n";
        std::cout<<l1.length()<<" "<<l2.length()<<"\n";
       return true;
}

}
return false;
}

area_t line_t::get_side_area(const Point &p) const
{ /*
   переписать
   1. проверить на принадлежность прямой
   2. проверить, что длины отрезков образованных точкой в сумме равны длине отрезка
   */
  // 1. разница между данными точками
    Point da=point(1)-point(0);
    Point db=p-point(0);
    float sa=da.x()*db.y()-db.x()*da.y();
  //  std::cout<<"SA="<<sa<<"\n";
    if(sa>0.0 ) return LEFT_SIDE;
    if(sa<0.0 ) return RIGHT_SIDE;
  // дополнительные расчеты
if(point(0).isEqual(p)) return ORIGIN;
if(point(1).isEqual(p)) return DESTINATION;
if(da.x()*db.x()<0.0||da.y()*db.y()<0.0) return  BEHIND;
 float alen=sqrt(da.x()*da.x()+da.y()*da.y());
 float blen=sqrt(db.x()*db.x()+db.y()*db.y());
 if(alen<blen) return BEYOND;

//if(sqrt(da.x()*da.x()+da.y()*da.y())<sqrt(db.x()*db.x()+db.y()*db.y()))
//    return BEYOND;
return INTER_SIDE;
 }
  // разделены ли точки данным отрезком
bool line_t::separates(const Point &p1, const Point &p2) const
{
 area_t side1=get_side_area(p1);
 area_t side2=get_side_area(p2);
std::cout<<"side 1 = "<<side1<<"\n";
std::cout<<"side 2 = "<<side2<<"\n";
 if(side1==INTER_SIDE||side1==ORIGIN||side1==DESTINATION) return false ;
 if(side2==INTER_SIDE||side2==ORIGIN||side2==DESTINATION) return false;
 // если точки лежат на одной прямой но по разным концам
//if((side1!=side2) &&(side1==BEHIND||side1==BEYOND)&&(side2==BEHIND||side2==BEYOND)) return false;
 //std::cout<<"SeParates\n";
if(side1==BEYOND||side1==BEHIND) return false;

if(side2==BEYOND||side2==BEHIND) return false;
 return !(side1==side2);
}

bool line_t::intersect(const line_t &other) const
{
    return separates(other.begin(),other.end()); // если разделяет вершины отрезка то пересекается

}

bool line_t::contain(Point p)
{
    if(this->normal(p)<5) // если длина нормали к линии меньше 5 пикс
    {
      Point pt=getPoint(p); // получим точку пересечения с  нормалью
      if(this->get_side_ln(pt)) // если эта точка лежит на отрезке
     // if(line_t{p,pt}.separates(begin(),end()))
      return true;

    }
    return false;
}

void line_t::change(Point p1,Point p2)
{
  Shape_t::change(p1,p2); // меняем прежнюю вершину на p2
   line_t ln(begin(),end());
  a=ln.a;
  b=ln.b;
   c=ln.c;
}


// конец линии

// класс shape_t список связанных вершин, таким образом все линии даже Separates связанны между собой, что не правильно

// Poly_lines_t

void poly_lines_t::draw_lines() const
{
   //
 Shape_t::draw_lines();

}
bool poly_lines_t::contain(Point p)
{
 // пройти по всем вершинам, определив содержат ли они данную точку
for(int i=0;i<vertex_count()-1;++i)
{
 line_t ln(point(i),point(i+1));
  if(ln.contain(p))
   {  std::cout<<"Contain\n"<<" "<<i<<" "<<i+1<<"\n";
         return true;
    }
}
std::cout<<" not contain\n";
return false;
}

void poly_lines_t::add_vertex(Point p)
{
    if(vertex_count()==0)
    add(p,{p.x()+1,p.y()+1});
else add(p);
}



//***************************************************
// lines_t

void lines_t::add(Point p1, Point p2)
{
 //if(p1.isValid()&&p2.isValid())
    lines.push_back(new line_t{p1,p2});
//Shape_t::add(p1);
// Shape_t::add(p2);
}

void lines_t::add(const line_t& ln)
{
  lines.push_back(new line_t(ln.begin(),ln.end()));
//Shape_t::add(ln.begin());
//Shape_t::add(ln.end());
}



void lines_t::draw_lines() const
{
  for( unsigned i=0;i<lines.size();++i)
      lines[i]->draw();
//for(unsigned i=1;i<vertex_count();i+=2)
//{
//  fl_line(Shape_t::point(i-1).x(),Shape_t::point(i-1).y(),Shape_t::point(i).x(),Shape_t::point(i).y());
//}
}

Point lines_t::point(int i) const
{
   // перебираем все вершины всех линий, пока не достигнем указанной точки

    int num_line=(i<vertex_count())? i: vertex_count();
  //if(i%2==0)
  //{
     // return num_line]->point(0);
  //} // else return  lines[num_line]->point(1);
    return Shape_t::point(num_line);
}

int lines_t::vertex_count() const
{
    return   Shape_t::vertex_count();// lines.size()*2;
}
bool lines_t::contain(Point p)
{
    for(unsigned i=0;i<lines.size();++i)
    {
     if(lines[i]->contain(p))
         return lines[i];
    }
    return false;
}

}

