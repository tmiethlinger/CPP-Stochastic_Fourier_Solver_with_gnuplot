//
//  D2Fourier.hpp
//

#pragma once

#include <vector>

#include "Function.hpp"


/**
 * @brief class D2Fourier represents the second derivate
 * of a Fourier-(cos)series.
 * Second derivative of Fourier-(cos)series sum_k=0^(n-1) c_k cos(k*x) is 
 * sum_k=0^(n-1) c_k (-k*k) cos(k*x).
 * Inherits from Function.
 */
class D2Fourier : public Function
{
    public:
        /**
         * @brief Default constructor.
         * Initialize members to:
         * _c = {} (empty vector),
         * _n = 0.
         */
        D2Fourier();

        /**
         * @brief Constructor with initializer list.
         * @param c Vector of coefficients
         */
        D2Fourier(std::vector<double>);

        /**
         * @brief Getter for coefficients vector _c.
         * @return _c Vector of coefficients
         */
        std::vector<double> get_coefficients();

        /**
         * @brief Setter for coefficients vector _c.
         * @param c Vector of new coefficients
         */
        void set_coefficients(const std::vector<double>);

        /**
         * @brief Evaluate second derivative of Fourier-(cos)series at position x.
         * @param x Position
         * @return Function value 
         */
        double operator() (double x) const override;

        Function* clone() const override;

        std::string gnuplot_plot() const override;

        std::string gnuplot_title() const override;

    private:
        std::vector<double> _c; // vector for Fourier coefficients
        int _n; // number of Fourier coefficients
};