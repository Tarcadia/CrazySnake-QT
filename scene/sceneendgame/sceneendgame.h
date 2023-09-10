#ifndef SCENEENDGAME_H
#define SCENEENDGAME_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class SceneEndGame;
}

class SceneEndGame : public QWidget
{
    Q_OBJECT

public:
    explicit SceneEndGame(QWidget *parent = nullptr);
    ~SceneEndGame();

signals:
    void cmdStop();

public slots:
    void recordScore(int score);
    void endScore(int score);

private slots:
    void callCmdStop();

private:
    Ui::SceneEndGame *ui;
    QString rtStylePrefix = "<html><head/><body><p><span style=\" font-weight:700; color:#ffffff;\">";
    QString rtStyleSufix = "</span></p></body></html>";
    
};

#endif // SCENEENDGAME_H
