#include "heliocentric/entity.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

#include <cstddef> //For NULL

using namespace std;

Entity::Entity() : Entity(NULL) {
}

Entity::Entity(Appearance* appearance) : parent(NULL), appearance(appearance) {
}

void Entity::addChild(Entity* child) {
    child->parent = this;
    children.push_back(child);
}

bool Entity::removeChild(Entity* child) {
    parent->children.remove(child);
    parent = NULL;
}

void Entity::orphanize() {
    parent->removeChild(this);
}

void Entity::updateAll(double delta) {
    update(delta);
    for (Entity* e : children) {
        e->updateAll(delta);
    }
}

void Entity::renderAll(MatrixStack& ms) {
    ms.push();
    render(ms);
    for (Entity* e : children) {
        e->renderAll(ms);
    }
    ms.pop();
}

void Entity::render(MatrixStack& ms) {
    ms *= glm::translate(glm::mat4(), position);
    ms.apply(orientation);
    if (appearance != NULL) {
        glUseProgram(appearance->getShaderProgram()->getProgram());
        glUniformMatrix4fv(
                appearance->getShaderProgram()->getUniformLocation("modelToCameraMatrix"),
                1, GL_FALSE, ms.array());
        appearance->render(ms);
        glUseProgram(0);
    }
};

void Entity::setPosition(glm::vec3 position) {
    this->position = position;
}

void Entity::translate(float x, float y, float z) {
    translate(glm::vec3(x, y, z));
}

void Entity::translate(glm::vec3 v) {
    setPosition(position + v);
}

glm::vec3 Entity::getPosition() {
    return position;
}

void Entity::setOrientation(glm::quat orientation) {
    this->orientation = orientation;
}

glm::quat Entity::getOrientation() {
    return orientation;
}

void Entity::rotate(glm::quat q) {
    setOrientation(orientation * q);
}

void Entity::rotate(glm::vec3 axis, float angleRad) {
    float scalar = cos(angleRad / 2.0f);
    axis = glm::normalize(axis) * sin(angleRad / 2.0f);
    rotate(glm::quat(scalar, axis.x, axis.y, axis.z));
}

void Entity::rotateDeg(glm::vec3 axis, float angleDeg) {
    rotate(axis, angleDeg * M_PI / 180);
}