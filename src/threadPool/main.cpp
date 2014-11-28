#include <iostream>
#include "ThreadPool.h"
#include "Worker.h"

// Inspired by http://habrahabr.ru/post/188234/

void foo()					
{ 
    std::cout << "foo()" << std::endl; 
}
void foo2(int i, float f)	
{ 
    std::cout << "foo2(" << i << ", " << f << ")" << std::endl; 
}
struct Baz
{
    void bar() 
    { 
        std::cout << "Baz::bar()" << std::endl; 
    }
    void bar2(double d, const std::string &str) 
    { 
        std::cout << "Baz::bar2(" << d << ", " << str.c_str() << ")" << std::endl; 
    }
};

int main()
{
    ThreadPool pool;

    Baz* pBaz = new Baz();
    Baz baz;

    std::function<void(int,int)> myFn = [&](int a, int b)
    { 
        std::cout << "functor(" << a << ", " << b << ")" << std::endl;
     };

    // Вызов простой функции
    pool.runAsync(&foo);
    // Вызов функции с аргументами
    pool.runAsync(&foo2,100,54.5f);
    // Вызов метода класса, указатель на класс передаем 2м аргументом
    pool.runAsync(&Baz::bar,pBaz);
    // Вызов метода класса с аргументами *
    pool.runAsync(&Baz::bar2,&baz,400.3,"Hello World!");
    // Вызов лямбда функции
    pool.runAsync([](){ std::cout << "lambda()" << std::endl; });
    // Вызов функтора
    pool.runAsync(myFn,10,20);
}