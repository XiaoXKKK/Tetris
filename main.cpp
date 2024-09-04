#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "define.h"
#include "control.h"
#include "game.h"

using namespace std;


void init()
{
#ifdef _WIN32
    system("chcp 65001");
#endif
    tc::hideCursor();
    tc::clearScreen();
    tc::setCursor(1, 1);
    dw::window(1,1,9,6,"Hold");
    dw::window(1,10,12,22,"Tetriz");
    dw::window(7,1,9,16,"Status");
    dw::window(19,22,8,4,"Info");
    dw::window(1,22,8,18,"Next");

    gm::init();
    gm::startListener();    
}

void loop()
{
    int i = 1;
    while(gm::running)   
    {
        gm::process();


        tc::setCursor(10,4);
        cout << "FPS:" << ut::fps();
        tc::setCursor(12, 4);
        std::cout << "Level: " << gm::level;
        tc::setCursor(13, 4);
        std::cout << "Score: " << gm::score;
        tc::setCursor(14, 4);
        std::cout << "Lines: " << gm::lines;

        if(gm::end){
            dw::window(9, 12, 9, 3, "");
            tc::setCursor(10, ut::b2c(14));
            tc::setForeColor((int)Color::Red);
            std::cout << "Game Over!";
            this_thread::sleep_for(chrono::seconds(3));
            break;
        }

        // tc::setCursor(gm::row, ut::b2c(gm::col));
        // tc::setBackColor(15);
        // tc::setForeColor(214);  
        // cout << "  " << flush;
        dw::frame(gm::frame, 2, 11);
        dw::next(gm::next_pieces, 2, 23);
        dw::hold(gm::hold_piece, 2, 2);


        tc::resetColor();
        // this_thread::sleep_for(chrono::milliseconds(100));
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