
#include <QMouseEvent>

#include "scenehelp.h"
#include "ui_scenehelp.h"

SceneHelp::SceneHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneHelp)
{
    qDebug() << "Initing SceneHelp...";

    ui->setupUi(this);
    ui->labelHelp->installEventFilter(this);
    
    qDebug() << "Done init SceneHelp.";
}

bool SceneHelp::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->ui->labelHelp && event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        int x = mouseEvent->pos().x() + this->ui->labelHelp->x();
        int y = mouseEvent->pos().y() + this->ui->labelHelp->y();
        int imWidth = ui->labelHelp->width();
        int imHeight = ui->labelHelp->height();
        int uiWidth = this->width();
        int uiHeight = this->height();
        int imX = - x * (imWidth - uiWidth) / uiWidth;
        int imY = - y * (imHeight - uiHeight) / uiHeight;
        ui->labelHelp->move(imX, imY);
    }

    if (watched == this->ui->labelHelp && event->type() == QEvent::MouseButtonPress)
    {
        emit this->cmdStop();
    }
    return QWidget::eventFilter(watched, event);
}

SceneHelp::~SceneHelp()
{
    delete ui;
}

void SceneHelp::callCmdStop()
{
    emit this->cmdStop();
}
