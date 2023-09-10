#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

#include "game.h"

namespace Ui {
class SceneGame;
}

class SceneGame : public QWidget
{
    Q_OBJECT

public:
    explicit SceneGame(QWidget *parent = nullptr);
    ~SceneGame();

public:
    const int sizeGridWidth = GAME_SIZE_GRID_WIDTH;
    const int sizeGridHeight = GAME_SIZE_GRID_HEIGHT;
    const int gameStepInterval = 500;

signals:
    void cmdStop();
    void cmdExit();
    void scored(int score);
    void ended(int score);

public slots:
    void setupGame();
    void updateGame();

private slots:
    void callCmdStop();
    void callCmdExit();

private:
    void onScore(int score);
    void onEnded(int score);

private:
    Ui::SceneGame *ui;
    QTimer *timer;
    Game::Game *game = nullptr;
    
    QLabel *labelGrid[GAME_SIZE_GRID_WIDTH][GAME_SIZE_GRID_HEIGHT];
    QPixmap *pixmapNull = new QPixmap();
    QPixmap *pixmapHead = static_cast<QPixmap*>(nullptr);
    QPixmap *pixmapBody = static_cast<QPixmap*>(nullptr);
    QPixmap *pixmapCoin = static_cast<QPixmap*>(nullptr);

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENEGAME_H
