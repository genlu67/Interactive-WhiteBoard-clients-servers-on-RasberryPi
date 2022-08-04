#include "dataqueue.h"

DataQueue::DataQueue()
{
    pthread_mutex_init(&mutex,nullptr);
}

DataQueue::~DataQueue()
{
    pthread_mutex_destroy(&mutex);
}

int DataQueue::size()
{
    pthread_mutex_lock(&mutex);
    int s = (int) queue.size();
    pthread_mutex_unlock(&mutex);
    return s;
}

std::vector<bool> DataQueue::front()
{
    std::vector<bool> dvector;
    pthread_mutex_lock(&mutex);
    dvector = queue.front();
    pthread_mutex_unlock(&mutex);
    return dvector;
}

void DataQueue::pop_back()
{
    pthread_mutex_lock(&mutex);
    queue.pop();
    pthread_mutex_unlock(&mutex);
}

void DataQueue::push_back(std::vector<bool> data)
{
    pthread_mutex_lock(&mutex);
    queue.push(data);
    pthread_mutex_unlock(&mutex);
}

