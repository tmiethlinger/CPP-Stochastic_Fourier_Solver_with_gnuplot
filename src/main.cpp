// Thomas Miethlinger
// March 2022
// Udacity C++ Nanodegree: Capstone project
// Title: "Stochastic Fourier Solver with gnuplot"
// solve_f f''(x) = g(x), where:
// f is a Fourier series
// g(x) is the second derivative of a Gaussian.
// Takes ~10 seconds with standard settings.

#include <iostream>
#include <thread>

#include "D2Fourier.hpp"
#include "D2Gauss.hpp"
#include "Fourier.hpp"
#include "Gauss.hpp"
#include "GnuplotFunctionViewer.hpp"
#include "MathUtil.hpp"
#include "StochasticSolver.hpp"


// Helper functions
template <typename T>
void print_vector(const std::vector<T>&);

// We don't parse command line arguments since I neither like
// getopt nor boost::program_options ...
int main()
{
    // Define RHS g(x), which is the second derivative of a Gaussian with:
    double a = 1.0; // amplitude
    double k = 4.0; // kernel width
    double x0 = 0.0; // shift (please keep that fixed, since we only include cos() terms)
    std::shared_ptr<D2Gauss> g_s_ptr = std::make_shared<D2Gauss>(a, k, x0);

    // We also want to plot the analytical solution, the original Gaussian.
    std::shared_ptr<Gauss> sol_s_ptr = std::make_shared<Gauss>(a, k, x0);

    // Define solver object, using a specified seed
    unsigned int seed = 1234u;
    StochasticSolver solver(seed);

    const int m = 1e5; // number of iterations in solver
    const int n = 10; // number of Fourier-(cos)coefficients
    const int N = 100; // number of discrete intervals for numeric integration
    double lr = 1e-4; // use smaller lr for nicer animation

    // Create shared pointer of D2Fourier object representing f''(x),
    // initialized with an coefficients zero.
    std::shared_ptr<D2Fourier> d2f_s_ptr = std::make_shared<D2Fourier>(std::vector<double>(n));

    // Create shared pointer of Fourier object representing f(x),
    // which we get "for free" if we determine f''(x)
    std::shared_ptr<Fourier> f_s_ptr = std::make_shared<Fourier>(d2f_s_ptr);

    // Create a GnuplotFunctionViewer object from the 4 derived Function objects.
    GnuplotFunctionViewer gnuplot_viewer({d2f_s_ptr, g_s_ptr, f_s_ptr, sol_s_ptr});

    // Start a second thread which runs gnuplot in the background,
    // plotting the current version of the functions.
    std::thread t = std::thread(&GnuplotFunctionViewer::operator(), &gnuplot_viewer);

    // Start solver, get solved D2Fourier object
    D2Fourier d2f = solver.solve(d2f_s_ptr, g_s_ptr, m, n, N, lr);

    // Give signal to stop plotting,
    gnuplot_viewer.stop();

    // and join threads
    t.join();

    // Write out information about the solving process
    std::cout << "Coefficients of Fourier-(cos)modes: " << std::endl;
    print_vector(d2f.get_coefficients());
    std::cout << "Final distance: " << MathUtil::Distance::L2(d2f, *g_s_ptr, -M_PI, M_PI, N) << std::endl;

    return 0;
}

template <typename T>
void print_vector(const std::vector<T>& vector)
{
    for(T elem : vector)
        std::cout << elem << " ";
    std::cout << std::endl;
}