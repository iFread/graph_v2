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






int main ()
{
 //   Graph::axis(Axis_pos::horisontal,{0,9},100,10,"");

//    test_gui_interfase();
    using namespace  Graph;
    test_window win({100,100},950,640,"test_window");
    return gui_run();
    //return 0;
}
