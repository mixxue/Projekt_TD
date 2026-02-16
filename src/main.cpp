#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"
#include "Map.h"
#include "Texture.h"

// Window size
int currentWidth = 800;
int currentHeight = 600;

// Handle window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

	currentWidth = width;
    currentHeight = height;
}

int main()
{
    // ===============================
    // Initialize GLFW
    // ===============================
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(currentWidth, currentHeight, "2D Renderer", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowAspectRatio(window, 16, 9);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ===============================
    // Load GLAD
    // ===============================
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, currentWidth, currentHeight);

    // Enable transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create renderer
    Renderer renderer(currentWidth, currentHeight);

    // Load texture
    
    // Create map
    Map gameMap("assets/maps/map1.txt", 32);

    // ===============================
    // Render loop
    // ===============================
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Get width and height of window after resize
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Update renderer's screen size
        renderer.setScreenSize(width, height);

        renderer.drawSquare(0.0f, 0.0f, (float)width, (float)height, 0.0f, 0.8f, 1.0f);

        gameMap.draw(renderer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}