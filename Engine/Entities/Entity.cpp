#include "Entity.h"

Entity::Entity(RawModel model, glm::vec3 position, glm::vec3 rotation, float scale, std::string name)
	: model(model), position(position), rotation(rotation), scale(scale), name(name) {
}

RawModel& Entity::getModel() { return model; }
glm::vec3 Entity::getPosition() { return position; }
glm::vec3 Entity::getRotation() { return rotation; }
float Entity::getScale() { return scale; }
std::string Entity::getEntityName() { return name; }


void Entity::setPosition(glm::vec3 position) { this->position = position; }
void Entity::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Entity::setScale(float scale) { this->scale = scale; }
void Entity::setName(std::string name) { this->name = name; }
