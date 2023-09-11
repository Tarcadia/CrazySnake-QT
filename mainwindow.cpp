
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QKeyEvent>

#include "scene/scenemenu/scenemenu.h"
#include "scene/scenehelp/scenehelp.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // sceneMenu = new SceneMenu(this);
    // sceneHelp = new SceneHelp(this);
    // sceneGame = new SceneGame(this);
    ui->setupUi(this);
    this->setCentralWidget(this->ui->widgetScene);

    QObject::connect(this->ui->sceneMenu, SIGNAL(cmdExit()), this, SLOT(close()));
    QObject::connect(this->ui->sceneMenu, SIGNAL(cmdGame()), this, SLOT(setSceneGame()));
    QObject::connect(this->ui->sceneMenu, SIGNAL(cmdHelp()), this, SLOT(setSceneHelp()));
    QObject::connect(this->ui->sceneHelp, SIGNAL(cmdStop()), this, SLOT(setSceneMenu()));
    QObject::connect(this->ui->sceneGame, SIGNAL(cmdStop()), this, SLOT(setSceneMenu()));
    QObject::connect(this->ui->sceneGame, SIGNAL(cmdExit()), this, SLOT(close()));
    QObject::connect(this->ui->sceneGame, SIGNAL(ended(int)), this, SLOT(setSceneEndGame()));
    QObject::connect(this->ui->sceneEndGame, SIGNAL(cmdStop()), this, SLOT(setSceneMenu()));

    QObject::connect(this->ui->sceneMenu, SIGNAL(cmdGame()), this->ui->sceneGame, SLOT(setupGame()));
    QObject::connect(this->ui->sceneGame, SIGNAL(scored(int)), this->ui->sceneEndGame, SLOT(recordScore(int)));
    QObject::connect(this->ui->sceneGame, SIGNAL(ended(int)), this->ui->sceneEndGame, SLOT(endScore(int)));
    QObject::connect(this, SIGNAL(keyGame(Game::Direct)), this->ui->sceneGame, SLOT(updateGameKeyDir(Game::Direct)));

    this->setSceneMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSceneMenu()
{
    //Magic Number controlled by QStackedWidget widgetScene indexes;
    this->ui->widgetScene->setCurrentIndex(0);
}

void MainWindow::setSceneHelp()
{
    //Magic Number controlled by QStackedWidget widgetScene indexes;
    this->ui->widgetScene->setCurrentIndex(1);
}

void MainWindow::setSceneGame()
{
    //Magic Number controlled by QStackedWidget widgetScene indexes;
    this->ui->widgetScene->setCurrentIndex(2);
}

void MainWindow::setSceneEndGame()
{
    //Magic Number controlled by QStackedWidget widgetScene indexes;
    this->ui->widgetScene->setCurrentIndex(3);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (this->ui->widgetScene->currentIndex() == 2)
    {
        Game::Direct opDir = Game::Direct::NDIR;
        switch (event->key())
        {
        case Qt::Key_Up:
            opDir = Game::Direct::UP;
            break;
        case Qt::Key_Down:
            opDir = Game::Direct::DOWN;
            break;
        case Qt::Key_Left:
            opDir = Game::Direct::LEFT;
            break;
        case Qt::Key_Right:
            opDir = Game::Direct::RIGHT;
            break;
        
        default:
            break;
        }

        emit keyGame(opDir);
    }
}
