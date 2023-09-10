#include "sceneendgame.h"
#include "ui_sceneendgame.h"

SceneEndGame::SceneEndGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneEndGame)
{
    ui->setupUi(this);
}

SceneEndGame::~SceneEndGame()
{
    delete ui;
}

void SceneEndGame::recordScore(int score) {
    this->ui->labelScore->setText(
        this->rtStylePrefix + "Score: " + QString::number(score) + this->rtStyleSufix
    );
}

void SceneEndGame::endScore(int score)
{
    this->recordScore(score);
    this->show();
};

void SceneEndGame::callCmdStop()
{
    emit cmdStop();
}
