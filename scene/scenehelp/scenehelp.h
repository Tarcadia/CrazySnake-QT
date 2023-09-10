#ifndef SCENEHELP_H
#define SCENEHELP_H

#include <QWidget>

namespace Ui {
class SceneHelp;
}

class SceneHelp : public QWidget
{
    Q_OBJECT

public:
    explicit SceneHelp(QWidget *parent = nullptr);
    ~SceneHelp();

signals:
    void cmdStop();

private slots:
    void callCmdStop();
    
private:
    Ui::SceneHelp *ui;

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // SCENEHELP_H
