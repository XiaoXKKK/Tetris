#include "terminal.h"
#include "utils.h"
#include "draw.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void init()
{
    tc::clearScreen();
    tc::hideCursor();
    tc::setCursor(1,1);
    dw::window(1,1,9,6,"Hold");
    dw::window(1,10,12,22,"Tetriz");
    dw::window(7,1,9,16,"Status");
    dw::window(19,22,8,4,"Info");
    dw::window(1,22,8,18,"Next");
}

void loop()
{
    int i = 1;
    while(true)
    {
        tc::setCursor(10,4);
        cout << "FPS:" << ut::fps();

        tc::setCursor(5, 10);
        tc::setBackColor(15);
        tc::setForeColor(214);
        cout << "    " << flush;
        tc::resetColor();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void exit()
{
    tc::showCursor();
}

int main ()
{
    init();
    loop();
    exit();
    return 0;
}