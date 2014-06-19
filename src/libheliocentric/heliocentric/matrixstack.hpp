#ifndef MATRIXSTACK_HPP
#define	MATRIXSTACK_HPP

#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
    void apply(const glm::mat4& matrix);
    void apply(const glm::quat& quaternion);
    MatrixStack& operator*=(const glm::mat4& matrix);
};

#endif	/* MATRIXSTACK_HPP */

