#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "../models/RawModel.h"

class Entity {
public:
    Entity(RawModel model, glm::vec3 position, glm::vec3 rotation, float scale, std::string name = "Entity");

    RawModel& getModel();
    glm::vec3 getPosition();      
    glm::vec3 getRotation();
    float getScale();
    std::string getEntityName();

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(float scale);
    void setName(std::string name);

private:
    RawModel model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
    std::string name;
};