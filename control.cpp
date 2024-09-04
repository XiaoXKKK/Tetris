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
        {KEY_HARDDOWN, commdrop}
    };

    void keyEvent(){
        while (running)
        {
            if (locking) continue;
            command = _getch();
            if (commandMap.find(command) != commandMap.end())
            {
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
}
