#include "Worker.h"

class ThreadPool
{
public:

    ThreadPool(size_t threads = 1)
    {
        if (threads==0)
            threads=1;
        for (size_t i=0; i<threads; i++)
        {
            worker_ptr pWorker(new Worker);
            _workers.push_back(pWorker);
        }
    }
    ~ThreadPool() {}

private:
        
    worker_ptr getFreeWorker();

    std::vector<worker_ptr> _workers; 

};