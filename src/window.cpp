#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <stdio.h>

#include <iostream>
#include <vector>

#include "print.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
double clockToMilliseconds(clock_t ticks)
{
    return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

GLFWwindow* init(int width, int height)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        throw "Failed to init glfw\n";

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(width, height, "Shellular Automata", NULL, NULL);
    if (window == NULL)
        throw "Failed to create window\n";
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // Enable vsync

    if (glewInit() != GLEW_OK)
        throw "Failed to init glew\n";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char *glsl_version = "#version 460";
    ImGui_ImplOpenGL3_Init(glsl_version);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(GLDebugMessageCallback, 0);

    return window;
}

int main()
{
    GLFWwindow* window = init(1024, 512); 

    clock_t deltaTime = 0;
    unsigned int frames = 0;
    double frameRate = 30;
    double averageFrameTimeMilliseconds = 33.333;

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    clock_t beginFrame = clock();
    clock_t endFrame = clock();
    clock_t renderTime = clock();
    while (!glfwWindowShouldClose(window))
    {
        endFrame = clock();
        deltaTime += endFrame - beginFrame;
        frames++;
        beginFrame = clock();

        if (clockToMilliseconds(deltaTime) > 1000.0)
        {                                                       // every second
            frameRate = (double)frames * 0.5 + frameRate * 0.5; // more stable
            frames = 0;
            deltaTime -= CLOCKS_PER_SEC;
            averageFrameTimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);

            std::cout << "FrameTime was:" << frameRate << std::endl;
        }
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // DO STUFF

        ImGui::ShowDemoWindow();

        ImGui::Render();

        clock_t currentTime = clock();
        if (clockToMilliseconds(currentTime - renderTime) > 1000.0 / 60.0) {
            renderTime = clock();
            // Rendering
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
