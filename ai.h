#ifndef AIH
#define AIH
#include <string>
enum Color
{
    RED,
    BLACK
};

struct Action
{
    int fx; // from_x
    int fy; // from_y
    int tx; // to_x
    int ty; // to_y
};

class Bot
{
public:
    virtual void Ready(Color color) = 0;
    virtual Action Move(Action &actoin) = 0;
    virtual void GameDebug(bool error, std::string message) = 0;
};

#endif
