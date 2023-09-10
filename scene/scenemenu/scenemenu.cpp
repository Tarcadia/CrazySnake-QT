#include "scenemenu.h"
#include "ui_scenemenu.h"

SceneMenu::SceneMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneMenu)
{
    qDebug() << "Initing SceneMenu...";

    ui->setupUi(this);
    
    qDebug() << "Done init SceneMenu.";
}

SceneMenu::~SceneMenu()
{
    delete ui;
}

void SceneMenu::callCmdGame()
{
    emit this->cmdGame();
};

void SceneMenu::callCmdHelp()
{
    emit this->cmdHelp();
};

void SceneMenu::callCmdExit()
{
    emit this->cmdExit();
};