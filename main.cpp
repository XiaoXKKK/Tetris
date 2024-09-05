#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "define.h"
#include "control.h"
#include "game.h"
#include "window.h"

using namespace std;


void init()
{
#ifdef _WIN32
    system("chcp 65001");
#endif
    tc::hideCursor();
    tc::clearScreen();
    tc::setCursor(1, 1);

    ui::show_windows();
    ui::show_help();

    gm::init();
    gm::startListener();    
}

void loop()
{
    int i = 1;
    while(gm::running)   
    {
        gm::process();

        ui::show_info();
        ui::show_game();

        std::this_thread::sleep_for(15.625ms);
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