//
//  GnuplotFunctionViewer.cpp
//

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "GnuplotFunctionViewer.hpp"


void mysleep(unsigned ms)
{
    usleep(ms * 1000);
}

GnuplotFunctionViewer::GnuplotFunctionViewer(std::vector<std::shared_ptr<Function>> vec_s_ptr)
{
    _vec_s_ptr = vec_s_ptr;
    _n = vec_s_ptr.size();
    _run = false;
}

void GnuplotFunctionViewer::operator()()
{
    FILE* pipe;
    std::cout << "Opening gnuplot... ";
    pipe = popen("gnuplot -persist", "w");
    if (!pipe)
    {
        std::cout << "failed!" << std::endl;
        return;
    }
    else
    {
        std::cout << "succeded." << std::endl;
        _run = true;
    }

    fputs("set title 'C++ND Capstone Project: Stochastic Fourier Solver with gnuplot'\n", pipe);
    fflush(pipe);
    fputs("set samples 1000\n", pipe);
    fflush(pipe);
    fputs("set xlabel 'x'\n", pipe);
    fflush(pipe);
    fputs("set ylabel 'functions'\n", pipe);
    fflush(pipe);
    fputs("set yrange [-10:10]\n", pipe);
    fflush(pipe);
    std::string cmd;
    while(_run)
    {
        fputs("plot [-pi:pi] ", pipe);
        for(int j = 0; j < _n; j++)
        {
            std::shared_ptr<Function> f = _vec_s_ptr[j];
            cmd = f->gnuplot_plot() + " with lines title '" + f->gnuplot_title();
            cmd += j < (_n - 1) ? "', " : "'\n";
            fputs(cmd.c_str(), pipe);
        }
        fflush(pipe);
        mysleep(20);
    }
    pclose(pipe);
}

void GnuplotFunctionViewer::stop()
{
    _run = false;
}