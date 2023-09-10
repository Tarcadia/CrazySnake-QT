#ifndef SCENEMENU_H
#define SCENEMENU_H

#include <QWidget>

namespace Ui {
class SceneMenu;
}

class SceneMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SceneMenu(QWidget *parent = nullptr);
    ~SceneMenu();

signals:
    void cmdGame();
    void cmdHelp();
    void cmdExit();

private slots:
    void callCmdGame();
    void callCmdHelp();
    void callCmdExit();

private:
    Ui::SceneMenu *ui;
};

#endif // SCENEMENU_H
