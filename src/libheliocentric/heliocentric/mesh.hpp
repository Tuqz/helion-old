#ifndef MESH_HPP
#define	MESH_HPP

#include "core.hpp"
#include <vector>

class Mesh {
private:
    std::vector<float> vertexData;
    std::vector<unsigned short> indices;
    GLuint vbo, ebo;
public:
//    bool load(const std::string& filename);
    void load(std::vector<float> vertexData, std::vector<unsigned short> indices);
    void load();
    void render();
};

#endif	/* MESH_HPP */