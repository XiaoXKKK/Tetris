#include "terminal.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
int main ()
{
    // cout << "\033[5;10H" << "\033[38;5;214m" << "Hello World!" << "\033[0m" << endl;
    int i = 1;
    tc::hideCursor();
    while(true)
    {
        tc::clearScreen();
        tc::setCursor(i++, 10);
        tc::setBackColor(15);
        tc::setForeColor(214);
        cout << "    " << flush;
        tc::resetColor();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    return 0;
}