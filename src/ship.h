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
		void rotate(double x, double y, double z);
	};	
}
