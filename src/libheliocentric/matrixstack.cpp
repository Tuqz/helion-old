#include <glm/gtc/type_ptr.hpp>

#include "heliocentric/matrixstack.hpp"

using namespace glm;

MatrixStack::MatrixStack() : MatrixStack(mat4()) {
}

MatrixStack::MatrixStack(mat4 current) {
    ms.push(current);
}

mat4& MatrixStack::top() {
    return ms.top();
}

void MatrixStack::push() {
    ms.push(mat4(ms.top()));
}

void MatrixStack::pop() {
    ms.pop();
    if (ms.size() == 0) {
        ms.push(mat4());
    }
}

float* MatrixStack::array() {
    return value_ptr(ms.top());
}

void MatrixStack::apply(const mat4& matrix) {
    ms.top() *= matrix;
}

void MatrixStack::apply(const quat& quaternion) {
    apply(glm::mat4_cast(quaternion));
}

MatrixStack& MatrixStack::operator*=(const mat4& matrix) {
    apply(matrix);
    return *this;
}