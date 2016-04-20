#include <iostream>
#include <memory>

namespace // UnexpectedSizeOfClass
{
    class EmptyClass {};
    class Alignment1 { std::uint8_t a;};
    class Alignment2 { std::uint8_t a; std::uint64_t b;};
    class Alignment3 { std::uint8_t a; std::uint8_t b; std::uint8_t c;};
    class Alignment4 { std::uint64_t b; std::uint8_t a;};
}
class UnexpectedSizeOfClass
{
public:
    void Run()
    {
        std::cout << "!!!! Begin of UnexpectedSizeOfClass !!!!" << std::endl;
        std::cout << "Size of class with no members is: " << sizeof(EmptyClass) << std::endl;
        std::cout << "Size of class with std::uint8_t is: " << sizeof(Alignment1) << std::endl;
        std::cout << "Size of class with std::uint8_t and std::uint64_t is: " << sizeof(Alignment2) << std::endl;
        std::cout << "Size of class with std::uint8_t and std::uint8_t and std::uint8_t is: " << sizeof(Alignment3) << std::endl;
        std::cout << "Size of class with and std::uint64_t std::uint8_t is: " << sizeof(Alignment4) << std::endl;
        std::cout << "!!!! End of UnexpectedSizeOfClass !!!!" << std::endl << std::endl;
    }
};
////////////////////////
namespace // DoNotThrowExceptionInConstructor
{
    class SomeException{};
    class A
    {
        std::uint64_t someValue;
    public:
        ~A()
        {
            std::cout << "Destructor ~A() is called. No Memory leak." << std::endl;
        }
    };

    class B
    {
        std::unique_ptr<A> _a;
    public:
        B() : _a(new A)
        {
            throw SomeException();
        }
    };

    class C
    {
        A* _a;
    public:
        C() : _a(new A)
        {
            throw SomeException();
        }

        ~C()
        {
            delete _a;
        }
    };
}

class DoNotThrowExceptionInConstructor
{
public:
    void Run()
    {
        std::cout << "!!!! Begin of DoNotThrowExceptionInConstructor !!!!" << std::endl;
        std::cout << "Let`s instantiate class B that uses unique_ptr and throws exception" << std::endl;
        std::cout << "in constructor. Here we don`t have memory leaks" << std::endl;

        try
        {
            B object;
        }
        catch(SomeException)
        {
            std::cout << "If you see message that destructor of A was called - everything is OK" << std::endl;
        }

        std::cout << "And now instantiate class C that uses raw pointer as a member and throws exception" << std::endl;
        std::cout << "in constructor. Here we have memory leak" << std::endl;

        try
        {
            C object;
        }
        catch(SomeException)
        {
            std::cout << "You should not see message that destructor of A was called - memory leak" << std::endl;
        }

        std::cout << "!!!! End of DoNotThrowExceptionInConstructor !!!!" << std::endl << std::endl;
    }
};