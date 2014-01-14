#pragma once

#include <GL/gl.h>
#include "body.h"
#include "ship.h"
#include "converter.hpp"

namespace render {
	void planet_render(sim::Body body, double scale_factor);
	void ship_render(sim::Ship ship, double scale_factor);
	void orbit_render(sim::Body body, double scale_factor);
	void orbit_render(sim::Ship ship, double scale_factor);
}
