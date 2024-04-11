#include <vec3.hpp>
#include <image_outputer.hpp>

int main() {
	uint32_t image_width = 256;
	uint32_t image_height = 256;
	water::output_ppm_image(image_width, image_height,
		[image_width, image_height](auto x, auto y) {
			return water::vec3{
				static_cast<double>(x) / (image_width - 1),
				static_cast<double>(y) / (image_height - 1),
				0.0
			};
		});
	return 0;
}