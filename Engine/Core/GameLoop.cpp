#include "GameLoop.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void GameLoop::run(GLFWwindow* window, RawModel& model,
    glm::vec3 position, glm::vec3 rotation, float scale) {

    // ImGui initialize
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    shader.StartShader();
    shader.connectTextureUnits();
    shader.StopShader();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        renderer.prepare();
        shader.StartShader();

        glm::mat4 matrix = Math::createTransformationMatrix(position, rotation, scale);
        shader.loadTransformationMatrix(matrix);

        renderer.render(model);
        shader.StopShader();

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::SliderFloat3("Position", &position.x, -1.0f, 1.0f);
        ImGui::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat("Scale", &scale, 0.1f, 3.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // temizlik
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    shader.cleanUp();
}

void GameLoop::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}