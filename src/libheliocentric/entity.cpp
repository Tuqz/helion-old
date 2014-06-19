#include "heliocentric/entity.hpp"
#include <glm/gtc/matrix_transform.hpp> 

#include <cstddef> //For NULL

using namespace std;

Entity::Entity() : Entity(NULL) {
}

Entity::Entity(Appearance* appearance) : parent(NULL), appearance(appearance) {
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

glm::vec3 Entity::getPosition() {
    return position;
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