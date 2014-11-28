#ifndef SRC_THREADPOOL_THREADPOOL_H
#define SRC_THREADPOOL_THREADPOOL_H

#include "Worker.h"

class ThreadPool
{

public:

    ThreadPool(size_t threads = 1);
    ~ThreadPool();

    template<typename _FN, typename ... _ARGS>
    void runAsync(_FN _fn, _ARGS... _args)
    {
        getFreeWorker()->appendFn(std::bind(_fn,_args...));
    }

private:
    worker_ptr getFreeWorker();

    std::vector<worker_ptr> _workers;
};

#endif //SRC_THREADPOOL_THREADPOOL_H