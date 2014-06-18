#ifndef MESH_HPP
#define	MESH_HPP

#include "core.hpp"
#include "entity.hpp"
#include <vector>

class Mesh {
private:
    std::vector<float> vertexData;
    std::vector<unsigned short> indices;
    GLuint vbo, ebo;
public:
    void load(std::vector<float> vertexData, std::vector<unsigned short> indices);
    void load();
    void render();
};

class MeshAppearance : public Appearance {
private:
    Mesh* mesh;
    ShaderProgram* sp;
public:
    MeshAppearance(Mesh* mesh, ShaderProgram* sp);
    virtual void render(MatrixStack& ms);
    virtual ShaderProgram* getProgram();
};

#endif	/* MESH_HPP */