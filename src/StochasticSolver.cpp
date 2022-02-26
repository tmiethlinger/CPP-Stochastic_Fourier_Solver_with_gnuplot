//
//  StochasticSolver.cpp
//

#include <algorithm> // std::transform
#include <numeric> // std::inner_product

#include "MathUtil.hpp"
#include "StochasticSolver.hpp"


StochasticSolver::StochasticSolver()
{
    _gen = std::default_random_engine(1);
    _dist = std::uniform_real_distribution<double>(-1.0, 1.0);
}

StochasticSolver::StochasticSolver(int seed)
{
    _gen = std::default_random_engine(seed);
    _dist = std::uniform_real_distribution<double>(-1.0, 1.0);
}
#include <iostream>
D2Fourier StochasticSolver::solve(
    std::shared_ptr<D2Fourier> d2f_s_ptr,
    std::shared_ptr<D2Gauss> g_s_ptr,
    int m, int n, int N, double lr
)
{
    std::vector<double> c0 = d2f_s_ptr->get_coefficients();
    std::vector<double> c1 = c0;
    D2Fourier d2f_prev(c1);
    std::vector<double> dc(n);
    for(int i = 0, i_lr = 0; i < m; i++)
    {
        dc = step(n, lr);
        std::transform(c0.begin(), c0.end(), dc.begin(),
                       c1.begin(), std::plus<double>()
        );
        d2f_s_ptr->set_coefficients(c1);
        if(MathUtil::Distance::L2(*d2f_s_ptr, *g_s_ptr, -M_PI, M_PI, N) <
            MathUtil::Distance::L2(d2f_prev, *g_s_ptr, -M_PI, M_PI, N))
        {
            c0 = d2f_s_ptr->get_coefficients();
            d2f_prev.set_coefficients(c0);
            i_lr = 0;
        }
        else
        {
            i_lr++;
            if(i_lr % 100 == 0)
                lr *= 0.9;
        }
    }

    return D2Fourier(*d2f_s_ptr);
}

std::vector<double> StochasticSolver::step(int n, double lr)
{
    std::vector<double> dc(n);
    for(int i = 0; i < n; i++)
    {
        dc[i] = _dist(_gen);
    }
    double norm = sqrt(
        std::inner_product(
            dc.begin(), dc.end(),
            dc.begin(), 0.0
        )
    );
    std::transform(
        dc.begin(), dc.end(),
        dc.begin(), [lr, norm](double d){ return lr * d/norm; }
    );
    return dc;
}