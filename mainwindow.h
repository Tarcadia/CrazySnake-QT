#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene/scenemenu/scenemenu.h"
#include "scene/scenehelp/scenehelp.h"
#include "scene/scenegame/scenegame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setSceneMenu();
    void setSceneHelp();
    void setSceneGame();
    void setSceneEndGame();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
