#include <vector>
#include <string>
#include "vector.hpp"
#include <GL/gl.h>

namespace render {
	struct Mesh {
	public:
		bool load(const std::string &path);
		void render(double scale, sim::Vector position);	
		double height();
		double width();
		double breadth();
	private:
		std::vector<sim::Vector> verts;
		std::vector<std::vector<int>> faces;
		std::vector<sim::Vector> normals;
	};
}
