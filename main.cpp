#include "terminal.h"
#include "utils.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void init()
{
    tc::clearScreen();
    tc::hideCursor();
}

void loop()
{
    int i = 1;
    while(true)
    {
        tc::clearScreen();

        tc::setCursor(1,1);
        cout << "FPS:" << ut::fps();

        tc::setCursor(i++%10, 10);
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