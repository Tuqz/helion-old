#pragma once

#include "vector.hpp"
#include <GL/glu.h>

namespace render {

	struct Camera {
		sim::Vector pos;
		sim::Vector lookat;
		sim::Vector up;
		void lookAt(sim::Vector new_look);
		void translate(sim::Vector shift);
		void rotate(sim::Vector point, double x, double y, double z);
		void refresh();
	};
}
