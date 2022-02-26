//
// D2Gauss.hpp
//

#pragma once

#include "Function.hpp"


/**
 * @brief class D2Gauss represents the second derivate
 * of a Gaussian function with amplitude, kernel width and shift.
 * Second derivative of Gaussian a*exp(-k*(x-x0)^2) is 
 * a(-2*exp(-k*(x-x0)^2)*k + 4*exp(-k*(x-x0)^2)*k^2*(x-x0)^2).
 * Inherits from Function.
 */
class D2Gauss : public Function
{
    public:
        /**
         * @brief Default constructor.
         * Initialize members to:
         * _a = 1.0,
         * _k = 1.0,
         * _x0 = 0.0
         */
        D2Gauss();

        /**
         * @brief Constructor with initializer list.
         * @param a Amplitude
         * @param k Kernel width
         * @param x0 Shift parameter
         */
        D2Gauss(double, double, double);

        /**
         * @brief Evaluate second derivative of Gaussian at position x.
         * @param x Position
         * @return Function value 
         */
        double operator() (double x) const override;
        
        Function* clone() const override;

        std::string gnuplot_plot() const override;
        
        std::string gnuplot_title() const override;

    private:
        double _a; // amplitude
        double _k; // kernel width
        double _x0; // shift
};