#pragma once

#include "hittable.hpp"
#include <vec3.hpp>
#include <algorithm>

namespace water {
	class sphere : public hittable {
	public:
		sphere(const vec3& center, double radius) : m_center{ center }, m_radius{ std::max(0.0, radius) } {}
		std::optional<hit_record> hit(const ray& r, interval ray_interval) const override {
			vec3 oc = m_center - r.origin();
			auto a = r.direction().length_squared();
			auto h = dot(r.direction(), oc);
			auto c = oc.length_squared() - m_radius * m_radius;
			
			auto discriminant = h * h - a * c;
			if (discriminant < 0)
				return std::nullopt;

			auto sqrtd = sqrt(discriminant);

			auto root = (h - sqrtd) / a;
			if (!ray_interval.surrounds(root)) {
				root = (h + sqrtd) / a;
				if (!ray_interval.surrounds(root))
					return std::nullopt;
			}
			hit_record res{};
			res.t = root;
			res.p = r.at(res.t);
			vec3 outward_normal = (res.p - m_center) / m_radius;
			res.set_face_normal(r, outward_normal);
			return res;
		}
	private:
		vec3 m_center;
		double m_radius;
	};
}