#ifndef BASE_TOOL_H
#define BASE_TOOL_H
#include "base_graph.h"

namespace Graph {


  // базовый класс для инструментов,
/*
   1.определяет возможные типы и функцию получения типа
   2. определяет выделение фигуры,(или группы фигур)
   3. // Zoom - так же должен быть инструментом



*/

/*
 canvas отслеживает перемещение мыши и предоставляет инструменту указатель на Shape_t (фигуру, которая находится под курсором)
 либо нулевой указатель
/
*/

// вариант 1 Tool имеет свой список фигур, и отображает его
class canvas_2;
class Tool
{
public:
    enum tool_type {base_tool,creating_tool,modify_tool,transform_tool};
//Возможно использовать указатель на widget, унаследовать от Fl_Widget
    Tool(canvas_2* cnv):_type{base_tool},cnvs{cnv} {} // по умолчанию присваивает базовый тип
    // устанавливаем объект для работы

    tool_type type()const {return _type;}
 //void ?
  Shape_t* selecting(Shape_t* sh); // изменяет отображение переданной фигуры (выделяет фигуру)
 void add( Shape_t * sp); // возможно Shape_t&*
void remove(Shape_t* sh); // удаляет из списка фигуру

int division(Shape_t* p,int e);
void clear();
bool empty() const{return active_shape.empty();}

  void change(Point p); // установитиь точку i в значение p
// нужно учитывать что здесь передается адрес Shape_t, который так же будет использован в Canvas

  virtual void draw();
int size(){return active_shape.size();}
        // пока событие передается ввиде целого числа,
virtual int handle(int e);  //  в дальнейшем определить свой класс события
virtual ~Tool(){active_shape.clear();}

protected:
 tool_type _type; // тип инструмента
  canvas_2 *cnvs;     // указатель на виджет Widget, (унаследовать от Widget)

    Tool(canvas_2* ptr,Tool::tool_type tp):_type{tp},cnvs{ptr}{}
 std::vector<Shape_t*> active_shape; // список активных фигур, с которыми будет работать инструмент
private:


};

 //  обозвать Line
// возможно создать общий доерний класс Creating_tool(интерфейс для создающих классов) и объеденить методы




class Creating_tool:public Tool     // общий для создающих
{
    // конструктор скрыт, т.к. нельзя создать объект класса, неизвестно что он создает
protected:
    Creating_tool(canvas_2*ptr):Tool{ptr,Tool::creating_tool},state{false}{}
 // вспомогательные функции
 virtual void modify_base(Point p);     // базовые модификации при создании
    bool active() const {return state;}
    void active(bool st){state=st;}
public:
    int handle(int e) override; // перегрузка
    virtual  Shape_t *create(Point p)=0;   // создание фигуры определяется для каждого инструмента
private:
    bool state;
    Shape_t* curr_shape;

};

class Pen:public  Creating_tool
{
public:
    Pen(canvas_2 *ptr):Creating_tool(ptr) {}
   Shape_t* create(Point p) override; // создать объект || так объекты создаются параллельно осям,
    // созданный объект помещается оба контейнера : в контейнер sh_t_vec и active_vec
    // после отпускания мыши, для типов create контейнер  active_shape очищается
  // void  modify_base(Point p);  // базовая модификация объекта, изменяет размер, поворачивает - базовый поворот осуществляется от точки создания,
  // bool active() const {return state;}
  // void active(bool st){state=st;}
int handle(int e) override;
 };

class Poly_line:public Creating_tool
{
public:
    Poly_line(canvas_2 *cnv):Creating_tool(cnv){}

  Shape_t* create (Point p) override;
protected:
  int handle(int e) override;
void modify_base(Point p) override;
void draw() override;

};



class Rect:public Creating_tool
{
 Shape_t* create(Point p) override;

 int handle(int e) override;

};

}
#endif // BASE_TOOL_H
