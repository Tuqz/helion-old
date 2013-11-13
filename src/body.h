#pragma once
#include "vector.hpp"
#include "orbit.hpp"
#include "constants.h"
#include <cmath>
#include <string>

namespace sim {
	struct Body {
		Orbit orbit;
		double mass, radius, aop, lan, anomaly, time;
		std::string name, orb_desc;
		Body* central_mass;
		bool Sun;
		
		Body operator =(Body body);

		double grav_param() const;
		
		double period() const;
		
		void update(double delta_t);
		
		Vector pos();
	};
}
