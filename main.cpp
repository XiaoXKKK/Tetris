#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "define.h"
#include "control.h"
#include "game.h"

using namespace std;


void init()
{
    tc::hideCursor();
    gm::init();
    gm::startListener();    
}

void loop()
{
    int i = 1;
    while(gm::running)   
    {
        tc::clearScreen();
        tc::setCursor(1,1);
        dw::window(1,1,9,6,"Hold");
        dw::window(1,10,12,22,"Tetriz");
        dw::window(7,1,9,16,"Status");
        dw::window(19,22,8,4,"Info");
        dw::window(1,22,8,18,"Next");
        tc::setCursor(10,4);
        cout << "FPS:" << ut::fps();

        tc::setCursor(gm::row, ut::b2c(gm::col));
        tc::setBackColor(15);
        tc::setForeColor(214);
        cout << "  " << flush;
        tc::resetColor();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void exit()
{
    tc::showCursor();
    tc::clearScreen();
    tc::setCursor(1,1);
    cout<<"Goodbye!"<<endl;
}

int main ()
{
    init();
    loop();
    exit();
    return 0;
}