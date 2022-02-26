//
//  D2Gauss.cpp
//

#include <cmath>

#include "D2Gauss.hpp"


D2Gauss::D2Gauss() : _a(1.0), _k(1.0), _x0(0.0) {}

D2Gauss::D2Gauss(double a, double k, double x0) : _a(a), _k(k), _x0(x0) {}

double D2Gauss::operator()(double x) const
{
    return _a * (-2 * exp(-_k*(x-_x0)*(x-_x0)) * _k +
                  4 * exp(-_k*(x-_x0)*(x-_x0)) * _k*_k * (x-_x0)*(x-_x0));
}

Function * D2Gauss::clone() const
{
    return new D2Gauss(*this);
}

std::string D2Gauss::gnuplot_plot() const
{
    std::string s = std::to_string(_a) + "*(" +
                    "-2*exp(-" + std::to_string(_k) + "*x**2)*" + std::to_string(_k) +
                    " + 4*exp(-4*x**2)*" + std::to_string(_k) + "**2*x**2)";
    return s;
}

std::string D2Gauss::gnuplot_title() const
{
    std::string s = "g(x) = d^2/dx^2 a exp(-kx^2)";
    return s;
}