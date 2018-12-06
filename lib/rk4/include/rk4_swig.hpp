#include <vector>
#include <array>
template<typename T, std::size_t n> class System;
void sys_init(void);
std::vector<double> iterate(double, double, double, double, double, double, double);
std::vector<std::array<double, 6>> iterate_range(double, double, double, double, double, double, double, double, double);
