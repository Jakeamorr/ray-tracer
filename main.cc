#include <iostream>

int main() {
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render

    // PPM file format information
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    // Image information
    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            auto r = double(x) / (image_width - 1);
            auto g = double(y) / (image_height - 1);
            auto b = 0.25;

            // rgb values are normalized between 0 and 1, convert to value between 0-255
            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cerr << "\nDone.\n";
}