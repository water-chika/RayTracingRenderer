#include <vec3.hpp>
#include <image_outputer.hpp>
#include <draw_pixels.hpp>
#include "ray.hpp"
#include "camera.hpp"

std::optional<double> hit_sphere(const water::vec3& center, double radius, const water::ray& r) {
	auto oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return std::nullopt;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

water::vec3 ray_color(water::ray r) {
	auto t = hit_sphere(water::vec3{ 0, 0, -1 }, 0.5, r);
	if (t.has_value()) {
		auto N = (r.at(t.value()) - water::vec3{ 0, 0, -1 }).unit();
		return 0.5 * (N + water::vec3{ 1,1,1 });
	}
	auto unit_direction = r.direction().unit();
	auto a = 0.5 * (unit_direction[1] + 1.0);
	return (1.0 - a) * water::vec3{ 1.0, 1.0, 1.0 } + a * water::vec3{ 0.5, 0.7, 1.0 };
}

int main() {
	uint32_t image_width = 800;
	uint32_t image_height = 600;

	water::camera camera{ 1.0, {2.0 * static_cast<double>(image_width) / image_height, 2.0}, {0,0,0} };

	auto [viewport_width, viewport_height] = camera.get_viewport_resolution();
	auto viewport_u = water::vec3{ viewport_width, 0, 0 };
	auto viewport_v = water::vec3{ 0, -viewport_height, 0 };

	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	auto viewport_upper_left = 
		camera.get_center() - water::vec3{ 0,0,camera.get_focal_length()}
		- viewport_u / 2 - viewport_v / 2;
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	std::vector<uint32_t> image_data(image_width * image_height);
	for (uint32_t j = 0; j < image_height; j++) {
		for (uint32_t i = 0; i < image_width; i++) {
			auto x = i, y = j;
			auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
			auto ray_direction = pixel_center - camera.get_center();
			water::ray ray{ camera.get_center(), ray_direction };
			auto [r, g, b] = ray_color(ray);
			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);
			image_data[y * image_width + x] = (ir << 16) | (ig << 8) | ib;
		}
	}

	water::draw_pixels(image_width, image_height, image_data.data());
	return 0;
}