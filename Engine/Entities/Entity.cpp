#include "Entity.h"

//
//Entity::Entity(unsigned int entityID, glm::vec3 position)
//    : entityID(entityID), position(position) {
//}
//
//unsigned int Entity::getEntityID() { return entityID; }
//glm::vec3 Entity::getPosition() { return position; }

Entity::Entity(RawModel model, glm::vec3 position, glm::vec3 rotation, float scale)
	: model(model), position(position), rotation(rotation), scale(scale) { }

RawModel& Entity::getModel() { return model; }
glm::vec3 Entity::getPosition() { return position; }
glm::vec3 Entity::getRotation() { return rotation; }
float Entity::getScale() { return scale; }

void Entity::setPosition(glm::vec3 position) { this->position = position; }
void Entity::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Entity::setScale(float scale) { this->scale = scale; }