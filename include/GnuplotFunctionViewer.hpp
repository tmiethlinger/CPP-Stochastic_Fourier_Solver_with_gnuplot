//
//  GnuplotFunctionViewer.hpp
//

#pragma once

#include <memory>
#include <vector>

#include "Function.hpp"


class GnuplotFunctionViewer
{
    public:
        /**
         * @brief Construct a new Gnuplot Function Viewer object from
         * vector of (shared) pointers to derived Function objects.
         * @param vec_s_ptr Vector of shared pointers of functions to be plotted
         */
        GnuplotFunctionViewer(std::vector<std::shared_ptr<Function>> vec_s_ptr);

        /**
         * @brief Handle Gnuplot to make animation during StochasticSolver::solve.
         * Plots all functions stored in _vec_s_ptr;
         * Implement operator() in order to be able to
         * start new threads with function objects.
         */
        void operator()();

        /**
         * @brief Stops Gnuplot plotting.
         */
        void stop();

    private:
        std::vector<std::shared_ptr<Function>> _vec_s_ptr; // Vector of function pointers

        bool _run; // _state == true -> keep running/plotting
        int _n; // size of vector of function pointers
};