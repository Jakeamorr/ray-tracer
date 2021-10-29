#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"

#include <iostream>

// Using the equation of sphere and vector algebra to determine whether or not a ray intersects our sphere.
// We simplify to a quadratic equation -b +- sqrt(b^2 -4ac)/2a
double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

// Create linear gradient
color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we exceed the ray bounce limit, no more light is gathered
    // Ensures the following recursive call to ray_color doesn't overflow the stack
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.01, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Camera
    camera cam;

    // Render
    // PPM file format information
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    // Being timer for render
    auto start = std::chrono::steady_clock::now();

    // Image information
    for (int y = image_height - 1; y >= 0; --y) {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < image_width; ++x) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (x + random_double()) / (image_width - 1);
                auto v = (y + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    // Output render time
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cerr << "\nRender finsihed in " << duration.count() << " seconds.\n";
}
