#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include "helion/mesh.h"

namespace render {
	bool Mesh::load(const std::string &path) {
		std::ifstream file(path.c_str());
		if(!file.is_open()) {
			return false;
		}
		std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		std::istringstream ss(contents);
		while(!ss.eof()) {
			std::string line;
			std::getline(ss, line);
			if(line.length()) {
				if((line[0] == 'v' && line[1] == ' ') || line[0] == 'f') {
					std::string parts;
					std::istringstream ssline(line);
					ssline >> parts;
					if(line[0] == 'v') {
						std::vector<double> vert;
						for(int i = 1; i <= 3; ++i) {
							ssline >> parts;
							vert.push_back(atof(parts.c_str()));
						}
						verts.push_back({vert[0], vert[1], vert[2]});
					} else {
						std::vector<int> face;
						for(int i = 1; i <= 3; ++i) {
							ssline >> parts;
							face.push_back(atoi(parts.c_str()));
						}
						faces.push_back({double(face[0]), double(face[1]), double(face[2])});
					}
				}
			}
		}
		return true;
	}

	void Mesh::render(double scale, sim::Vector position) {
		for(int i = 0; i < faces.size(); ++i) {
			glBegin(GL_TRIANGLES);
			for(int j = 0; j < 3; ++j) {
				int vert_no = 0;
				if(j == 0) {
					vert_no = faces[i].x - 1;
				} else {
					if(j == 1) {
						vert_no = faces[i].y - 1;
					} else {
						vert_no = faces[i].z - 1;
					}
				}
				glVertex3f(scale*verts[vert_no].x + position.x, scale*verts[vert_no].y+position.y, scale*verts[vert_no].z+position.z);
			}
			glEnd();
		}
	}

	double Mesh::height() {
		double maximum = 0;
		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].z > maximum) {
				maximum = verts[i].z;
			}
		}

		double minimum = maximum;

		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].z < minimum) {
				minimum = verts[i].z;
			}
		}
		return maximum - minimum;
	}

	double Mesh::width() {
		double maximum = 0;
		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].x > maximum) {
				maximum = verts[i].x;
			}
		}

		double minimum = maximum;

		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].x < minimum) {
				minimum = verts[i].x;
			}
		}
		return maximum - minimum;
	}

	double Mesh::breadth() {
		double maximum = 0;
		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].y > maximum) {
				maximum = verts[i].y;
			}
		}

		double minimum = maximum;

		for(int i = 0; i < verts.size(); ++i) {
			if(verts[i].y < minimum) {
				minimum = verts[i].y;
			}
		}
		return maximum - minimum;
	}
}

