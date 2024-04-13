#pragma once

#include "ray.hpp"
#include <optional>
#include <vec3.hpp>
#include "interval.hpp"

namespace water {
	class hit_record {
	public:
		vec3 p;
		vec3 normal;
		double t;
		bool front_face;

		void set_face_normal(const ray& r, const vec3& outward_normal) {
			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
	};

	class hittable {
	public:
		virtual ~hittable() = default;
		virtual std::optional<hit_record> hit(const ray& r, interval ray_interval) const = 0;
	};
}