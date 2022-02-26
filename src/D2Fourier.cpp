//
//  D2Fourier.cpp
//

#include <cmath>

#include "D2Fourier.hpp"


D2Fourier::D2Fourier() : _c({}), _n(0) {}

D2Fourier::D2Fourier(std::vector<double> c) : _c(c), _n(_c.size()) {}

std::vector<double> D2Fourier::get_coefficients()
{
    return _c;
}

void D2Fourier::set_coefficients(const std::vector<double> c)
{
    _c = c;
    _n = _c.size();
}

double D2Fourier::operator()(double x) const
{
    double sum = 0.0;
    for(int k = 0; k < _n; k++)
    {
        sum += _c[k] * (-k*k) * cos(k*x);
    }
    return sum;
}

Function * D2Fourier::clone() const
{
    return new D2Fourier(*this);
}

std::string D2Fourier::gnuplot_plot() const
{
    std::string s = "";
    for(int k = 0; k < _n; k++)
    {
        s += std::to_string(_c[k]) + " * (" + std::to_string(k) + ")**2 * (-1) * cos(" + std::to_string(k) + " * x)";
        s += k < (_n - 1) ? " + " : "";
    }
    return s;
}

std::string D2Fourier::gnuplot_title() const
{
    std::string s = "d^2/dx^2 f(x) = d^2/dx^2 {/Symbol S}@^{n-1}_{k=0} c_k cos(kx)";
    return s;
}
