#include <iostream>
#include "color.h"

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
            double normalized_x_coord = double(x) / (image_width - 1);
            double normalized_y_coord = double(y) / (image_height - 1);
            color pixel_color(normalized_x_coord, normalized_y_coord, 0.25);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}
