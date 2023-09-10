#include "game.h"

#include <random>
#include <vector>

#define loopq(index) (((index) + GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT) % (GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT))
#define queueSnake(index) queueSnake[loopq(index)]
#define tiles(point) tiles[(point).x][(point).y]

using namespace Game;

Game::Game::Game()
{

    srand(time(NULL));

    for (int i = 0; i < GAME_SIZE_GRID_WIDTH; i++)
        for (int j = 0; j < GAME_SIZE_GRID_HEIGHT; j++)
        {
            this->tiles[i][j] = Tile::NTILE;
        }
    for (int i = 0; i < GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT; i++)
    {
        this->queueSnake(i) = NULL_POINT;
    }

    this->headerSnake = GAME_INIT_BODY_SIZE - 1;
    this->lengthSnake = GAME_INIT_BODY_SIZE;
    for (int i = 0; i < GAME_INIT_BODY_SIZE; i++)
    {
        this->queueSnake(headerSnake-i).x = GAME_INIT_HEAD_LOC_X + i*M_DX[M_REVDIR[Direct::GAME_INIT_FORWARD]];
        this->queueSnake(headerSnake-i).y = GAME_INIT_HEAD_LOC_Y + i*M_DY[M_REVDIR[Direct::GAME_INIT_FORWARD]];
        this->tiles(queueSnake(headerSnake-i)) = (i==0) ? (Tile::HEAD) : (Tile::BODY) ;
    }

}

Game::Game::~Game() {};

Status Game::Game::getGameStatus()
{
    return this->gameStatus;
}

void Game::Game::step()
{
    bool scored = false;
    if (this->gameStatus != Status::IDLE) return;
    this->gameStatus = Status::STEPING;
    if (this->prepOpDirect != Direct::NDIR)
    {
        this->lastOpDirect = this->thisOpDirect;
        this->thisOpDirect = this->prepOpDirect;
        this->prepOpDirect = Direct::NDIR;
    }
    if (this->lastOpDirect != Direct::NDIR)
    {
        this->tiles(this->queueSnake(headerSnake - lengthSnake + 1)) = Tile::NTILE;
        this->tiles(this->queueSnake(headerSnake)) = Tile::BODY;
        this->queueSnake(headerSnake+1) = this->queueSnake(headerSnake);
        this->headerSnake = (headerSnake + 1) % (GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT);
        dirPoint(&(this->queueSnake(headerSnake)), this->lastOpDirect);
        if (
            this->queueSnake(headerSnake).x < 0
            || this->queueSnake(headerSnake).x >= GAME_SIZE_GRID_WIDTH
            || this->queueSnake(headerSnake).y < 0
            || this->queueSnake(headerSnake).y >= GAME_SIZE_GRID_HEIGHT
            || this->tiles(this->queueSnake(headerSnake)) == Tile::BODY
        )
        {
            this->gameStatus = Status::ENDED;
            return;
        }
        else
        {
            if (this->tiles(this->queueSnake(headerSnake)) == Tile::COIN)
            {
                this->lengthSnake += 1;
                this->tiles(this->queueSnake(headerSnake - lengthSnake + 1)) = Tile::BODY;
                scored = true;
                if (this->lengthSnake == GAME_SIZE_GRID_WIDTH * GAME_SIZE_GRID_HEIGHT)
                {
                    this->gameStatus = Status::ENDED;
                    return;
                }
            }
            this->tiles(this->queueSnake(headerSnake)) = Tile::HEAD;
        }
    }
    this->gameStatus = Status::IDLE;
    if (scored) return this->callOnScore();
    else return;
}

void Game::Game::coin()
{
    std::vector<Point> listFreePoint;
    Point choice;

    if (this->gameStatus != Status::IDLE) return;
    for (int i = 0; i < GAME_SIZE_GRID_WIDTH; i++)
        for (int j = 0; j < GAME_SIZE_GRID_HEIGHT; j++)
            if (this->tiles[i][j] == Tile::NTILE)
                listFreePoint.insert(listFreePoint.end(), Point(i, j));
    if (listFreePoint.size() > 0)
    {
        choice = listFreePoint.at(rand() % listFreePoint.size());
        this->tiles(choice) = Tile::COIN;
    }
}

void Game::Game::setOpDirect(Direct dir)
{
    if (
        this->thisOpDirect != Direct::NDIR
        && dir != this->thisOpDirect
        && dir != M_REVDIR[this->thisOpDirect]
        || this->thisOpDirect == Direct::NDIR
        && dir != Direct::GAME_INIT_FORWARD
        && dir != M_REVDIR[Direct::GAME_INIT_FORWARD]
    )
        this->prepOpDirect = dir;
}

Direct Game::Game::getOpDirect()
{
    return this->thisOpDirect;
}

Direct Game::Game::getLastOpDirect()
{
    return this->lastOpDirect;
}

int Game::Game::getScore()
{
    return this->lengthSnake - GAME_INIT_BODY_SIZE;
}

int Game::Game::getSnakeLength()
{
    return lengthSnake;
}

Point Game::Game::getHead()
{
    if (lengthSnake >= 1)
    {
        return this->queueSnake(headerSnake);
    }
    else
    {
        return NULL_POINT;
    }
}

Point Game::Game::getTail()
{
    if (lengthSnake >= 1)
    {
        return this->queueSnake(headerSnake - lengthSnake + 1);
    }
    else
    {
        return NULL_POINT;
    }
}

Point Game::Game::getBody(int index)
{
    if (lengthSnake >= 1 && index >= 0 && index < lengthSnake)
    {
        return this->queueSnake(headerSnake - index);
    }
    else
    {
        return NULL_POINT;
    }
}

void Game::Game::setOnScoreCallBack(PtrScoreCallback cb)
{
    this->ptrScoreCallback = cb;
}

void Game::Game::unsetOnScoreCallBack()
{
    this->ptrScoreCallback = nullptr;
}

void Game::Game::callOnScore()
{
    if (this->ptrScoreCallback == nullptr) return;
    this->ptrScoreCallback(this->getScore());
}
