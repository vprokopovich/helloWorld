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

    Worker()
        :enabled(true),fqueue()
        ,thread(&Worker::thread_fn, this)
    {}
    ~Worker()
    {
        enabled = false;
        cv.notify_one();	
        thread.join();
    }
    void appendFn(fn_type fn)
    {
        std::unique_lock<std::mutex> locker(mutex);
        fqueue.push(fn);			
        cv.notify_one();
    }
    size_t getTaskCount() 		
    { 
        std::unique_lock<std::mutex> locker(mutex);
        return fqueue.size();		
    }
    bool   isEmpty() 			
    { 
        std::unique_lock<std::mutex> locker(mutex);
        return fqueue.empty();	
    }

private:

    std::condition_variable		cv;
    std::queue<fn_type>			fqueue;
    std::mutex				mutex;
    std::thread				thread;
    bool				enabled;	

    void thread_fn();
};

typedef std::shared_ptr<Worker> worker_ptr;