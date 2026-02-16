#pragma once

#include <vector>
#include <string>

class Renderer; // forward declaration

class Map
{
private:
    std::vector<std::vector<int>> grid;

    int rows;
    int cols;
    int tileSize;

public:
    // Constructor: load map from file
    Map(const std::string& filename, int tileSize);

    // Draw map centered
    void draw(Renderer& renderer);

    // Optional getters (useful later)
    int getRows() const;
    int getCols() const;
    int getTileSize() const;
};