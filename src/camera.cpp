#include "camera.h"

namespace render {

	void Camera::lookAt(sim::Vector new_look) {
		lookat = new_look;
		refresh();
	}

	void Camera::translate(sim::Vector shift) {
		pos = pos + shift;
		refresh();
	}

	void Camera::rotate(sim::Vector point, double x, double y, double z) {
		sim::Vector rot_x[3] = {{1, 0, 0}, {0, cos(x), -sin(x)}, {0, sin(x), cos(x)}};
		sim::Vector delta = pos + (point * -1);
		sim::Vector delta_rot_x = {sim::Vector::dot(delta, rot_x[0]), sim::Vector::dot(delta, rot_x[1]), sim::Vector::dot(delta, rot_x[2])};
		sim::Vector rot_y[3] = {{cos(y), 0, sin(y)}, {0, 1, 0}, {-sin(y), 0, cos(y)}};
		sim::Vector delta_rot_y = {sim::Vector::dot(delta_rot_x, rot_y[0]), sim::Vector::dot(delta_rot_x, rot_y[1]), sim::Vector::dot(delta_rot_x, rot_y[2])};
		sim::Vector rot_z[3] = {{cos(z), -sin(z), 0}, {sin(z), cos(z), 0}, {0, 0, 1}};
		sim::Vector delta_rot_z = {sim::Vector::dot(delta_rot_y, rot_z[0]), sim::Vector::dot(delta_rot_y, rot_z[1]), sim::Vector::dot(delta_rot_y, rot_z[2])};
		pos = point + delta_rot_z;
		refresh();
	}

	void Camera::refresh() {
		gluLookAt(pos.x, pos.y, pos.z, lookat.x, lookat.y, lookat.z, up.x, up.y, up.z);
	}
}
