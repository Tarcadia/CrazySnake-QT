#ifndef QSLIDERLABEL_H
#define QSLIDERLABEL_H

#include <QLabel>
#include <QTimer>
#include <QObject>

class QSliderLabel : public QLabel
{
    Q_OBJECT
public:
    QSliderLabel(QWidget *parent=nullptr): QLabel(parent){};
    ~QSliderLabel() {};

signals:
    void clicked();

public slots:
    void slideUp();
    void slideDown();
    void slideLeft();
    void slideRight();
    void slideStep();

private:
    int const moveStepLength = 10;
    int const moveStepCount = 100;
    int const moveStepIntervalms = 5;
    
    void setupSlide(int dx, int dy);
    QTimer* moveTimer = nullptr;

    int movedx = 0;
    int movedy = 0;
    int movecnt = 0;

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // QSLIDERLABEL_H
