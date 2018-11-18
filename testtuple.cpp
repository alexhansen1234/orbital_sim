#include <iostream>
#include <tuple>

template <class... Args>
void doSomethingForAll(Args const&... args) {
  auto x = {doSomething(args, )...};
}



int main()
{
  std::initializer_list<double> args {1, 2, 3};
  std::cout << func(args) << "\n";
}
