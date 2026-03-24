#include <iostream>
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

    // Optional: einfache Validierung
    if (width <= 0 || height <= 0 || maxIterations <= 0)
    {
        std::cout << "Invalid input values.\n";
        return 1;
    }

    Mandelbrot mandelbrot(width, height, maxIterations, minX, minY, maxX, maxY);

    std::cout << "\nGenerating Mandelbrot...\n";

    mandelbrot.generate();

    mandelbrot.save("mandelbrot.png");

    std::cout << "Done! Image saved as mandelbrot.png\n";
    system("start mandelbrot.png");

    return 0;
}