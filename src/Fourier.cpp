//
//  Fourier.cpp
//

#include <cmath>

#include "Fourier.hpp"


Fourier::Fourier(std::shared_ptr<D2Fourier> d2f_s_ptr)
{
    _d2f_s_ptr = d2f_s_ptr;
    _n = _d2f_s_ptr->get_coefficients().size();
}

double Fourier::operator()(double x) const
{
    double sum = 0.0;
    for(int k = 0; k < _n; k++)
    {
        sum += _d2f_s_ptr->get_coefficients()[k] * cos(k*x);
    }
    return sum;
}

Function * Fourier::clone() const
{
    return new Fourier(*this);
}

std::string Fourier::gnuplot_plot() const
{
    std::string s = "";
    for(int k = 0; k < _n; k++)
    {
        s += "4 * " + std::to_string(_d2f_s_ptr->get_coefficients()[k]) + " * cos(" + std::to_string(k) + " * x)";
        s += k < (_n - 1) ? " + " : "";
    }
    return s;
}

std::string Fourier::gnuplot_title() const
{
    std::string s = "f(x) = {/Symbol S}@^{n-1}_{k=0} c_k cos(kx) (scaled)";
    return s;
}
