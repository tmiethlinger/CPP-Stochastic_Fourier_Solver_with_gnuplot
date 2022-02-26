//
//  Gauss.cpp
//

#include <cmath>

#include "Gauss.hpp"


Gauss::Gauss() : _a(1.0), _k(1.0), _x0(0.0) {}

Gauss::Gauss(double a, double k, double x0) : _a(a), _k(k), _x0(x0) {}

double Gauss::operator()(double x) const
{
    return _a * exp(-_k*(x-_x0)*(x-_x0));
}

Function * Gauss::clone() const
{
    return new Gauss(*this);
}

std::string Gauss::gnuplot_plot() const
{
    std::string s = "4 * " + std::to_string(_a) + "*exp(-" + std::to_string(_k) + "*x**2)";
    return s;
}

std::string Gauss::gnuplot_title() const
{
    std::string s = "a exp(-kx^2) (scaled)";
    return s;
}