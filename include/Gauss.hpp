//
// Gauss.hpp
//

#pragma once

#include "Function.hpp"


/**
 * @brief class Gauss represents a Gaussian function
 * a*exp(-k*(x-x0)^2) with amplitude a, kernel width k
 * and shift x0. Inherits from Function.
 */
class Gauss : public Function
{
    public:
        /**
         * @brief Default constructor.
         * Initialize members to:
         * _a = 1.0,
         * _k = 1.0,
         * _x0 = 0.0
         */
        Gauss();

        /**
         * @brief Constructor with initializer list.
         * @param a Amplitude
         * @param k Kernel width
         * @param x0 Shift parameter
         */
        Gauss(double, double, double);

        /**
         * @brief Evaluate Gaussian at position x.
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