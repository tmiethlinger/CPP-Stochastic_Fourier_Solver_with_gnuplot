//
//  MathUtil.hpp
//

#pragma once

#include <algorithm> // std::max_element, std::transform
#include <cmath> // pow, sqrt
#include <functional> // std::function
#include <numeric> // std::iota
#include <vector>

#include "Function.hpp"


namespace MathUtil
{
    /**
     * @brief Numerically integrate functions in range 
     * @param f integrand (Function, or std::function<double(double)>)
     * @param a lower integration boundary (double)
     * @param b upper integration boundary (double)
     * @param n number of discrete intervals (int)
     * @return definite integral (double)
     */
    namespace Integrator
    {
        /**
         * @brief Simple (centered) Riemann integrator
         * @param f integrand const std::function<double(double)>& 
         */
        inline double simple(const std::function<double(double)>& f, double a, double b, int n)
        {
            double dx = (b - a) / n;
            double dx_2 = dx / 2;
            double sum = 0.0;
            for(int i = 0; i < n; i++)
            {
                sum += f(a + dx*i + dx_2);
            }
            sum *= dx;
            return sum;
        }

        /**
         * @brief Simple (centered) Riemann integrator
         * Calls simple(const std::function<double(double)>&, ...)
         * @param f integrand const Function&
         */
        inline double simple(const Function& f, double a, double b, int n)
        {
            return simple([&f](double x){ return f(x); }, a, b, n);
        }

        /**
         * @brief Composite Simpson's rule integrator
         * @param f integrand const std::function<double(double)>& 
         */
        inline double simpson(const std::function<double(double)>& f, double a, double b, int n)
        {
            double s1 = 0;
            double s2 = 0;
            double dx = (b - a) / n;
            for (int j = 1; j <= (n / 2 - 1); j++)
            {
                s1 += f(a + 2 * j*dx);
            }
            for (int j = 1; j <= n / 2; j++)
            {
                s2 += f(a + (2 * j - 1)*dx);
            }
            return (dx / 3 * (f(a) + (2 * s1) + (4 * s2) + f(b)));
        }

        /**
         * @brief Composite Simpson's rule integrator.
         * Calls simpson(const std::function<double(double)>&, ...)
         * @param f integrand const Function&
         */
        inline double simpson(const Function& f, double a, double b, double dx)
        {
            return simpson([&f](double x){ return f(x); }, a, b, dx);
        }
    }

    /**
     * @brief Compute distance function d(f1, f2) in function space 
     * @param f1 first function (const Function&)
     * @param f2 second function (const Function&)
     * @param a lower boundary (double)
     * @param b upper boundary (double)
     * @param n number of discrete intervals (int)
     * @return definite integral (double)
     */
    namespace Distance
    {
        /**
         * @brief Compute L1 distance int_a^b |f1 - f2|.
         * Demonstrates how to create more complex
         * mathematical expressions by combining Function
         * objects into a std::function<double(double)>
         * using lambda expressions.
         * Not used in main program.
         */
        inline double L1(const Function& f1, const Function& f2, double a, double b, int n)
        {
            auto f = [&f1, &f2](double x){ return abs(f1(x) - f2(x)); };
            return Integrator::simple(f, a, b, n);
        }

        /**
         * @brief Compute L2 distance sqrt(int_a^b (f1 - f2)^2)
         * Demonstrates how to create more complex
         * mathematical expressions by combining Function
         * objects into a std::function<double(double)>
         * using lambda expressions.
         * Used in main program.
         */
        inline double L2(const Function& f1, const Function& f2, double a, double b, int n)
        {
            auto f = [&f1, &f2](double x){ return pow(f1(x) - f2(x), 2); };
            return sqrt(Integrator::simple(f, a, b, n));
        }

        /**
         * @brief Compute L_inf distance (Chebyshev distance) max |f1 - f2|.
         * Demonstrates the usage of the STL library (iota, max,
         * max_element and transform).
         * Could be implemented much easier using e.g. for-loops.
         * Not used in main program.
         */
        inline double LInf(const Function& f1, const Function& f2, double a, double b, int n)
        {
            auto f = [&f1, &f2](double x){ return std::max(f1(x), f2(x)); };
            std::vector<double> vec(n);
            std::iota(vec.begin(), vec.end(), 0);
            std::transform(vec.begin(), vec.end(), vec.begin(),
                [f, a, b, n](double i)
                {
                    double dx = (b - a) / n;
                    double dx_2 = dx / 2;
                    double x = i*dx + dx_2;
                    return f(x);
                }
            );
            return *std::max_element(vec.begin(), vec.end());
        }
    }
};