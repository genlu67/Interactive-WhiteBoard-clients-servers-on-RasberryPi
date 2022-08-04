#include "receiver.h"

Receiver::Receiver(QObject *parent) : QObject(parent)
{

}

void Receiver::setRec(Draw *rdraw)
{
    rDraw = rdraw;
    QObject::connect(this, &Receiver::rPos, rDraw, &Draw::onSendPos);
    QObject::connect(this, &Receiver::rClear, rDraw, &Draw::clearImage);
    QObject::connect(this, &Receiver::rColor, rDraw, &Draw::setPenColor);
}

void Receiver::deserialize(std::vector<bool> rdata)
{
    qDebug() << "deserializing ... ";
    bool toggle;
    int xPos = 0;
    int yPos = 0;
    int rColour = 0;
    int gColour = 0;
    int bColour = 0;
    if(rdata.size() == 27){
        if(rdata[0] && rdata[1]){

            toggle = rdata[2];
            for(int i = 0; i <12; i++){
                int numx, numy;
                numx = (rdata[i + 3] == true) ? 1:0;
                numy = (rdata[i + 15] == true) ? 1:0;
                xPos += (numx*pow(2,i));
                yPos += (numy*pow(2,i));
            }

            QPoint point;
            point.setX(xPos);
            point.setY(yPos);
            emit rPos(point, toggle);
            qDebug() << "toggling" << toggle;
        } else if(!rdata[0] && !rdata[1]) {
            emit rClear();
        } else if(!rdata[0] && rdata[1]){
            for(int i = 0; i < 8; i++){
                int rData, gData, bData;
                rData = (rdata[i + 3] == true) ? 1:0;
                gData = (rdata[i + 3 + 8] == true) ? 1:0;
                bData = (rdata[i + 3 + 16] == true) ? 1:0;
                rColour += (rData*pow(2,i));
                bColour += (bData*pow(2,i));
                gColour += (gData*pow(2,i));
            }
            QColor colour;
            colour.setRgb(rColour,gColour,bColour);
            emit rColor(colour);
        }
    } else {
        qDebug() << "Data size Error";
    }
}
