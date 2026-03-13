#pragma once
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Entity {
public:
    Entity(unsigned int entityID, glm::vec3 position);

    unsigned int getEntityID();   
    glm::vec3 getPosition();      

private:
    unsigned int entityID;        
    glm::vec3 position;
};