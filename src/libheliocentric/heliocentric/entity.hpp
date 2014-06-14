#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <list>
#include <functional>
#include "matrixstack.hpp"

class Entity {
protected: 
    Entity* parent;
    std::list<Entity*> children;
    glm::vec3 position;
public:
    Entity();
    virtual ~Entity() {};
    virtual void update(double delta) {};
    virtual void render(MatrixStack& ms) {};
    void updateAll(double delta);
    void renderAll(MatrixStack& ms);
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    void addChild(Entity* child);
    bool removeChild(Entity* child);
    void orphanize();
};
#endif	/* ENTITY_HPP */

