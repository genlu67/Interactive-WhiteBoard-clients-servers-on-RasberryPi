#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QPoint>
#include <QDebug>
#include <math.h>

#include "draw.h"
class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = 0);
    void setRec(Draw *rdraw);
    void deserialize(std::vector<bool> rdata);

signals:
    void rPos(QPoint p, bool toggle);
    void rClear();
    void rColor(QColor colour);
public slots:


private:
    Draw * rDraw;
};

#endif // RECEIVER_H
