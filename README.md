
# C++ND Capstone: Stochastic Fourier Solver with gnuplot

This is the repo for the implementation of my Capstone project in the Udacity C++ Nanodegree Program.

Mathematically speaking, in this program we want to solve

<img src="https://render.githubusercontent.com/render/math?math=f''(x) = g(x)">

for f(x), where

<img src="https://render.githubusercontent.com/render/math?math=g(x)=\frac{d^2}{dx^2} a e^{-k(x-x_0)^2} = a(-2 e^{-k(x-x_0)^2}k %2B+ 4e^{-k(x-x_0)^2}k^2(x-x_0)^2)">.

Without shift (for now, for simplicity we impose zero shift, i.e. we set x_0=0 in the program), this function is even and can thus be expressed as a Fourier-(cos)series:

<img src="https://render.githubusercontent.com/render/math?math=g(x) = \sum_{k=0}^{\infty}{a_k \cos(k x)}">,

where the a_k's are the coefficients of the series.
Thus, it is straightforward to use a truncated sum as our ansatz function for f(x):

<img src="https://render.githubusercontent.com/render/math?math=f(x) := \sum_{k=0}^{n-1}{c_k \cos(k x)}">,

where the c_k's are different (but related to a_k) coefficients, n is the total number of Fourier components used. Then, we can readily obtain the second derivate, f''(x):

<img src="https://render.githubusercontent.com/render/math?math=f''(x) = \sum_{k=0}^{n-1}{c_k (-k^2) \cos(k x)} = \sum_{k=0}^{n-1}{a_k \cos(k x)} \approx \sum_{k=0}^{\infty}{a_k \cos(k x)}">.


Of course, for this example we can numerically obtain the coefficients in O(n log(n)) using FFT libraries (such as [FFTW][fftw]) (or possibly even purely analytical), but to have some fun and get a smooth animation, we use a stochastic solver with adaptive learning rate lr to incrementally find our solution.
In other words, we train our coefficients (using bold for vector notation) using the following update rule:

<img src="https://render.githubusercontent.com/render/math?math=\mathbf{c}\leftarrow\mathbf{c}%2B+\text{step(lr)}">,

which occurs if and only if the L2 distance

<img src="https://render.githubusercontent.com/render/math?math=d:=L_2[f''(x), g(x)] = \sqrt{\int_{-\pi}^{\pi}{\lvert f''(x) - g(x) \rvert^2 \: dx}}">

would decrease with the new coefficients.

Within the code, this training process is done using a `D2Fourier` object which derives from the abstract base class `Function` (same for `Fourier`, `Gauss` and `D2Gauss`). The L2 distance functional is implemented by creating a `std::function<double(double)>`object from the function arguments via lambda function syntax. This object then is passed to the function `simpson` which implements the composite Simpson`s rule integrator.

Lastly, we update the solving process using `gnuplot`, which runs in a second `std::thread` using member function syntax. Since the `GnuplotFunctionViewer` class also overloads the `operator()`, we could have also passed the viewer instance itself to the thread constructor. To avoid data leaks in inter-thread communication, we use modern memory management techniques (in particular, `std::shared_ptr<T>` objects).

Due to nested namespaces this project requires C++17 (hence, gcc/g++ >= 6.0).

## Dependencies for Running Locally
* cmake >= 3.7
  * All OS: click [here][cmake] for installation instructions
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: install [Xcode][xcode] command line tools to get make
  * Windows: Click [here][makewin] for installation instructions
* gcc/g++ >= 6.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same as for make - [Xcode][xcode] command line tools
  * Windows: recommend using [MinGW][mingw]
* gnuplot
  * [Primary download site on SourceForge](https://sourceforge.net/projects/gnuplot/files/gnuplot/)
    * [git repository](https://sourceforge.net/p/gnuplot/gnuplot-main/ci/master/tree/)
  * Debian/Ubuntu: `sudo apt install gnuplot`
  * [Linux, Mac binaries][gnuplotbin]
  * [Windows binaries][gnuplotwin]

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run: `./StochasticFourierSolver`

[cmake]: <https://cmake.org/install>
[xcode]: <https://developer.apple.com/xcode/features/>
[makewin]: <http://gnuwin32.sourceforge.net/packages/make.htm>
[mingw]: <https://sourceforge.net/projects/mingw/>
[fftw]: <https://www.fftw.org>
[gnuplotbin]: <http://tmacchant33.starfree.jp/gnuplot_bin.html>
[gnuplotwin]: <http://tmacchant33.starfree.jp/gnuplot_bin.html>

## Rubric Points
The project fulfills (at least) the following rubric points (min. requirements: 5).
 1. The project demonstrates an understanding of C++ functions and control structures.
    * Control structures:
      * `if-else` statements (StochasticSolver.cpp:41)
      * `for-loops` (StochasticSolver.cpp:34)
      * `for-each` loops (main.cpp:83)
      * `while` loops (GnuplotFunctionViewer:52)
    * STL functions, different examples: 
      * `std::function` (MathUtil.hpp:121)
      * `std::inner_product` (StochasticSolver:67)
      * `std::max` (MathUtil.hpp:134)
      * `std::max_element` (MathUtil.hpp:146)
      * `std::transform` (StochasticSolver:74)
 2. The project uses Object Oriented Programming techniques.
    * Altogether, 7 classes are implemented:
      * `D2Fourier` (D2Fourier.hpp:19)
      * `D2Gauss` (D2Gauss.hpp:17)
      * `Fourier` (Fourier.hpp:19)
      * `Function` (abstract class) (Function.hpp:10)
      * `Gauss` (Gauss.hpp:15)
      * `GnuplotFunctionViewer` (GnuplotFunctionViewer:13)
      * `StochasticSolver` (StochasticSolver.hpp:20)
    * Organized into class attributes (e.g., Gauss.hpp:49) and class methods (e.g., Gauss.hpp:40).
 3. Classes follow an appropriate inheritance hierarchy.
    * Base class `Function` (Function:10).
    * Other classes representing functions (e.g., `Fourier`) inherit from `Function` (Fourier.hpp:19).
 4. Derived class functions override virtual base class functions.
    * Pure virtual function `Function::operator()`: `virtual  double  operator() (double  x) const = 0;` (Function:18) makes `Function` an abstract class.
    * Override virtual base class member function: `double  operator() (double  x) const  override;` (Fourier.hpp:33).
 5. The project uses smart pointers instead of raw pointers.
    * In this project, we use several times `std::shared_ptr<Function>`.
      * For example, `std::vector<std::shared_ptr<Function>> _vec_s_ptr` (GnuplotFunctionViewer:37) is a vector of shared pointers of (derived) `Function` objects (which we'll use to plot the functions).
 6. The project uses multithreading.
    * A second `std::thread` is created to plot the functions / interact with gnuplot (main:61).
