#include "render.h"
#include <iostream>

namespace render {
	void planet_render(sim::Body body, double scale_factor) {
		sim::Vector pos = body.pos();
		while (!in_body.Sun) {
			pos = pos + Body.pos();
		}
		pos = pos*scale_factor;
		glPointSize(1);
		glBegin(GL_POINTS);
		glVertex3f(pos.x, pos.y, pos.z);
		glEnd();
	}
}
