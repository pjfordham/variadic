#include <iostream>

template<typename... Args> class X;

template<typename T>
class X<T> {
 public:
    T value;
    X(T value_) : value(value_) {}
};

// Empty arg packs will match ambiguously with nothing so make sure the empty pack case is distanct from the base case

template<typename T, typename T2, typename... Args>
class X<T, T2, Args...> : public X<T2, Args...> {
public:
   T value;
   X(T value_, T2 arg, Args... args) : value(value_), X<T2, Args...>(arg, args...) {}
};

template<typename T>
std::ostream& operator <<(std::ostream& stream, const X<T>& value_) {
   stream << value_.value << ".";
   return stream;
}

template<typename T, typename T2, typename... Args>
std::ostream& operator <<(std::ostream& stream, const X<T, T2, Args...>& value_) {
   stream << value_.value << "," << static_cast<X<T2,Args...> const& >(value_);
   return stream;
}

class Person : public X<std::string, int, int>{
public:
   Person(std::string name, int age, int number) : X<std::string, int, int>(name, age, number) {}
};

std::ostream& operator <<(std::ostream& stream, const Person &value_) {
   stream << static_cast<const X<std::string, int, int>&>(value_);
   return stream;
}

int main()
{
   std::cout << Person("Me", 35, 10) << std::endl;
   return 0;
}
