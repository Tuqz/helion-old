#ifndef MESH_HPP
#define	MESH_HPP

#include "core.hpp"
#include <string>
#include <vector>

class Mesh {
private:
    std::vector<float> vertexData;
    std::vector<unsigned short> indices;
    unsigned short nVertices, nNormals, nFaces;
    GLuint vbo, ebo;
public:
    bool load(const std::string& filename);
    void render();
    long unsigned int numberOfVertices();
    long unsigned int numberOfNormals();
    long unsigned int numberOfFaces();
};

#endif	/* MESH_HPP */