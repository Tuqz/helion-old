#ifndef ENTITY_HPP
#define	ENTITY_HPP

#include <list>
#include <functional>
#include "matrixstack.hpp"
#include "shaders.hpp"
#include "glm/gtc/quaternion.hpp"

class Appearance {
public:

    virtual ~Appearance() {
    };
    virtual void render(MatrixStack& ms) = 0;
    virtual ShaderProgram* getShaderProgram() = 0;
};

class Entity {
protected:
    Entity* parent;
    std::list<Entity*> children;
    glm::vec3 position;
    glm::quat orientation;
    Appearance* appearance;
public:
    Entity();
    Entity(Appearance* appearance);

    virtual ~Entity() {};

    virtual void update(double delta) {};
    virtual void render(MatrixStack& ms);
    void updateAll(double delta);
    void renderAll(MatrixStack& ms);

    void addChild(Entity* child);
    bool removeChild(Entity* child);
    void orphanize();

    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
    void translate(float x, float y, float z);
    void translate(glm::vec3 v);
    
    void setOrientation(glm::quat orientation);
    glm::quat getOrientation();
    void rotate(glm::quat q);
    void rotate(glm::vec3 axis, float angleRad);
    void rotateDeg(glm::vec3 axis, float angleRad);
};

#endif	/* ENTITY_HPP */