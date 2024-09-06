#include "control.h"
#include "define.h"
#include "game.h"


namespace gm
{
    char command;

    std::map<char, std::function<void()>> commandMap{
        {KEY_QUIT, commquit},
        {KEY_ROTATECW, commrotatecw},
        {KEY_ROTATECCW, commrotateccw},
        {KEY_ROTATE180, commrotate180},
        {KEY_SOFTDOWN, commdown},
        {KEY_LEFT, commleft},
        {KEY_RIGHT, commright},
        {KEY_HARDDOWN, commdrop},
        {KEY_HOLD, commhold},
        {KEY_HELP, commhelp},
        {KEY_RESET, commreset}
    };

    void keyEvent(){
        while (running)
        {
            char tmp = tc::getch();
            if (locking) continue;
            if (commandMap.find(tmp) != commandMap.end())
            {
                command = tmp;
                if(helping && command != KEY_HELP && command != KEY_QUIT)
                {
                    continue;
                }
                if(end && command != KEY_RESET && command != KEY_QUIT)
                {
                    continue;
                }
                commandMap[command]();
            }
        }
             
    }
    void startListener()
    {
        std::thread t(keyEvent);
        t.detach();
    }
    void commquit()
    {
        quit();
    }
    void commrotatecw(){
        rotate(1);
    }
    void commrotateccw(){
        rotate(3);
    }
    void commrotate180(){
        rotate(2);
    }
    void commdown() {
        down();
    }
    void commleft(){
        left();
    }
    void commright(){
        right();
    }
    void commdrop()
    {
        drop();
    }
    void commhold()
    {
        hold();
    }
    void commhelp()
    {
        help();
    }
    void commreset()
    {
        reset();
    }
}
