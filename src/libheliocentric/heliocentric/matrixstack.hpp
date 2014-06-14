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
    float* array();
    MatrixStack& operator*=(const glm::mat4& matrix);
};

#endif	/* MATRIXSTACK_HPP */

