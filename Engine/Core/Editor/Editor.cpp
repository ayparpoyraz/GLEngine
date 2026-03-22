#include "Editor.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <filesystem>
#include <iostream>

void Editor::applyEditorTheme() {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Resource/fonts/Roboto-Regular.ttf", 15.0f);
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


    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.03f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.40f, 0.05f, 0.05f, 1.00f);


    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);


    style.Colors[ImGuiCol_Header] = ImVec4(0.35f, 0.05f, 0.05f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.50f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.65f, 0.10f, 0.10f, 1.00f);

    style.Colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.05f, 0.05f, 1.00f);
    style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.70f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.15f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.03f, 0.03f, 1.00f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.35f, 0.05f, 0.05f, 1.00f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.04f, 0.04f, 1.00f);
}

void Editor::scanResources() {
    modelFiles.clear();
    textureFiles.clear();

    if (std::filesystem::exists("Resource/OBJs/")) {
        for (auto& entry : std::filesystem::directory_iterator("Resource/OBJs/"))
            if (entry.path().extension() == ".obj")
                modelFiles.push_back(entry.path().filename().string());
    }

    if (std::filesystem::exists("Resource/Textures/")) {
        for (auto& entry : std::filesystem::directory_iterator("Resource/Textures/"))
            if (entry.path().extension() == ".png" || entry.path().extension() == ".jpg")
                textureFiles.push_back(entry.path().filename().string());
    }
}

