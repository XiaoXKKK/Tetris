#include "terminal.h"
#include "define.h"

#define CSI "\033["

void tc::setCursor(int r, int c, std::ostream &os)
{
    os << CSI << r << ";" << c << "H";
}

void tc::setForeColor(int c, std::ostream &os)
{
    os << CSI << "38;5;" << c << "m";
}

void tc::setBackColor(int c, std::ostream &os)
{
    os << CSI << "48;5;" << c << "m";
}
void tc::resetColor(std::ostream &os)
{
    os << CSI << "0m";
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
#ifdef _WIN32
    return _getch();
#else 
    char c;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
#endif
}
