#include <iostream>
#include <sstream>
#include <vector>
#include <initializer_list>


template<typename...Ts>
void ignore_returnvalues(Ts&&...) {}

template<typename ... T>
void print(T ... args) {
   // Expansion into function call
   ignore_returnvalues( (std::cout << args << '\n', 0)... );

   // Expansion into initialization lists
   int dummy[sizeof...(T)] = { ((void)(std::cout << args << '\n'), 0)... };

   auto xdummy = { ((void)(std::cout << args << '\n'), 0)... };

   (void) std::initializer_list<int>{  ((void)(std::cout << args << '\n'), 0)... };
}

// Call a function for everything passed in
template<typename Fun, typename...Ts>
void sequential_foreach(Fun f, const Ts&... args) {
	(void) std::initializer_list<int>{
           ((void)(f(args)),0)...
	};
}

// Make that function a lambda that writes to the given stream
template<typename...Ts>
void print_all(std::ostream& stream, const Ts&... args) {
   sequential_foreach([&](const auto& arg){stream << arg <<'\n';}, args...);
}

int main() {
   print("Hello", "World", 1, 2.3);
   print_all(std::cout, "Hello", "World", 1, 2.3);
   return 0;
}
