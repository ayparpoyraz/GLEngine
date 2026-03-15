#include "Editor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void Editor::applyEditorTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.ScrollbarRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.ItemSpacing = ImVec2(8, 6);
    style.WindowPadding = ImVec2(10, 10);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
}

void Editor::run(GLFWwindow* window, std::vector<Entity>& entities, RawModel& defaultModel) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    applyEditorTheme();

    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        1200.0f / 800.0f,
        0.1f,
        1000.0f
    );

    shader.StartShader();
    shader.loadProjectionMatrix(projection);
    shader.connectTextureUnits();
    shader.StopShader();

    float rotation = 0.0f;
    float lastFrame = 0.0f;
    int selectedEntity = 0;
    bool autoRotate = true;
    bool isStarted = false;
    bool isMenuVisible = true;

    while (!glfwWindowShouldClose(window)) {
        int screenWidth, screenHeight;
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);
            
        static bool insertPressed = false;
        if (glfwGetKey(window, GLFW_KEY_INSERT) == GLFW_PRESS) {
            if (!insertPressed) {
                isMenuVisible = !isMenuVisible;
                insertPressed = true;
            }
        }
        else {
            insertPressed = false;
        }

        processInput(window);
        camera.processKeyboard(window, deltaTime);

        if (autoRotate) rotation += 0.5f;

        renderer.prepare();
        shader.StartShader();
        shader.loadViewMatrix(camera.getViewMatrix());

        for (Entity& entity : entities) {
            glm::mat4 matrix = Math::createTransformationMatrix(
                entity.getPosition(),
                entity.getRotation(),
                entity.getScale()
            );
            shader.loadTransformationMatrix(matrix);
            renderer.render(entity.getModel());
        }

        shader.StopShader();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (isMenuVisible) {

            
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    ImGui::MenuItem("New Scene");
                    ImGui::MenuItem("Save Scene");
                    ImGui::Separator();
                    if (ImGui::MenuItem("Exit"))
                        glfwSetWindowShouldClose(window, true);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Add")) {
                    if (ImGui::MenuItem("Entity"))
                        entities.push_back(Entity(defaultModel, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f));
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("View")) {
                    ImGui::MenuItem("Wireframe");
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Camera")) {
                    if (ImGui::MenuItem("Free Camera", nullptr, currentMode == CameraMode::Free))
                        currentMode = CameraMode::Free;
                    if (ImGui::MenuItem("FPS Camera", nullptr, currentMode == CameraMode::FPS))
                        currentMode = CameraMode::FPS;
                    if (ImGui::MenuItem("Orbit Camera", nullptr, currentMode == CameraMode::Orbit))
                        currentMode = CameraMode::Orbit;
                    ImGui::EndMenu();
                }

      
                float buttonWidth = 70.0f;
                float windowWidth = ImGui::GetWindowWidth();
                ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                if (isStarted) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.4f, 0.1f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
                }
                if (ImGui::Button(isStarted ? " Stop " : " Derle "))
                    isStarted = !isStarted;
                ImGui::PopStyleColor(3);

                ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 120);
                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
                ImGui::EndMainMenuBar();
            }

            // Sol panel
            ImGui::SetNextWindowPos(ImVec2(0, 20));
            ImGui::SetNextWindowSize(ImVec2(200, screenHeight - 20));
            ImGui::Begin("Scene Entities", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::Checkbox("Auto Rotate", &autoRotate);
            ImGui::Separator();
            for (int i = 0; i < (int)entities.size(); i++) {
                char label[32];
                sprintf_s(label, "Entity %d", i);
                if (ImGui::Selectable(label, selectedEntity == i))
                    selectedEntity = i;
            }
            ImGui::Separator();
            if (ImGui::Button("+ Add Entity", ImVec2(-1, 0)))
                entities.push_back(Entity(defaultModel, glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), 1.0f));
            if (!entities.empty()) {
                if (ImGui::Button("- Remove Entity", ImVec2(-1, 0))) {
                    entities.erase(entities.begin() + selectedEntity);
                    if (selectedEntity >= (int)entities.size())
                        selectedEntity = (int)entities.size() - 1;
                }
            }
            ImGui::End();

            //Entity Transform
            ImGui::SetNextWindowPos(ImVec2(screenWidth - 200, 20));
            ImGui::SetNextWindowSize(ImVec2(200, screenHeight - 20));
            ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            if (!entities.empty()) {
                ImGui::Text("Entity %d", selectedEntity);
                ImGui::Separator();
                ImGui::Text("Transform");
                ImGui::Spacing();
                glm::vec3 pos = entities[selectedEntity].getPosition();
                glm::vec3 rot = entities[selectedEntity].getRotation();
                float scale = entities[selectedEntity].getScale();
                if (ImGui::DragFloat3("Position", &pos.x, 0.01f))
                    entities[selectedEntity].setPosition(pos);
                if (ImGui::DragFloat3("Rotation", &rot.x, 0.5f))
                    entities[selectedEntity].setRotation(rot);
                if (ImGui::DragFloat("Scale", &scale, 0.01f, 0.1f, 10.0f))
                    entities[selectedEntity].setScale(scale);
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Text("Camera");
                ImGui::Spacing();
                glm::vec3 camPos = camera.getPosition();
                ImGui::Text("Pos: %.1f %.1f %.1f", camPos.x, camPos.y, camPos.z);
            }
            ImGui::End();

        } 

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    shader.cleanUp();
}

void Editor::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}