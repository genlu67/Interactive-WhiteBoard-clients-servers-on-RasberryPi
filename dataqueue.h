#ifndef DATAQUEUE_H
#define DATAQUEUE_H

// A class that acts as data queue for signal to correctly transport from one Rasberry Pi to others
// This class used mutex to avoid Race Condition 

#include <vector>
#include <queue>
#include <pthread.h>

class DataQueue
{
public:
    DataQueue();
    ~DataQueue();

    int size();
    std::vector<bool> front();
    void pop_back();
    void push_back(std::vector<bool> data);

private:
    std::queue< std::vector<bool> > queue;
    pthread_mutex_t mutex;
};

#endif // DATAQUEUE_H
