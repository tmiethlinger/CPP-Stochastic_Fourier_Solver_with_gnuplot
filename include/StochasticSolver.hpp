//
//  StochasticSolver.hpp
//

#pragma once

#include <memory> // std::shared_ptr
#include <random> // std::default_random_engine, std::uniform_real_distribution
#include <vector>

#include "D2Gauss.hpp"
#include "D2Fourier.hpp"


/**
 * @brief class StochasticSolver implements a stochastic solver
 * for solving the equation f''(x) = g(x), where we use a
 * Fourier-(cos)series as ansatz function for f(x).
 */
class StochasticSolver
{
    public:
        /**
         * @brief Default constructor.
         * Initialize member _generator with seed=1 and
         * defines member _distribution to lie in range [-1.0, 1.0)
         */
        StochasticSolver();

       /**
         * @brief Default constructor.
         * Initialize member _generator with argument seed and
         * defines member _distribution to lie in range [-1.0, 1.0)
         */
        StochasticSolver(int);

        /**
         * @brief Solves the equation f''(x) = g(x), where
         * we use a Fourier-(cos)series as ansatz function, i.e.
         * f(x) = sum_k=0^n c_k cos(k*x), for a given g(x).
         * @param g RHS of f''(x) = g(x), reference to D2Gauss object
         * @param m number of iterations in stochastic solver, int
         * @param n number of Fourier coefficients
         * @param N number of discrete intervals for numeric integration, int
         * @return D2Fourier solution object with new coefficients
         */
        D2Fourier solve(std::shared_ptr<D2Fourier>, std::shared_ptr<D2Gauss>, int, int, int, double);

    private:
        /**
         * @brief Computes new stochastic step vector,
         * i.e. difference to new coefficients vector.
         * @param n number of Fourier coefficients
         * @param lr learning rate, i.e. magnitude (L2-norm)
         * of step vector, double
         * @return step vector, std::vector<double>
         */
        std::vector<double> step(int, double);

        std::default_random_engine _gen; // random engine generator for step
        std::uniform_real_distribution<double> _dist; // distribution for step
};

