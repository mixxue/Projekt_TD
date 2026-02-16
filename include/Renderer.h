#pragma once

#include <glad/glad.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Renderer
{
private:
    Shader* shader;
    VAO vao;

    int screenWidth;
    int screenHeight;

public:
    Renderer(int width, int height);

    void setScreenSize(int width, int height);

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawSquare(float x, float y,
                    float width, float height,
                    float r, float g, float b,
                    GLuint textureID = 0);
};