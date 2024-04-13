#include <vec3.hpp>
#include <image_outputer.hpp>
#include <draw_pixels.hpp>
#include "ray.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "renderer.hpp"

#include <limits>

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

water::vec3 ray_color(water::ray r, const water::hittable& world) {
	auto hit_res = world.hit(r, water::interval{0, std::numeric_limits<double>::infinity()});
	if (hit_res.has_value()) {
		return 0.5 * (hit_res.value().normal + water::vec3{1,1,1});
	}
	auto unit_direction = r.direction().unit();
	auto a = 0.5 * (unit_direction[1] + 1.0);
	return (1.0 - a) * water::vec3{ 1.0, 1.0, 1.0 } + a * water::vec3{ 0.5, 0.7, 1.0 };
}

int main() {
	uint32_t image_width = 800;
	uint32_t image_height = 600;

	water::hittable_list world{};

	using std::make_shared;
	using water::sphere;
	using water::vec3;
	
	world.add(std::make_shared<water::sphere>(water::vec3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));

	water::renderer renderer{ image_width, image_height };
	renderer.set_samples_per_pixels(1);
	renderer.render(world);

	return 0;
}