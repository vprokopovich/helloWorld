// TypeList.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <typeinfo> // Using RTTI

namespace TL    // Namespace for TypeLists
{
    class NullType{};       // Null type definition. Used to point the end of TypeList

    // TypeList definition
    template <typename T, typename U>
    struct TypeList
    {
        typedef T head;
        typedef U tail;
    };

    /**
     * Calculating Length of TypeList
     *
     * Explanation:
     * The length of zero-length TypeList is zero.
     * The length of non zero-length TypeList is 1 + length of its Tail
    **/
    template <typename TypeList> struct Length;
    template <> struct Length<NullType>{enum {value = 0};};
    template <typename T, typename U>
    struct Length<TypeList<T, U> >
    {
        enum {value = 1 + Length<U>::value};
    };

    /**
     * Implementation of indexed access
     * (What type is stored in the TypeList at index i?)
     *
     * Explanation:
     * If TypeList is not empty and index==0, Result is Head of TypeList
     * If TypeList is not empty and index!=0, Result is applying TypeAt 
     * algorithm to the Tail of TypeList with (index-1)
    **/
    template <typename TList, unsigned int index> struct TypeAt;
    template <typename Head, typename Tail>
    struct TypeAt<TypeList<Head, Tail>, 0 >
    {
        typedef Head Result;
    };
    template <typename Head, typename Tail, unsigned int i>
    struct TypeAt<TypeList<Head, Tail> , i >
    {
        typedef typename TypeAt<Tail, i-1>::Result Result;
    };

    // Implementation of search of Type in TypeList
    // (What is the index of specified type in TypeList?)
    template <typename TList, typename T> struct IndexOf;
    template <typename T>
    struct IndexOf<NullType, T>
    {
        enum {value = -1};
    };
    template <typename Tail, typename T>
    struct IndexOf<TypeList<T, Tail>, T>
    {
        enum {value = 0};
    };
    template <typename Head, typename Tail, typename T>
    struct IndexOf<TypeList<Head, Tail>, T>
    {
    private:
        enum {temp = IndexOf<Tail, T>::value};
    public:
        enum {value = (temp == -1) ? -1 : 1 + temp};
    };

    // Implementation of adding the element of type T to existing TypeList
    template <typename TList, typename T> struct Append;
    template <>
    struct Append<NullType, NullType>
    {
        typedef NullType Result;
    };
    template <typename T>
    struct Append<NullType, T>
    {
        typedef TypeList<T, NullType> Result;
    };
    template <typename Head, typename Tail>
    struct Append<NullType, TypeList<Head, Tail> >
    {
        typedef TypeList<Head, Tail> Result;
    };
    template <typename Head, typename Tail, typename T>
    struct Append<TypeList<Head, Tail>, T >
    {
        typedef TypeList<Head, typename Append<Tail, T>::Result > Result;
    };

    // Erasing Type from TypeList
    template <typename TList, typename T> struct Erase;
    template <typename T>
    struct Erase<NullType, T>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail>
    struct Erase<TypeList<T, Tail>, T>
    {
        typedef Tail Result;
    };
    template <typename Head, typename Tail, typename T>
    struct Erase<TypeList<Head, Tail>, T>
    {
        typedef TypeList<Head, typename Erase<Tail, T>::Result > Result;
    };

    // Erasing All types from TypeList //3.9
    template <typename TList, typename T> struct EraseAll;
    template <typename T>
    struct EraseAll <NullType, T>
    {
        typedef NullType Result;
    };
    template <typename T, typename Tail>
    struct EraseAll<TypeList<T, Tail>, T>
    {
        typedef typename EraseAll<Tail, T>::Result Result;
    };
    template <typename Head, typename Tail, typename T>
    struct EraseAll<TypeList<Head, Tail>, T>
    {
        typedef TypeList<Head, typename EraseAll<Tail,T>::Result> Result;
    };

    //Erasing all duplicates //3.10
    template <typename TList> struct NoDuplicates;
    template <>
    struct NoDuplicates<NullType>
    {
        typedef NullType Result;
    };
    template <typename Head, typename Tail>
    struct NoDuplicates<TypeList<Head, Tail> >
    {
    private: 
        typedef typename NoDuplicates<Tail>::Result L1;
        typedef typename Erase<L1, Tail>::Result L2;
    public:
        typedef TypeList<Head, L2> Result;
    };

