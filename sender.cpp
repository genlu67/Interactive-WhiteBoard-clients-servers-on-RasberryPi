#include "sender.h"

Sender::Sender(QObject *parent) : QObject(parent)
{

}

void Sender::setSend(Draw *draw, DataQueue *queue)
{
    sdraw = draw;
    squeue = queue;
    QObject::connect(sdraw, &Draw::sendPoint, this, &Sender::onPoint);
    QObject::connect(sdraw, &Draw::sendClear, this, &Sender::onClear);
    QObject::connect(sdraw, &Draw::sendColour, this,  &Sender::onColour);
}

std::vector<bool> Sender::intToBit(int i)
{
    std::vector<bool> bit;
    while(i != 0){
        bool data;
        data = (i%2 == 0) ? 0:1;
        bit.push_back(data);
        i = i/2;
    }
    for(unsigned int j = bit.size(); j < 12; j ++){
        bit.push_back(0);
    }
    return bit;
}

std::vector<bool> Sender::intColourToBit(int i)
{
    std::vector<bool> bit;
    while(i != 0){
        bool data;
        data = (i%2 == 0) ? 0:1;
        bit.push_back(data);
        i = i/2;
    }
    for(unsigned int j = bit.size(); j < 8; j ++){
        bit.push_back(0);
    }
    return bit;
}



void Sender::onPoint(QPoint data, char type)
{
    std::vector<bool> posx;
    std::vector<bool> posy;
    std::vector<bool> posData;

    posx = intToBit(data.x());
    posy = intToBit(data.y());
    bool toggle;
    toggle = (type == 't') ? true:false;
    posData = serializept(1,1,toggle,posx,posy);
    sendData(posData);
    qDebug() << "Point position send: " << posData;
}

void Sender::onClear()
{
    std::vector<bool> clearData;
    std::vector<bool> clearX(12,0);
    std::vector<bool> clearY(12,0);

    clearData = serializept(0,0,0,clearX, clearY);
    sendData(clearData);
    qDebug() << "Clear sent";
}

void Sender::onColour(QColor colour)
{
    std::vector<bool> rData;
    std::vector<bool> gData;
    std::vector<bool> bData;
    std::vector<bool> cData;

    rData = intColourToBit(colour.red());
    gData = intColourToBit(colour.green());
    bData = intColourToBit(colour.blue());

    cData = serializecl(0,1,0,rData,gData,bData);
    sendData(cData);
    qDebug() << "Colour send" << cData;
}

std::vector<bool> Sender::serializecl(bool instr, bool instr2, bool extra, std::vector<bool> rc, std::vector<bool> gc, std::vector<bool> bc)
{
    std::vector<bool> data;

    data.push_back(instr);
    data.push_back(instr2);
    data.push_back(extra);

    data.insert(data.end(),rc.begin(), rc.end());
    data.insert(data.end(),gc.begin(), gc.end());
    data.insert(data.end(),bc.begin(), bc.end());
    return data;
}

std::vector<bool> Sender::serializept(bool instr, bool instr2, bool extra, std::vector<bool> xPos, std::vector<bool> yPos)
{
    std::vector<bool> data;

    data.push_back(instr);
    data.push_back(instr2);
    data.push_back(extra);

    data.insert(data.end(),xPos.begin(), xPos.end());
    data.insert(data.end(),yPos.begin(), yPos.end());
    return data;
}

void Sender::sendData(std::vector<bool> data)
{
    squeue->push_back(data);
}

