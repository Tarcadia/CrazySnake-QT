#include "qclickimage.h"

void QClickImage::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    emit this->mouseOn();
}

void QClickImage::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    emit this->mouseOff();
}

void QClickImage::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit this->clicked();
}
