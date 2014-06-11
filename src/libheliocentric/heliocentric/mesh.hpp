#include "core.hpp"
#include <string>
#include <vector>

class Mesh {
private:
    std::vector<float> vertexData;
    std::vector<unsigned short> indices;
    GLuint vbo, ebo;
public:
    bool load(const std::string& filename);
    void render();
    long unsigned int numberOfVertices();
};

