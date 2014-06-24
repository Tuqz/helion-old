#include "heliocentric/mesh.hpp"
#include "heliocentric/shaders.hpp"
#include <fstream>
#include <iostream>
#include <list>

using namespace std;

void Mesh::load(std::vector<float> vertexData, std::vector<unsigned short> indices, 
        ShaderProgram* sp) {
    this->vertexData = vertexData;
    this->indices = indices;
    this->sp = sp;
    load();
}

void Mesh::load() {
    // Upload data to VRAM
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
            sizeof (float) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            sizeof (unsigned short) * indices.size(), &indices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::render(MatrixStack& ms) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (8 * sizeof (float)), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (8 * sizeof (float)), (void*) (3 * sizeof (float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (8 * sizeof (float)), (void*) (6 * sizeof (float)));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ShaderProgram* Mesh::getShaderProgram() {
    return sp;
}