#include <iostream>

template<typename... Args> class X;


template<typename T>
class X<T> {
public:
    T value;
    X(T value_) : value(value_) {}
};

template<typename T>
std::ostream& operator <<(std::ostream& stream, const X<T>& value_) {
   stream << value_.value << ".";
   return stream;
}


// Empty arg packs will match ambiguously with nothing so make sure the empty pack case is distanct from the base case

template<typename T, typename T2, typename... Args>
class X<T, T2, Args...> {
public:
   T value;
   X<T2, Args...> superValue;
   X(T value_, T2 arg, Args... args) : value(value_), superValue(arg, args...) {}
};

template<typename T, typename T2, typename... Args>
std::ostream& operator <<(std::ostream& stream, const X<T, T2, Args...>& value_) {
   stream << value_.value << "," << value_.superValue;
   return stream;
}


class Person : public X<std::string, int, int>{
public:
   Person(std::string name, int age, int number) : X<std::string, int, int>(name, age, number) {}
};

int main()
{
   std::cout << Person("Me", 35, 10) << std::endl;
   return 0;
}
