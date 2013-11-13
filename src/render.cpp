#include "render.h"
#include <iostream>

namespace render {
	void planet_render(sim::Body body, double scale_factor) {
		sim::Vector pos = {0, 0, 0};
		sim::Body in_body = body;
		while (!in_body.Sun) { //Untill you are at the Sun, add on the thing you are orbiting's postion to yours.
			pos = pos + in_body.pos();
			in_body = *in_body.central_mass;
		}
		pos = pos*scale_factor;
		glPointSize(2);
		glBegin(GL_POINTS);
		glVertex3f(pos.x, pos.z, pos.y);
		glEnd();
	}
}
