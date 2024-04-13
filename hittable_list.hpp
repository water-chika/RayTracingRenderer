#pragma once

#include "hittable.hpp"

#include <vector>
#include <memory>

namespace water {
	class hittable_list : public hittable {
	public:
		hittable_list() = default;
		hittable_list(std::shared_ptr<hittable> object) : m_objects{ object } {}
		void clear() { m_objects.clear(); }
		void add(std::shared_ptr<hittable> object) {
			m_objects.push_back(object);
		}
		std::optional<hit_record> hit(const ray& r, interval ray_interval) const override {
			std::optional<hit_record> res{};
			auto closest_so_far = ray_interval.max();

			for (const auto& object : m_objects) {
				auto hit_res = object->hit(r, interval{ ray_interval.min(), closest_so_far });
				if (hit_res.has_value()) {
					closest_so_far = hit_res.value().t;
					res = hit_res;
				}
			}
			return res;
		}
	private:
		std::vector<std::shared_ptr<hittable>> m_objects;
	};
}