#include "dataqueue.h"

// All of this function is a wrap around simple functions of queue (STL in C++) with mutex, therefore the information can be corrected transport 

DataQueue::DataQueue()
{
    pthread_mutex_init(&mutex,nullptr);
}

DataQueue::~DataQueue()
{
    pthread_mutex_destroy(&mutex);
}

// return size of the dataqueue
int DataQueue::size()
{
    pthread_mutex_lock(&mutex);
    int s = (int) queue.size();
    pthread_mutex_unlock(&mutex);
    return s;
}

//return the front of the dataququeue
std::vector<bool> DataQueue::front()
{
    std::vector<bool> dvector;
    pthread_mutex_lock(&mutex);
    dvector = queue.front();
    pthread_mutex_unlock(&mutex);
    return dvector;
}

// delete the front elements of the data queue
void DataQueue::pop_back()
{
    pthread_mutex_lock(&mutex);
    queue.pop();
    pthread_mutex_unlock(&mutex);
}

// add new data to the queue
void DataQueue::push_back(std::vector<bool> data)
{
    pthread_mutex_lock(&mutex);
    queue.push(data);
    pthread_mutex_unlock(&mutex);
}

