//
//  Fourier.hpp
//

#pragma once

#include <memory>
#include <vector>

#include "D2Fourier.hpp"
#include "Function.hpp"


/**
 * @brief class D2Fourier represents a Fourier-(cos)series,
 * which can be expressed as sum_k=0^(n-1) c_k cos(k*x).
 * Inherits from Function.
 */
class Fourier : public Function
{
    public:
        /**
         * @brief Constructor from (shared) pointer of D2Fourier object.
         * @param s_ptr_c Shared pointer to vector of coefficients
         */
        Fourier(std::shared_ptr<D2Fourier> d2f_s_ptr);

        /**
         * @brief Evaluate Fourier-(cos)series at position x.
         * @param x Position
         * @return Function value 
         */
        double operator() (double x) const override;

        Function* clone() const override;

        std::string gnuplot_plot() const override;

        std::string gnuplot_title() const override;

    private:
        std::shared_ptr<D2Fourier> _d2f_s_ptr; // shared_ptr to D2Fourier object
        int _n; // number of Fourier coefficients
};