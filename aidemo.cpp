#include "ai.h"
#include <iostream>
using std::cout;
using std::endl;

class BotDemo : public Bot
{
    void Ready(Color color) override
    {
        cout << "my color is " << color << endl;
        if (color == Color::RED)
        {
            // red
        }
        else
        {
            // black
        }
        // init();
    }
    Action Move(Action &action) override // action给4个数, 表示对方棋子的起步xy, 和落点xy
    {
        if (action.fx == 0)
        {
            // first move as red
        }
        else
        {
            // 对手的走棋
            cout << "from" << action.fx << " " << action.fy << " to " << action.tx << " " << action.ty << endl;
        }

        // 例子: 车1进1
        Action my_action;
        my_action.fx = 1;
        my_action.fy = 1;
        my_action.tx = 1;
        my_action.ty = 2;
        return my_action;
    }

    void GameDebug(bool error, std::string message) override
    {
        if (error)
        {
            cout << "error: " << message << endl;
        }
        else
        {
            cout << "normal end: " << message << endl;
        }
    }
};

BotDemo bot1;
BotDemo bot2;

