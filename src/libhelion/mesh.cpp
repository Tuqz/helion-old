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
		while(!file.eof())
		{
			std::string line;
			std::getline(file, line);
			if(line.length())
			{
				if((line[0] == 'v' && line[1] == ' ') || line[0] == 'f')
				{
					char type;
					sim::Vector points;
					std::stringstream ss(line);

					if(!(ss >> type >> points.x >> points.y >> points.z))
						return false;

					if(type == 'v')
						verts.push_back(points);
					else
						faces.push_back(points);
				}
			}
		}
		file.close();
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

