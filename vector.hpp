#pragma once
#include <cmath>

namespace sim {
	struct Vector {
		double x, y, z;
		double magnitude() const {
			//Oppa pythag time!
			return std::sqrt((x * x) + (y * y) + (z * z));
		}
		Vector operator +(const Vector& other) const {
			return {x + other.x, y + other.y, z + other.z};
		}
		Vector operator *(double in_x) const {
			return {x * in_x, y * in_x, z * in_x};
		}
		//dot-product
		static double dot(const Vector& one, const Vector& two) {
			return (one.x * two.x) + (one.y * two.y) + (one.z * two.z);
		}
		//cross-product
		static Vector cross(const Vector& one, const Vector& two) {
			return {one.y * two.z - one.z * two.y, one.z * two.x - one.x * two.z, one.x * two.y - one.y * two.x};
		}
	};
}
