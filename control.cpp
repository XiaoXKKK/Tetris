#include "control.h"
#include "define.h"
#include "game.h"


namespace gm
{
    char command;

    std::map<char, std::function<void()>> commandMap{
        {KEY_Q, commquit},
        {KEY_W, commrotate},
        {KEY_S, commdown},
        {KEY_A, commleft},
        {KEY_D, commright},
        {KEY_SPACE,commdrop}
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
    void commrotate(){
        rotate();
    }
    void commdown(){
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
