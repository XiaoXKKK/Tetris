#include "terminal.h"
#include "define.h"

#define CSI "\033["

void tc::setCursor(int r, int c)
{
    std::cout << CSI << r << ";" << c << "H";
}

void tc::setForeColor(int c)
{
    std::cout << CSI << "38;5;" << c << "m";
}

void tc::setBackColor(int c)
{
    std::cout << CSI << "48;5;" << c << "m";
}

void tc::resetColor()
{
    std::cout << CSI << "0m";
}

void tc::clearScreen()
{
    std::cout << CSI << "2J";
}

void tc::hideCursor()
{
    std::cout << CSI << "?25l";
}

void tc::showCursor()
{
    std::cout << CSI << "?25h";
}

bool tc::kbhit()
{
    return std::cin.rdbuf()->in_avail();
}

char tc::getch()
{
    return std::cin.get();
}
