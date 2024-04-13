#pragma once

#include <limits>

namespace water {
	class interval {
	public:
		constexpr interval() : m_min{ +std::numeric_limits<double>::infinity() }, m_max{ -std::numeric_limits<double>::infinity() } {}
		constexpr interval(double min, double max) : m_min{ min }, m_max{ max } {}

		double size() const {
			return m_max - m_min;
		}
		
		bool contains(double x) const {
			return m_min <= x && x <= m_max;
		}
		bool surrounds(double x) const {
			return m_min < x && x < m_max;
		}
		double clamp(double x) const {
			return std::clamp(x, m_min, m_max);
		}
		static constexpr interval empty() {
			return interval{};
		}
		static constexpr interval universe() {
			return interval{ -std::numeric_limits<double>::infinity(), +std::numeric_limits<double>::infinity() };
		}
		double min() {
			return m_min;
		}
		double max() {
			return m_max;
		}
	private:
		double m_min;
		double m_max;
	};
}