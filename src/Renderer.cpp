#include "Renderer.h"
#include <iostream>

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height)
{
    shader = new Shader("assets/shaders/default.vert",
                        "assets/shaders/default.frag");

    shader->Activate();

    // Set texture unit once
    glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
}

void Renderer::setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

int Renderer::getScreenWidth() const
{
    return screenWidth;
}

int Renderer::getScreenHeight() const
{
    return screenHeight;
}

void Renderer::drawSquare(float x, float y,
                          float width, float height,
                          float r, float g, float b,
                          GLuint textureID)
{
    shader->Activate();

    // Convert pixel coords → NDC
    float left   =  (x / screenWidth) * 2.0f - 1.0f;
    float right  = ((x + width) / screenWidth) * 2.0f - 1.0f;
    float top    = 1.0f - (y / screenHeight) * 2.0f;
    float bottom = 1.0f - ((y + height) / screenHeight) * 2.0f;

    float vertices[] =
    {
        // positions        // tex coords
        left,  top,    0.0f,  0.0f, 1.0f,
        left,  bottom, 0.0f,  0.0f, 0.0f,
        right, bottom, 0.0f,  1.0f, 0.0f,
        right, top,    0.0f,  1.0f, 1.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    glUniform3f(glGetUniformLocation(shader->ID, "uColor"), r, g, b);

    if (textureID != 0)
    {
        glUniform1i(glGetUniformLocation(shader->ID, "useTexture"), 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    else
    {
        glUniform1i(glGetUniformLocation(shader->ID, "useTexture"), 0);
    }

    vao.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}