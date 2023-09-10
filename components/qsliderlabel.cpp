#include "qsliderlabel.h"

void QSliderLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked();
}

void QSliderLabel::setupSlide(int dx, int dy)
{
    if (this->moveTimer == nullptr)
    {
        this->movedx = dx;
        this->movedy = dy;
        this->movecnt = 0;
        this->moveTimer = new QTimer(this);
        this->moveTimer->setSingleShot(false);
        this->moveTimer->start(this->moveStepIntervalms);
        this->connect(this->moveTimer, SIGNAL(timeout()), this, SLOT(slideStep()));
    }
}

void QSliderLabel::slideUp()
{
    this->setupSlide(0, -this->moveStepLength);
}

void QSliderLabel::slideDown()
{
    this->setupSlide(0, this->moveStepLength);
}

void QSliderLabel::slideLeft()
{
    this->setupSlide(-this->moveStepLength, 0);
}

void QSliderLabel::slideRight()
{
    this->setupSlide(this->moveStepLength, 0);
}

void QSliderLabel::slideStep()
{
    if (this->moveTimer == nullptr) return;
    if (this->movecnt >= this->moveStepCount)
        this->moveTimer->stop();
    this->move(this->x()+this->movedx, this->y()+this->movedy);
    this->movecnt += 1;
}
