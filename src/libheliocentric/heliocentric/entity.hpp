#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <list>
#include <functional>
#include "matrixstack.hpp"
#include "shaders.hpp"

class Appearance {
public:
//    virtual ~Appearance() {};
    virtual void render(MatrixStack& ms) = 0;
    virtual ShaderProgram* getProgram() = 0;
};

class Entity {
protected: 
    Entity* parent;
    std::list<Entity*> children;
    glm::vec3 position;
    Appearance* appearance;
public:
    Entity();
    Entity(Appearance* appearance);
    virtual ~Entity() {};
    virtual void update(double delta) {};
    virtual void render(MatrixStack& ms);
    void updateAll(double delta);
    void renderAll(MatrixStack& ms);
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    void addChild(Entity* child);
    bool removeChild(Entity* child);
    void orphanize();
};

#endif	/* ENTITY_HPP */