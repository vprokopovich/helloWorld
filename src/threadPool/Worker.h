#ifndef SRC_THREADPOOL_WORKER_H
#define SRC_THREADPOOL_WORKER_H

#include <functional>
#include <thread>
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

typedef std::function<void()> fn_type;

class Worker
{    
public:

    Worker();
    ~Worker();

    void appendFn(fn_type fn);
    size_t getTaskCount();
    bool isEmpty();

private:

    std::condition_variable	cv;
    std::queue<fn_type>	    fqueue;
    std::mutex              mutex;
    std::thread	            thread;
    bool                    enabled;	

    void thread_fn();
};

typedef std::shared_ptr<Worker> worker_ptr;

#endif // SRC_THREADPOOL_WORKER_H