#include "Entity.h"


Entity::Entity(unsigned int entityID, glm::vec3 position)
    : entityID(entityID), position(position) {
}

unsigned int Entity::getEntityID() { return entityID; }
glm::vec3 Entity::getPosition() { return position; }