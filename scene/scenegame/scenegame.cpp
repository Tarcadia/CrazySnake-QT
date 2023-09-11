#include "scenegame.h"
#include "ui_scenegame.h"

SceneGame::SceneGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneGame)
{
    qDebug() << "Initing SceneGame...";
    ui->setupUi(this);
    this->timer = new QTimer();
    this->connect(this->timer, SIGNAL(timeout()), this, SLOT(updateGame()));

    this->pixmapHead = new QPixmap();
    this->pixmapBody = new QPixmap();
    this->pixmapCoin = new QPixmap();
    this->pixmapHead->load(":/res/head.png");
    this->pixmapBody->load(":/res/body.png");
    this->pixmapCoin->load(":/res/coin.png");

    for (int i = 0; i < sizeGridWidth; i++)
        for (int j = 0; j < sizeGridHeight; j++)
        {
            QWidget *widget = new QWidget(this);
            QLabel *label = new QLabel(widget);
            label->move(0, 0);
            label->setFixedSize(24, 23);
            label->setText("");
            // label->setText(QString::number(i) + "," + QString::number(j));
            label->setPixmap(*pixmapNull);
            label->setScaledContents(true);
            labelGrid[i][j] = label;
            ui->layoutGrid->addWidget(widget, j, i);
        }

    qDebug() << "Done init SceneGame.";
}

SceneGame::~SceneGame()
{
    delete ui;
    delete timer;
    delete pixmapNull;
    delete pixmapHead;
    delete pixmapBody;
    delete pixmapCoin;
    if (game != nullptr) delete game;
}

void SceneGame::callCmdStop()
{
    this->timer->stop();
    if (this->game != nullptr) delete this->game;
    this->game = nullptr;
    emit cmdStop();
}

void SceneGame::callCmdExit()
{
    emit cmdExit();
}

void SceneGame::setupGame()
{
    Game::Game *newGame = new Game::Game();
    Game::Game *oldGame = game;
    newGame->coin();
    newGame->setOnScoreCallBack([this](int score) {
        this->onScore(score);
    });
    this->game = newGame;
    this->timer->setSingleShot(false);
    this->timer->start(this->gameStepInterval);
    if (oldGame != nullptr) delete oldGame;
    return this->updateGame();
}

void SceneGame::updateGame()
{
    static Game::Tile lastTiles[GAME_SIZE_GRID_WIDTH][GAME_SIZE_GRID_HEIGHT];
    static Game::Status lastStatus = Game::Status::IDLE;
    const QPixmap *M_PIXMAP[4] = {this->pixmapNull, this->pixmapHead, this->pixmapBody, this->pixmapCoin};
    bool ended = false;

    if (this->game == nullptr) return;
    this->game->step();
    for (int i = 0; i < sizeGridWidth; i++)
        for (int j = 0; j < sizeGridHeight; j++)
            if (lastTiles[i][j] != this->game->tiles[i][j])
            {
                lastTiles[i][j] = this->game->tiles[i][j];
                this->labelGrid[i][j]->setPixmap(*M_PIXMAP[this->game->tiles[i][j]]);
                this->labelGrid[i][j]->setScaledContents(true);
            }
    ended = (lastStatus != Game::Status::ENDED && this->game->getGameStatus() == Game::Status::ENDED);
    lastStatus = this->game->getGameStatus();
    if (ended) return this->onEnded(this->game->getScore());
    else return;
}

void SceneGame::updateGameKeyDir(Game::Direct dir)
{
    if (this->game != nullptr) {
        this->game->setOpDirect(dir);
    }
}

void SceneGame::onScore(int score)
{
    this->ui->labelScore->setText(QString("Score: ") + QString::number(score));
    if (this->game != nullptr) this->game->coin();
    emit scored(score);
}

void SceneGame::onEnded(int score)
{
    this->timer->stop();
    if (this->game != nullptr) delete this->game;
    this->game = nullptr;
    emit ended(score);
}
