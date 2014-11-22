#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads)
{
    if (threads == 0)
    {
        threads = 1;
    }

    for (size_t i = 0; i < threads; i++)
    {
        worker_ptr pWorker(new Worker);
        _workers.push_back(pWorker);
    }
}

ThreadPool::~ThreadPool()
{
}

worker_ptr ThreadPool::getFreeWorker()
{
    worker_ptr pWorker;
    size_t minTasks = UINT32_MAX;				
    for (auto &it : _workers)
    {
        if (it->isEmpty())
        {
            return it;
        }
        else if (minTasks > it->getTaskCount())
        {
            minTasks = it->getTaskCount();
            pWorker = it;
        }
    }
    return pWorker;
}