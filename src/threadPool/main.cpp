#include <iostream>
#include "ThreadPool.h"
#include "Worker.h"
#include <CTrace.h>

// Inspired by http://habrahabr.ru/post/188234/

void foo()					
{ 
    TRC_DEBUG("foo()");
}
void foo2(int i, float f)	
{ 
    TRC_DEBUG("foo(%d, %d)",i, f);
}
struct Baz
{
    void bar() 
    { 
        TRC_DEBUG("Baz::bar()");
    }
    void bar2(double d, const std::string &str) 
    { 
        TRC_DEBUG("Baz::bar2(%f, %s)", d, str.c_str());
    }
};

int main()
{
    ThreadPool pool(3); // Pool is created with 3 threads

    Baz* pBaz = new Baz();
    Baz baz;

    std::function<void(int,int)> myFn = [&](int a, int b)
    { 
        TRC_DEBUG("functor(%d, %d)", a, b);
     };

    for (int i = 0; i < 10; i++)
    {

        // Вызов простой функции
        pool.runAsync(&foo);
        // Вызов функции с аргументами
        pool.runAsync(&foo2, 100, 54.5f);
        // Вызов метода класса, указатель на класс передаем 2м аргументом
        pool.runAsync(&Baz::bar, pBaz);
        // Вызов метода класса с аргументами *
        pool.runAsync(&Baz::bar2, &baz, 400.3, "Hello World!");
        // Вызов лямбда функции
        pool.runAsync([]()
        {
            TRC_DEBUG("lambda()");
        });
        // Вызов функтора
        pool.runAsync(myFn, 10, 20);
    }
}