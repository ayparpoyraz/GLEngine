#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../models/RawModel.h"




class Renderer {
public:
    void prepare();
    void setWireframe(bool enable);
    void render(RawModel& model);
};