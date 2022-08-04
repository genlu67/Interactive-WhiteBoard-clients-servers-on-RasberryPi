#include <QApplication>
#include <QDebug>

#include <pthread.h>
#include <wiringPi.h>

#include "window.h"
#include "draw.h"
#include "sender.h"
#include "receiver.h"
#include "dataqueue.h"

void* sendwork(void* s)
{
    DataQueue *sendData = (DataQueue*) s;
    qDebug() << "sender thread work";
    forever{
        if(sendData->size() != 0){
            std::vector<bool> bit = sendData->front();
            sendData->pop_back();
            qDebug() << "DATA SEND: " << bit;
            for(unsigned int i = 0; i < bit.size(); i++){
                digitalWrite(0, bit[i]);
                digitalWrite(2, true);
                while(!digitalRead(3));

                digitalWrite(2, false);
                while(digitalRead(3));
            }
        }
    }
    pthread_exit(NULL);
}

void* receivework(void* r)
{
    Receiver *rData = (Receiver*) r;
    qDebug() << "receiver thread work";
    std::vector<bool> bit;
    forever{
        while(digitalRead(22));

        digitalWrite(23,false);

        while(!digitalRead(22));

        bit.push_back(digitalRead(21));

        if(bit.size() == 27){
            rData->deserialize(bit);
            qDebug() << "Receive bit" << bit;
            bit.clear();
        }
        digitalWrite(23,true);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    wiringPiSetup();
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);

    pinMode(21, INPUT);
    pinMode(22, INPUT);
    pinMode(23, OUTPUT);

    pullUpDnControl(3, PUD_DOWN);
    pullUpDnControl(21, PUD_DOWN);
    pullUpDnControl(22, PUD_DOWN);


    DataQueue sdata;
    // setup Qt GUI
    QApplication app(argc, argv);
    Window wreceive, wsend ;
    wsend.setWindowTitle("SENDER");
    wreceive.setWindowTitle("RECEIVER");
    wsend.show();
    wreceive.show();




//    pthread_mutex_init(&mutex,0);


    
    Sender *sender = new Sender();
    sender->setSend(wsend.draw,&sdata);
    Receiver *receiver = new Receiver();
    receiver->setRec(wreceive.draw);


    // starting worker thread(s)
    int sc;
    pthread_t sender_thread;
    sc = pthread_create(&sender_thread, NULL, &sendwork, (void*) &sdata);
    if (sc) {
        qDebug() << "Unable to start sender thread.";
        exit(1);
    }
    int rc;
    pthread_t receiver_thread;
    rc = pthread_create(&receiver_thread, NULL, &receivework, (void*)receiver);
    if(rc) {
        qDebug() << "Unable to start receiver thread.";
        exit(1);
    }

    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = app.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}
