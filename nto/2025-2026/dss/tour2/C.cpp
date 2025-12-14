#include <iostream>

#include <cmath>

#include <iomanip>


int main() {

    double a, b, r;

    std::cin >> a >> b >> r;



    double result = std::round((r * 2.0 / 3.0 * a * a * a / b / b) * 100) / 100.0;

    std::cout << std::fixed << std::setprecision(2) << result;

}

