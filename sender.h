#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <pthread.h>
#include <wiringPi.h>
#include <QDebug>
#include <vector>
#include "draw.h"
#include "dataqueue.h"

class Sender : public QObject
{
    Q_OBJECT
public:
    explicit Sender(QObject *parent = 0);
    void test();
    void setSend(Draw *draw, DataQueue *queue);
    std::vector<bool> intToBit (int i);
    std::vector<bool> intColourToBit(int i);
    void sendData(std::vector<bool> data);
signals:
    void sendSignal(int i);
public slots:
    void onPoint(QPoint data, char type);
    void onClear();
    void onColour(QColor colour);
private:
    std::vector<bool> serializept(bool instr,bool instr2, bool extra, std::vector<bool> xPos, std::vector<bool> yPos);
    std::vector<bool> serializecl(bool instr, bool instr2, bool extra, std::vector<bool> rc, std::vector<bool> gc, std:: vector<bool> bc);
    Draw *sdraw;
    DataQueue *squeue;
};

#endif // SENDER_H