    // Replace
    template <typename TList, typename T, typename U> struct Replace;
    template <typename T, typename U>
    struct Replace<NullType, T, U>
    {
        typedef NullType Result;
    };
    template <typename T, typename U, typename ListTail>
    struct Replace<TypeList<T, ListTail>, T, U>
    {
        typedef TypeList<U, ListTail> Result;
    };
    template <typename T, typename U, typename ListHead, typename ListTail>
    struct Replace<TypeList<ListHead, ListTail>, T, U>
    {
        typedef TypeList<ListHead, typename Replace<ListTail, T, U>::Result> Result;
    };
} // namespace TL


using namespace std;
using namespace TL;

typedef TypeList<int, NullType> OneTypeOnly;
typedef TypeList<char, TypeList<signed char, TypeList<unsigned char, NullType> > > CharList;
typedef TypeList<signed char, TypeList<short int, TypeList<int, TypeList<long int, NullType> > > > SignedIntegrals;

int main(int argc, char* argv[])
{
	// Example of usage Length
    cout << "CharList TypeList length = " << Length<CharList>::value << endl;
    cout << "SignedIntegrals TypeList length = " << Length<SignedIntegrals>::value << endl;

    // Example of indexed access
    cout << "SignedIntegral at index = 0 contains type = " << typeid(TypeAt<SignedIntegrals, 0>::Result).name() << endl;
    cout << "SignedIntegral at index = 1 contains type = " << typeid(TypeAt<SignedIntegrals, 1>::Result).name() << endl;
    cout << "SignedIntegral at index = 2 contains type = " << typeid(TypeAt<SignedIntegrals, 2>::Result).name() << endl;
    cout << "SignedIntegral at index = 3 contains type = " << typeid(TypeAt<SignedIntegrals, 3>::Result).name() << endl;

    // Example of searching type index by type name
    cout << "Index of 'int' type in SignedIntegral TypeList = " << IndexOf<SignedIntegrals, int >::value << endl;

    // Example of appending 1 TypeList to another
    typedef Append<CharList, SignedIntegrals>::Result MergedTypeList;
    cout << "mergedTypeList at index = 0 contains type = " << typeid(TypeAt<MergedTypeList, 0>::Result).name() << endl;
    cout << "mergedTypeList at index = 1 contains type = " << typeid(TypeAt<MergedTypeList, 1>::Result).name() << endl;
    cout << "mergedTypeList at index = 2 contains type = " << typeid(TypeAt<MergedTypeList, 2>::Result).name() << endl;
    cout << "mergedTypeList at index = 3 contains type = " << typeid(TypeAt<MergedTypeList, 3>::Result).name() << endl;
    cout << "mergedTypeList at index = 4 contains type = " << typeid(TypeAt<MergedTypeList, 4>::Result).name() << endl;
    cout << "mergedTypeList at index = 5 contains type = " << typeid(TypeAt<MergedTypeList, 5>::Result).name() << endl;
    cout << "mergedTypeList at index = 6 contains type = " << typeid(TypeAt<MergedTypeList, 6>::Result).name() << endl;

    // Example of erasing type from TypeList
    typedef Erase<MergedTypeList, signed char>::Result TypeListAfterErase;
    cout << "TypeListAfterErase at index = 0 contains type = " << typeid(TypeAt<TypeListAfterErase, 0>::Result).name() << endl;
    cout << "TypeListAfterErase at index = 1 contains type = " << typeid(TypeAt<TypeListAfterErase, 1>::Result).name() << endl;
    cout << "TypeListAfterErase at index = 2 contains type = " << typeid(TypeAt<TypeListAfterErase, 2>::Result).name() << endl;
    cout << "TypeListAfterErase at index = 3 contains type = " << typeid(TypeAt<TypeListAfterErase, 3>::Result).name() << endl;
    cout << "TypeListAfterErase at index = 4 contains type = " << typeid(TypeAt<TypeListAfterErase, 4>::Result).name() << endl;
    cout << "TypeListAfterErase at index = 5 contains type = " << typeid(TypeAt<TypeListAfterErase, 5>::Result).name() << endl;

    return 0;
}

