//
//  Function.hpp
//

#pragma once

#include <string>


class Function
{
    public:
        /**
         * @brief Evaluate function at position x
         * @param x Position
         * @return Function value
         */
        virtual double operator() (double x) const = 0;

        /**
         * @brief Virtual copy constructor
         * @return Pointer to copy of this
         */
        virtual Function* clone() const = 0;

        /**
         * @brief Virtual destructor.
         * Every abstract class should have a virtual destructor.
         */
        virtual ~Function() {};

        /**
         * @brief Gnuplot command to plot current object.
         */
        virtual std::string gnuplot_plot() const = 0;

        /**
         * @brief Gnuplot command to plot current object title.
         */
        virtual std::string gnuplot_title() const = 0;
};