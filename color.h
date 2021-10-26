#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

void write_color(std::ostream &out, color pixel_color) {
    // Output the translasted (0-255) value of the pixel color
    out << static_cast<int>(255.99 * pixel_color.x()) << ' '
        << static_cast<int>(255.99 * pixel_color.y()) << ' '
        << static_cast<int>(255.99 * pixel_color.z()) << '\n';
}

#endif
