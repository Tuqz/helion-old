#ifndef MESH_HPP
#define	MESH_HPP

#include "core.hpp"
#include "entity.hpp"
#include <vector>

class Mesh : public Appearance {
private:
    std::vector<float> vertexData;
    std::vector<unsigned short> indices;
    GLuint vbo, ebo;
    ShaderProgram* sp;
public:
    void load(std::vector<float> vertexData, std::vector<unsigned short> indices, 
            ShaderProgram* sp);
    void load();
    void render();
    virtual void render(MatrixStack& ms);
    virtual ShaderProgram* getShaderProgram();
};

#endif	/* MESH_HPP */