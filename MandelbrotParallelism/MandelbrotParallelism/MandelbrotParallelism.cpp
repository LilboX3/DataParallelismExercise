#include <iostream>
#include <chrono>
#include "Mandelbrot.h"

int main()
{
    int width, height, maxIterations;
    double minX, minY, maxX, maxY;

    std::cout << "Enter image width: ";
    std::cin >> width;

    std::cout << "Enter image height: ";
    std::cin >> height;

    std::cout << "Enter max iterations: ";
    std::cin >> maxIterations;

    std::cout << "Enter viewport (minX minY maxX maxY): ";
    std::cin >> minX >> minY >> maxX >> maxY;

    if (width <= 0 || height <= 0 || maxIterations <= 0)
    {
        std::cout << "Invalid input values.\n";
        return 1;
    }

    Mandelbrot mandelbrot(width, height, maxIterations, minX, minY, maxX, maxY);

    int maxThreads = omp_get_max_threads();

    std::cout << "Max available threads: " << maxThreads << "\n\n";
    std::cout << "\nGenerating Mandelbrot...\n";

    auto start = std::chrono::high_resolution_clock::now();
    mandelbrot.generate(maxThreads);
    auto end = std::chrono::high_resolution_clock::now();
    double time = std::chrono::duration<double>(end - start).count();

    /*mandelbrot.save("mandelbrot.png");*/

    std::cout << "Done in " << time << " seconds."; // << "Image saved as mandelbrot.png\n";
    /*system("start mandelbrot.png");*/

    return 0;
}