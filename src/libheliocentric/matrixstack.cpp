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

//void MatrixStack::translate(const vec3& vector) {
//}
//
//void MatrixStack::translate(float x, float y, float z) {
//}
//
//void MatrixStack::scale(const vec3& vector) {
//}
//
//void MatrixStack::scale(float x, float y, float z) {
//}
//
//void MatrixStack::scale(float factor) {
//}
//
//void MatrixStack::apply(const mat4& matrix) {
//}
//
//MatrixStack& MatrixStack::operator*=(const mat4& matrix) {
//}
