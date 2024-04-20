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
	renderer.set_samples_per_pixels(50);
	renderer.set_max_depth(50);
	renderer.render(world);

	return 0;
}