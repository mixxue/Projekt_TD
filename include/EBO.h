#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif

// Renderer.h
#pragma once

#include <glad/glad.h>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Class responsible for converting pixel coordinates to NDC and issuing draw
// commands.  Stores current screen size so it can handle window resizing.
class Renderer
{
private:
    Shader* shader;   // pointer to shader program (owns the program)
    VAO vao;          // a VAO reused for all quads

    int screenWidth;  // current framebuffer width
    int screenHeight; // current framebuffer height

public:
    Renderer(int width, int height);

    void setScreenSize(int width, int height);

    int getScreenWidth() const;
    int getScreenHeight() const;

    // Draws a quad at pixel position (x,y) with given dimensions and color.
    // Optional textureID binds a texture instead of solid color.
    void drawSquare(float x, float y,
                    float width, float height,
                    float r, float g, float b,
                    GLuint textureID = 0);
};