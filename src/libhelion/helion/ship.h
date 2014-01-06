#pragma once

#include <vector>
#include "body.h"
#include "orbit.hpp"
#include "vector.hpp"
#include "part.h"

namespace sim {
	struct Ship {
		Body* central_mass;
		Orbit orbit;
		std::vector<Part> parts;
		Vector rotation;
		double aop, lan, anomaly, time;
		void rotate(double x, double y, double z);
		double period();
		void update(double delta_t);
		Vector pos();
		Vector vel();
	};	
}