bool Editor::run(GLFWwindow* window, std::vector<Entity>& entities) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    applyEditorTheme();

    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    glm::mat4 projection = glm::perspective(
        glm::radians(70.0f),
        (float)screenWidth / (float)screenHeight,
        0.1f,
        1000.0f
    );

    shader.StartShader();
    shader.loadProjectionMatrix(projection);
    shader.connectTextureUnits();
    shader.StopShader();

    // skybox init
    Skybox skybox;
    skybox.init();

    float lastFrame = 0.0f;
    int selectedEntity = 0;
    bool autoRotate = false;
    bool isStarted = false;
    bool isMenuVisible = true;
    bool showAddEntityPopup = false;
    int selectedModelIdx = 0;
    int selectedTextureIdx = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwGetWindowSize(window, &screenWidth, &screenHeight);

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

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

        camera.updateInput(window, deltaTime,
            getMouseXOffset(), getMouseYOffset(), getScrollOffset());

        resetMouseOffset();
        resetScrollOffset();

        renderer.prepare();

        // 1. entity'ler
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

        // 2. skybox en son
        skybox.render(camera.getViewMatrix(), projection);

        // ImGui
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
                    if (ImGui::MenuItem("Entity")) {
                        scanResources();
                        showAddEntityPopup = true;
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("View")) {
                    if (ImGui::MenuItem("Wireframe", nullptr, wireframe)) {
                        wireframe = !wireframe;
                        renderer.setWireframe(wireframe);
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Camera")) {
                    if (ImGui::MenuItem("Free Camera", nullptr, currentMode == CameraMode::Free))
                        currentMode = CameraMode::Free;
                    if (ImGui::MenuItem("Orbit Camera", nullptr, currentMode == CameraMode::Orbit))
                        currentMode = CameraMode::Orbit;
                    ImGui::EndMenu();
                }

                //float buttonWidth = 70.0f;
                //float windowWidth = ImGui::GetWindowWidth();
                //ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

                //ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                //if (isStarted) {
                //    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.0f));
                //    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
                //}
                //else {
                //    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.4f, 0.1f, 1.0f));
                //    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
                //}
                //if (ImGui::Button(isStarted ? " Stop " : " Start ")) {
                //    isStarted = !isStarted;
                //    if (isStarted)
                //        glfwSetWindowShouldClose(window, true);
                //}
                //ImGui::PopStyleColor(3);

                ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 120);
                ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
                ImGui::EndMainMenuBar();
            }

            if (showAddEntityPopup)
                ImGui::OpenPopup("Add Entity");

            if (ImGui::BeginPopupModal("Add Entity", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Select Model:");
                ImGui::Separator();
                ImGui::BeginChild("ModelList", ImVec2(300, 150), true);
                for (int i = 0; i < (int)modelFiles.size(); i++) {
                    if (ImGui::Selectable(modelFiles[i].c_str(), selectedModelIdx == i))
                        selectedModelIdx = i;
                }
                ImGui::EndChild();

                ImGui::Spacing();
                ImGui::Text("Select Texture:");
                ImGui::Separator();
                ImGui::BeginChild("TextureList", ImVec2(300, 150), true);
                for (int i = 0; i < (int)textureFiles.size(); i++) {
                    if (ImGui::Selectable(textureFiles[i].c_str(), selectedTextureIdx == i))
                        selectedTextureIdx = i;
                }
                ImGui::EndChild();

                ImGui::Spacing();
                ImGui::Separator();

                if (ImGui::Button("Add", ImVec2(140, 0))) {
                    if (!modelFiles.empty() && !textureFiles.empty()) {
                        std::string modelName = modelFiles[selectedModelIdx];
                        modelName = modelName.substr(0, modelName.find_last_of('.'));
                        std::string texName = textureFiles[selectedTextureIdx];
                        texName = texName.substr(0, texName.find_last_of('.'));
                        Texture tex(texName);
                        RawModel newModel = OBJLoader::loadOBJ(modelName, loader, tex);
                        entities.push_back(Entity(newModel,
                            glm::vec3(0.0f, 0.0f, -3.0f),
                            glm::vec3(0.0f), 1.0f, modelName));
                        selectedEntity = (int)entities.size() - 1;
                    }
                    showAddEntityPopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(140, 0))) {
                    showAddEntityPopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }

            ImGui::SetNextWindowPos(ImVec2(0, 20));
            ImGui::SetNextWindowSize(ImVec2(200, screenHeight - 20));
            ImGui::Begin("Scene Entities", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::Checkbox("Auto Rotate", &autoRotate);
            ImGui::Separator();
            for (int i = 0; i < (int)entities.size(); i++) {
                if (ImGui::Selectable(entities[i].getEntityName().c_str(), selectedEntity == i))
                    selectedEntity = i;
            }
            ImGui::Separator();
            if (ImGui::Button("+ Add Entity", ImVec2(-1, 0))) {
                scanResources();
                showAddEntityPopup = true;
            }
            if (!entities.empty()) {
                if (ImGui::Button("- Remove Entity", ImVec2(-1, 0))) {
                    entities.erase(entities.begin() + selectedEntity);
                    if (selectedEntity >= (int)entities.size())
                        selectedEntity = (int)entities.size() - 1;
                }
            }
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(screenWidth - 210, 20));
            ImGui::SetNextWindowSize(ImVec2(210, screenHeight - 25));
            ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            if (!entities.empty() && selectedEntity < (int)entities.size()) {
                char nameBuf[64];
                strncpy_s(nameBuf, entities[selectedEntity].getEntityName().c_str(), sizeof(nameBuf));
                if (ImGui::InputText("##name", nameBuf, sizeof(nameBuf)))
                    entities[selectedEntity].setName(nameBuf);
                ImGui::Separator();
                if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
                    glm::vec3 pos = entities[selectedEntity].getPosition();
                    glm::vec3 rot = entities[selectedEntity].getRotation();
                    float scale = entities[selectedEntity].getScale();
                    if (ImGui::DragFloat3("Position", &pos.x, 0.01f))
                        entities[selectedEntity].setPosition(pos);
                    if (ImGui::DragFloat3("Rotation", &rot.x, 0.5f))
                        entities[selectedEntity].setRotation(rot);
                    if (ImGui::DragFloat("Scale", &scale, 0.01f, 0.1f, 10.0f))
                        entities[selectedEntity].setScale(scale);
                }
                if (ImGui::CollapsingHeader("Camera")) {
                    glm::vec3 camPos = camera.getPosition();
                    ImGui::Text("Pos: %.1f %.1f %.1f", camPos.x, camPos.y, camPos.z);
                    if (ImGui::DragFloat3("Position##cam", &camPos.x, 0.02f))
                        camera.setPosition(camPos);
                }
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    skybox.cleanUp();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    shader.cleanUp();

    return isStarted;
}