#pragma once
#include <iostream>
#include <vector>
#include <omp.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./stb_image_write.h"

class Mandelbrot
{
private:
    int width;
    int height;
    int maxIterations;

    double minX, minY, maxX, maxY;

    std::vector<unsigned char> image;

public:
    Mandelbrot(int w, int h, int maxIter,
        double minX, double minY, double maxX, double maxY, int numThreads)
        : width(w), height(h), maxIterations(maxIter),
        minX(minX), minY(minY), maxX(maxX), maxY(maxY)
    {
        omp_set_num_threads(numThreads);
        image.resize(width * height * 3); // RGB
    }

    void generate()
    {

#pragma omp parallel for
        for (int py = 0; py < height; py++)
        {
            for (int px = 0; px < width; px++)
            {
                computePixel(px, py);
            }
        }
    }

    void save(const char* filename)
    {
        stbi_write_png(filename, width, height, 3, image.data(), width * 3);
    }

private:

    void computePixel(int px, int py)
    {
        // map pixel to complex number
        double cx = minX + (double)px / width * (maxX - minX);
        double cy = minY + (double)py / height * (maxY - minY);

        double zx = cx;
        double zy = cy;

        int iteration = 0;

        // add to z iteration and decide pixel color
        for (int n = 0; n < maxIterations; n++)
        {
            double x = zx * zx - zy * zy + cx;
            double y = 2 * zx * zy + cy;

            if (x * x + y * y > 4.0)
            {
                iteration = n;
                break;
            }

            zx = x;
            zy = y;

            iteration = n;
        }

        setColor(px, py, iteration);
    }

    void setColor(int px, int py, int iteration)
    {
        int index = (py * width + px) * 3;

        if (iteration == maxIterations - 1)
        {
            // reached end --> black pixel
            image[index + 0] = 0;
            image[index + 1] = 0;
            image[index + 2] = 0;
        }
        else
        {
            // color based on n
            int color = (int)(255.0 * iteration / maxIterations);

            image[index + 0] = color;
            image[index + 1] = 0;
            image[index + 2] = 255 - color;
        }
    }
};

