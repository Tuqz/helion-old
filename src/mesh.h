#include <vector>
#include <string>
#include "vector.hpp"
#include <GL/gl.h>

namespace render {
	struct Mesh {
	public:
		bool load(const std::string &path);
		void render();	
	private:
		std::vector<sim::Vector> verts;
		std::vector<sim::Vector> faces;
	};
}
