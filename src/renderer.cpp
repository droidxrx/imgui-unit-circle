#include "renderer.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_freetype.h>
#include "NotoSansSemiBold.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Renderer::Renderer() {
    window   = nullptr;
    imWindow = nullptr;
    imFont   = nullptr;
    imIo     = nullptr;
    imStyle  = nullptr;
}

void Renderer::renderStart() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::renderEnd(int display_w, int display_h) {
    ImGui::Render();
    glViewport(0, 0, display_w, display_h);
    glClearColor(displayBg.x * displayBg.w, displayBg.y * displayBg.w, displayBg.z * displayBg.w, displayBg.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void Renderer::destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Renderer::initImGui() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return false;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(1280, 720, "ImGui Unit Circle", nullptr, nullptr);
    if (window == nullptr) return false;
    glfwSetWindowSizeLimits(window, 1280, 720, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    imIo    = &ImGui::GetIO();
    imStyle = &ImGui::GetStyle();
    ImFontConfig fontConfig;

    ImGui::StyleColorsDark();
    imIo->Fonts->FontBuilderIO = ImGuiFreeType::GetBuilderForFreeType();
    imIo->IniFilename = imIo->LogFilename = nullptr;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    fontConfig.FontDataOwnedByAtlas = false;
    fontConfig.OversampleH = fontConfig.OversampleV = 1;
    fontConfig.RasterizerMultiply                   = 1;

    imIo->FontDefault = imFont = imIo->Fonts->AddFontFromMemoryTTF(NotoSansSemiBold_data, NotoSansSemiBold_size, 16, &fontConfig, NotoSansSemiBold_ranges);

    imStyle->WindowRounding  = 0;
    imStyle->WindowMinSize   = { 400, 720 };
    imStyle->AntiAliasedFill = imStyle->AntiAliasedLines = true;
    imStyle->Colors[ImGuiCol_WindowBg]                   = { 0.06f, 0.06f, 0.06f, 1.0f };

    return true;
}

void Renderer::loopRender() {
    int display_w, display_h;

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        this->renderStart();

        if ((float)display_w != displaySize.x || (float)display_h != displaySize.y) {
            displaySize.x = (float)display_w;
            displaySize.y = (float)display_h;
            availableDisplay.Update(400, 0, displaySize.x, displaySize.y);
            ImGui::SetNextWindowPos({});
            ImGui::SetNextWindowSize({ availableDisplay.Min.x, displaySize.y });
            ImGui::SetNextWindowBgAlpha(1);
            c.update(availableDisplay.Center);
        }

        this->updateMousePos();
        this->drawUnitCircle(ImGui::GetBackgroundDrawList());
        this->drawWindow();
        this->renderEnd(display_w, display_h);
    }

    this->destroy();
}

void Renderer::updateMousePos() {
    if (!imIo->KeyCtrl) return;
    mousePos = imIo->MousePos;
}