#ifndef GAME_H
#define GAME_H

#include <functional>

#define GAME_SIZE_GRID_WIDTH 20
#define GAME_SIZE_GRID_HEIGHT 20

#define GAME_INIT_HEAD_LOC_X 10
#define GAME_INIT_HEAD_LOC_Y 10
#define GAME_INIT_BODY_SIZE 3
#define GAME_INIT_FORWARD RIGHT

namespace Game
{

    enum Status
    {
        IDLE,
        STEPING,
        ENDED,
    };

    enum Tile
    {
        NTILE,
        HEAD,
        BODY,
        COIN,
    };

    enum Direct
    {
        NDIR,
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    typedef struct Point
    {
        int x;
        int y;
        Point() : x(-1), y(-1) {}
        Point(int x, int y) : x(x), y(y) {}
    } Point;

    typedef std::function<void(int)> PtrScoreCallback;

    const int M_DX[5] = {0, 0, 0, -1, 1};
    const int M_DY[5] = {0, -1, 1, 0, 0};
    const Direct M_REVDIR[5] = {Direct::NDIR, Direct::DOWN, Direct::UP, Direct::RIGHT, Direct::LEFT};

    const Point NULL_POINT = Point(-1, -1);
    
    inline bool isNullPoint(const Point *p) {
        return p->x == -1 && p->y == -1;
    };
    inline void dirPoint(Point *p, Direct dir) {
        if(!isNullPoint(p)) { p->x += M_DX[dir]; p->y += M_DY[dir]; }
    };
    inline void dirPoint(Point *p, Direct dir, int d) {
        if(!isNullPoint(p)) { p->x += d*M_DX[dir]; p->y += d*M_DY[dir]; }
    }

    class Game
    {
    public:
        Game();
        ~Game();

    public:
        Tile tiles[GAME_SIZE_GRID_WIDTH][GAME_SIZE_GRID_HEIGHT];

        Status getGameStatus();

        void step();
        void coin();
        void setOpDirect(Direct dir);
        Direct getOpDirect();
        Direct getLastOpDirect();

        int getScore();
        int getSnakeLength();
        Point getHead();
        Point getTail();
        Point getBody(int index);

        void setOnScoreCallBack(PtrScoreCallback cb);
        void unsetOnScoreCallBack();
        void callOnScore();
    
    private:
        volatile Status gameStatus = Status::IDLE;
        Point queueSnake[GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT];
        int lengthSnake = 0;
        int headerSnake = 0;
        Direct prepOpDirect = Direct::NDIR;
        Direct thisOpDirect = Direct::NDIR;
        Direct lastOpDirect = Direct::NDIR;
        PtrScoreCallback ptrScoreCallback = nullptr;
    };
};

#endif // GAME_H
