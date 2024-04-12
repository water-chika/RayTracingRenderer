#pragma once

#include <utility>
#include "vec3.hpp"

namespace water {
	class camera {
	public:
		camera(double focal_length, std::pair<double, double> viewport_resolution, vec3 camera_center)
			:
			m_focal_length{ focal_length },
			m_viewport_resolution{ viewport_resolution },
			m_camera_center{ camera_center }
		{
		}
		double get_focal_length() const {
			return m_focal_length;
		}
		auto get_viewport_resolution() const {
			return m_viewport_resolution;
		}
		auto get_center() const {
			return m_camera_center;
		}
	private:
		double m_focal_length;
		std::pair<double, double> m_viewport_resolution;
		vec3 m_camera_center;
	};
}
