#ifndef QCLICKIMAGE_H
#define QCLICKIMAGE_H

#include <QLabel>
#include <QObject>

class QClickImage : public QLabel
{
    Q_OBJECT

public:
    QClickImage(QWidget *parent=nullptr): QLabel(parent){};
    ~QClickImage() {};

signals:
    void clicked();
    void mouseOn();
    void mouseOff();

protected:
    virtual void enterEvent(QEnterEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

};

#endif // QCLICKIMAGE_H
