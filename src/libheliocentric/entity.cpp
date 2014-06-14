#include "heliocentric/entity.hpp"

#include <cstddef> //For NULL

using namespace std;

Entity::Entity() : parent(NULL) {
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