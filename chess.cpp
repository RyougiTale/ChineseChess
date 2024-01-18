#include <cstring>
#include "ai.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
// struct Position
// {
//     int x;
//     int y;
// };

class Chessman
{
public:
    // virtual std::string getName() = 0;
    virtual std::string getName() = 0;
    // Position position;
    int x;
    int y;
    Color color;
};

// enum Chessman{

// };
class Rook : public Chessman // 车
{
    std::string getName()
    {
        return "Rook";
    }
};
class Knight : public Chessman // 马
{
    std::string getName()
    {
        return "Knight";
    }
};
class Elephant : public Chessman // 象
{
    std::string getName()
    {
        return "Elephant";
    }
};

class Mandarin : public Chessman // 士
{
    std::string getName()
    {
        return "Mandarin";
    }
};

class King : public Chessman // 将
{
    std::string getName()
    {
        return "King";
    }
};

class Cannon : public Chessman // 炮
{
    std::string getName()
    {
        return "Cannon";
    }
};

class Pawn : public Chessman // 兵
{
    std::string getName()
    {
        return "Pawn";
    }
};
// <-

// extern Bot *bot1;
// extern Bot *bot2;
extern Bot bot1;
extern Bot bot2;

// global
Chessman *chessboard[11][10]; // 0 0 不用

class Player
{
public:
    Color color;
    Rook rooks[2];

    void init(Color color)
    {
        color = color;
        // 车
        rooks[0].x = 1;
        rooks[0].y = 1;
        rooks[1].x = 9;
        rooks[1].y = 1;
        chessboard[1][1] = &rooks[0];
        chessboard[9][1] = &rooks[1];

        rooks[0].color = rooks[1].color = color;
    }
};

class ChessBoard
{
public:
    Player player[2];
    Bot *bots[2];
    Action state;
    int idx; // 当前走棋人

    ChessBoard()
    {
    }

    void init(Color color) // init bot1的color
    {
        idx = (int)color;
        memset(chessboard, 0, sizeof(chessboard));
        player[0].init((Color)color);
        player[1].init((Color)(color ^ 1));
        bots[0]->Ready((Color)color);
        bots[1]->Ready((Color)(color ^ 1));
        state.fx = state.fy = state.tx = state.ty = 0;
        // chessboard =
    }

    // 调试完成后为了性能考虑可以关掉这个函数
    // check 还没写完, 先纯凭自觉好了, 我慢慢补
    bool check(Action &action)
    {
        // bot->
        int x = action.fx;
        int y = action.fy;
        int tx = action.tx;
        int ty = action.ty;
        if (chessboard[x][y] == nullptr)
        {
            cout << "no chess here" << endl;
            return false;
        }
        if (chessboard[x][y]->color != player[idx].color || chessboard[tx][ty]->color == player[idx].color)
        {
            cout << "color not right" << endl;
            return false;
        }
        if (x < 1 || x > 9 || y < 1 || y > 10 || tx < 1 || tx > 9 || ty < 1 || ty > 10)
        {
            cout << "overflow" << endl;
            return false;
        }
        if (auto *rook = dynamic_cast<Rook *>(chessboard[x][y]))
        {
            if (x == tx)
            {
                // 进退
                if (ty < y)
                {
                    std::swap(ty, y);
                }
                for (int i = y + 1; i < ty; i++)
                {
                    if (chessboard[x][i] != nullptr)
                    {
                        cout << "[rook] barrier" << endl;
                        return false;
                    }
                }
            }
            else if (y == ty)
            {
                // 平
                if (tx < x)
                {
                    std::swap(tx, x);
                }
                for (int i = x + 1; i < tx; i++)
                {
                    if (chessboard[i][y] != nullptr)
                    {
                        cout << "[rook] barrier" << endl;
                        return false;
                    }
                }
            }
            else
            {
                cout << "[rook] not line" << endl;
                return false;
            }
        }
        else if (auto *knight = dynamic_cast<Knight *>(chessboard[x][y]))
        {
        }
        else if (auto *elephant = dynamic_cast<Elephant *>(chessboard[x][y]))
        {
        }
        else if (auto *mandarin = dynamic_cast<Mandarin *>(chessboard[x][y]))
        {
        }
        else if (auto *king = dynamic_cast<King *>(chessboard[x][y]))
        {
        }
        else if (auto *cannon = dynamic_cast<Cannon *>(chessboard[x][y]))
        {
        }
        else if (auto *pawn = dynamic_cast<Pawn *>(chessboard[x][y]))
        {
        }
        else
        {
            cout << "impossible" << endl;
        }
        return true;
    }

    void process(Action &state)
    {
        if (chessboard[state.tx][state.ty] != nullptr)
        {
            cout << "be eaten" << endl;
        }
        chessboard[state.tx][state.ty] = chessboard[state.fx][state.fy];
        chessboard[state.fx][state.fy] = nullptr;
    }

    void play()
    {
        int limit = 600;
        while (limit--)
        {
            Action new_state = bots[idx]->Move(state);
            if (check(new_state))
            {
                process(new_state);
                if (chessboard[new_state.tx][new_state.ty] != nullptr && chessboard[new_state.tx][new_state.ty]->getName() == "King")
                {
                    cout << idx << " win, " << (idx ^ 1) << " lose" << endl;
                    bots[idx]->GameDebug(false, "win");
                    bots[1 ^ idx]->GameDebug(false, "lose");
                    return;
                }
                state = std::move(new_state);
                idx++;
                idx %= 2;
            }
            else
            {
                bots[idx]->GameDebug(true, "chess invalid, please try again");
            }
        }

        if (limit == 0)
        {
            cout << "draw" << endl;
            bots[0]->GameDebug(false, "draw");
            bots[1]->GameDebug(false, "draw");
        }
    }
};

int main()
{
    int turn = 2; // 回合
    ChessBoard cboard;
    cboard.bots[0] = &bot1;
    cboard.bots[1] = &bot2;

    for (int t = 1; t < turn; t++)
    {
        if (t & 1)
        {
            // bot1执红, bot2执黑
            cboard.init((Color)0);
            cboard.play();
        }
        else
        {
            // bot2执红, bot1执黑
            cboard.init((Color)1);
            cboard.play();
        }
    }
    return 0;
}
