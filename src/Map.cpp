#include "Map.h"
#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <iostream>

// ===============================
// Constructor
// ===============================
Map::Map(const std::string& filename, int tileSize)
    : tileSize(tileSize)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Failed to open map file: " << filename << std::endl;
        rows = 0;
        cols = 0;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;

        while (ss >> value)
        {
            row.push_back(value);
        }

        if (!row.empty())
            grid.push_back(row);
    }

    rows = grid.size();
    cols = (rows > 0) ? grid[0].size() : 0;

    file.close();

    std::cout << "Map loaded: "
              << rows << " rows, "
              << cols << " cols\n";
}

// ===============================
// Draw (Centered Version)
// ===============================
void Map::draw(Renderer& renderer)
{
    if (rows == 0 || cols == 0)
        return;

    // Calculate total map size in pixels
    float mapWidth  = cols * tileSize;
    float mapHeight = rows * tileSize;

    // Get screen size from renderer
    float screenWidth  = renderer.getScreenWidth();
    float screenHeight = renderer.getScreenHeight();

    // Calculate center offset
    float offsetX = (screenWidth  - mapWidth)  / 2.0f;
    float offsetY = (screenHeight - mapHeight) / 2.0f;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            float x = offsetX + col * tileSize;
            float y = offsetY + row * tileSize;

            int tile = grid[row][col];

            // Basic color mapping
            switch (tile)
            {
                case 0: // grass
                    renderer.drawSquare(x, y, tileSize, tileSize,
                                        0.2f, 0.8f, 0.2f);
                    break;

                case 1: // path
                    renderer.drawSquare(x, y, tileSize, tileSize,
                                        0.6f, 0.4f, 0.2f);
                    break;

                case 2: // wall
                    renderer.drawSquare(x, y, tileSize, tileSize,
                                        0.3f, 0.3f, 0.3f);
                    break;

                case 3: // spawn
                    renderer.drawSquare(x, y, tileSize, tileSize,
                                        1.0f, 0.0f, 0.0f);
                    break;

                default:
                    renderer.drawSquare(x, y, tileSize, tileSize,
                                        1.0f, 0.0f, 1.0f);
                    break;
            }
        }
    }
}

// ===============================
// Getters
// ===============================
int Map::getRows() const
{
    return rows;
}

int Map::getCols() const
{
    return cols;
}

int Map::getTileSize() const
{
    return tileSize;
}