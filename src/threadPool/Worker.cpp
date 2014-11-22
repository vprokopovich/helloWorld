#include "Worker.h"

Worker::Worker()
: enabled(true)
, fqueue()
, thread(&Worker::thread_fn, this)
{}

Worker::~Worker()
{
    enabled = false;
    cv.notify_one();
    thread.join();
}

void Worker::appendFn(fn_type fn)
{
    std::unique_lock<std::mutex> locker(mutex);
    fqueue.push(fn);
    cv.notify_one();
}

size_t Worker::getTaskCount()       
{ 
    std::unique_lock<std::mutex> locker(mutex);
    return fqueue.size();
}

bool Worker::isEmpty()
{ 
    std::unique_lock<std::mutex> locker(mutex);
    return fqueue.empty();  
}

void Worker::thread_fn()
{
    while (enabled)
    {
        std::unique_lock<std::mutex> locker(mutex);
        // Ожидаем уведомления, и убедимся что это не ложное пробуждение
        // Поток должен проснуться если очередь не пустая либо он выключен
        cv.wait(locker, [&](){ return !fqueue.empty() || !enabled; });				
        while(!fqueue.empty())
        {
            fn_type fn = fqueue.front();
            fqueue.pop();
            // Разблокируем мютекс перед вызовом функтора
            locker.unlock();
            fn();
            // Возвращаем блокировку снова перед вызовом fqueue.empty() 
            locker.lock();
        }				
    }
}