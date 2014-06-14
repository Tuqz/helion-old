#ifndef MATRIXSTACK_HPP
#define	MATRIXSTACK_HPP

#include <stack>
#include <glm/glm.hpp>

class MatrixStack {
private:
    std::stack<glm::mat4> ms;
public:
    MatrixStack();
    MatrixStack(glm::mat4 current);
    glm::mat4& top();
    void push();
    void pop();
    void translate(const glm::vec3& vector);
    void translate(float x, float y, float z);
    void scale (const glm::vec3& vector);
    void scale(float x, float y, float z);
    void scale(float factor);
    void apply(const glm::mat4& matrix);
    MatrixStack& operator*=(const glm::mat4& matrix);
};

#endif	/* MATRIXSTACK_HPP */

