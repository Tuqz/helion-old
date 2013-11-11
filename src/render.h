#pragma once

#include <GL/gl.h>
#include "body.h"

namespace render {
	void planet_render(sim::Body body, double scale_factor);
}
