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
		glPointSize(4);
		glBegin(GL_POINTS);
		glVertex3f(pos.x, pos.z, pos.y);
		glEnd();
	}

	void orbit_render(sim::Body body, double scale_factor) {
		sim::Vector pos = {0, 0, 0};
		sim::Body in_body = *body.central_mass;
		glBegin(GL_LINE_LOOP);
		for(double i = 0; i < 360; ++i) {
			double semilatus = body.orbit.semimajor*(1-(body.orbit.eccentricity*body.orbit.eccentricity));
			double distance = semilatus/(1 + body.orbit.eccentricity*cos(deg_to_rad(i)));
			sim::Vector pos = {distance * cos(deg_to_rad(i)), distance * sin(deg_to_rad(i)), 0};
			sim::Vector R[3] = {{cos(body.lan)*cos(body.aop) - sin(body.lan)*sin(body.aop)*cos(body.orbit.inclination), -cos(body.lan)*sin(body.aop)-sin(body.lan)*cos(body.aop)*cos(body.orbit.inclination), sin(body.lan)*sin(body.orbit.inclination)}, {sin(body.lan)*cos(body.aop)+cos(body.lan)*sin(body.aop)*cos(body.orbit.inclination), -sin(body.lan)*sin(body.aop)+cos(body.lan)*cos(body.aop)*cos(body.orbit.inclination), -cos(body.lan)*sin(body.orbit.inclination)}, {sin(body.aop)*sin(body.orbit.inclination), cos(body.aop)*sin(body.orbit.inclination), cos(body.orbit.inclination)}}; //Conversion matrix
			sim::Vector glob_pos = {sim::Vector::dot(R[0], pos), sim::Vector::dot(R[1], pos), sim::Vector::dot(R[2], pos)};
			while(!in_body.Sun) {
				glob_pos = glob_pos + in_body.pos();
				in_body = *in_body.central_mass;
			}
			glVertex3f(glob_pos.x*scale_factor, glob_pos.z*scale_factor, glob_pos.y*scale_factor);
		}
		glEnd();
	}
}
