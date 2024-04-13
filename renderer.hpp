#pragma once

#include "camera.hpp"
#include "hittable.hpp"
#include <draw_pixels.hpp>

#include <vector>
#include <random>

namespace water {
	class renderer {
	public:
		renderer(uint32_t image_width, uint32_t image_height) 
			:
			m_image_width{image_width}, m_image_height{image_height},
			m_camera{ 1.0, {2.0 * static_cast<double>(image_width) / image_height, 2.0}, {0,0,0} },
			m_samples_per_pixel{ 10 },
			m_samples_offset{ generate_samples_offset(10) }
		{
			initialize();
		}
		void render(const hittable& world)
		{
			std::vector<uint32_t> image_data(m_image_width * m_image_height);
			for (uint32_t j = 0; j < m_image_height; j++) {
				for (uint32_t i = 0; i < m_image_width; i++) {
					vec3 pixel_color{ 0,0,0 };
					for (auto [x_offset, y_offset] : m_samples_offset) {
						auto x = i + x_offset, y = j + y_offset;
						auto pixel_sample = m_pixel00_loc + (x * m_pixel_delta_u) + (y * m_pixel_delta_v);
						auto ray_direction = pixel_sample - m_camera.get_center();
						water::ray ray{ m_camera.get_center(), ray_direction };
						pixel_color += ray_color(ray, world);
					}
					pixel_color /= m_samples_per_pixel;
					auto [r, g, b] = pixel_color;
					constexpr interval intensity(0.0, 0.999);
					int ir = static_cast<int>(255.999 * intensity.clamp(r));
					int ig = static_cast<int>(255.999 * intensity.clamp(g));
					int ib = static_cast<int>(255.999 * intensity.clamp(b));
					image_data[j * m_image_width + i] = (ir << 16) | (ig << 8) | ib;
				}
			}

			water::draw_pixels(m_image_width, m_image_height, image_data.data());
		}
		void set_samples_per_pixels(uint32_t spp) {
			m_samples_per_pixel = spp;
			m_samples_offset = generate_samples_offset(m_samples_per_pixel);
		}
	private:
		void initialize() {
			auto [viewport_width, viewport_height] = m_camera.get_viewport_resolution();
			auto viewport_u = water::vec3{ viewport_width, 0, 0 };
			auto viewport_v = water::vec3{ 0, -viewport_height, 0 };

			m_pixel_delta_u = viewport_u / m_image_width;
			m_pixel_delta_v = viewport_v / m_image_height;

			auto viewport_upper_left =
				m_camera.get_center() - water::vec3{ 0,0,m_camera.get_focal_length() }
			- viewport_u / 2 - viewport_v / 2;
			m_pixel00_loc = viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
		}
		vec3 ray_color(const ray& r, const hittable& world) const {
			auto hit_res = world.hit(r, water::interval{ 0, std::numeric_limits<double>::infinity() });
			if (hit_res.has_value()) {
				return 0.5 * (hit_res.value().normal + water::vec3{ 1,1,1 });
			}
			auto unit_direction = r.direction().unit();
			auto a = 0.5 * (unit_direction[1] + 1.0);
			return (1.0 - a) * water::vec3{ 1.0, 1.0, 1.0 } + a * water::vec3{ 0.5, 0.7, 1.0 };
		}
		static std::vector<std::pair<double, double>> generate_samples_offset(uint32_t samples_number) {
			std::vector<std::pair<double, double>> offsets(samples_number);
			std::uniform_real_distribution<double> dist{ 0.0, 1.0 };
			std::mt19937 generator{};
			for (auto& offset : offsets) {
				auto& [x, y] = offset;
				x = dist(generator);
				y = dist(generator);
			}
			return offsets;
		}
		camera m_camera;
		uint32_t m_image_width;
		uint32_t m_image_height;
		vec3 m_pixel00_loc;
		vec3 m_pixel_delta_u;
		vec3 m_pixel_delta_v;
		uint32_t m_samples_per_pixel;
		std::vector<std::pair<double, double>> m_samples_offset;
	};
}