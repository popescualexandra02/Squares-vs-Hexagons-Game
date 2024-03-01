#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 3, 
                                          3, 1, 2};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateDreptunghi(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* dreptunghi = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        dreptunghi->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    dreptunghi->InitFromData(vertices, indices);
    return dreptunghi;
}


Mesh* object2D::CreateSoldier(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, width, 1), color),
        VertexFormat(corner + glm::vec3(0, 2 * width, 1), color),
        VertexFormat(corner + glm::vec3(-length, width, 1), color),
        VertexFormat(corner + glm::vec3(length / 2, 3 * width / 4, 1), color), // 4
        VertexFormat(corner + glm::vec3(2 * length, 3 * width / 4, 1), color), // 5
        VertexFormat(corner + glm::vec3(2 * length, 5 * width / 4, 1), color), // 6
        VertexFormat(corner + glm::vec3(length / 2, 5 * width / 4, 1), color) // 7

    };

    Mesh* dreptunghi = new Mesh(name);
    std::vector<unsigned int> indices = { 3, 0 , 1,
                                          3, 1, 2,
                                          4, 5, 6,
                                          4, 6, 7};

    if (!fill) {
        dreptunghi->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    dreptunghi->InitFromData(vertices, indices);
    return dreptunghi;
}

Mesh* object2D::CreateDanger(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    glm::vec3 middle = corner + glm::vec3(0, 0.355f * length, 0);
    glm::vec3 smallMiddle = middle + glm::vec3(0, 0, 1);


    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, length / 2, 1), color), // 1 
        VertexFormat(corner + glm::vec3(length, 3 * length / 2, 1), color), //2
        VertexFormat(corner + glm::vec3( 0,  2 * length, 0), color), // 3
        VertexFormat(corner + glm::vec3(- length,  3 * length / 2, 1), color), // 4
        VertexFormat(corner + glm::vec3(-length,  length / 2, 1), color), // 5
        VertexFormat(corner + glm::vec3(0,  length / 2, 1), color), // 6
        
        VertexFormat(smallMiddle, color2), // 7
        VertexFormat(smallMiddle + glm::vec3(0.6f * length,0.6f * (length / 2), 2), color2), // 8
        VertexFormat(smallMiddle + glm::vec3(0.6f * length,0.6f * (3 * length / 2), 2), color2), //9
        VertexFormat(smallMiddle + glm::vec3(0,  0.6f *  2 * length, 2), color2), // 10
        VertexFormat(smallMiddle + glm::vec3(-length * 0.6f ,  0.6f *  (3 * length / 2), 2), color2), // 11
        VertexFormat(smallMiddle + glm::vec3(-length * 0.6f ,  0.6f * length / 2, 2), color2), // 12
        VertexFormat(smallMiddle + glm::vec3(0,  0.6f * (length / 2), 2), color2) // 13

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1 , 6,
                                          6, 1, 2,
                                          6, 2, 3,
                                          6, 3, 4,
                                          6, 4, 5,
                                          6, 5, 0,

                                            7, 8, 13,
                                            13, 8, 9,
                                            13, 9, 10,
                                            13, 10, 11,
                                            13, 11, 12,
                                            13, 12, 7};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0,  - 3 * length / 4, 4), color), // 1
        VertexFormat(corner + glm::vec3(length / 2, - length / 3, 4), color), // 2
        VertexFormat(corner + glm::vec3(- length / 2, -length / 3, 4), color), // 3
        VertexFormat(corner + glm::vec3(-length / 3, -length , 4), color), // 4
        VertexFormat(corner + glm::vec3(length / 3, -length , 4), color), // 5

        
        
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {1, 2, 3,
                                         1, 0, 4,
                                         1, 5, 0};
                        

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateSquareEmpty(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* square = new Mesh(name);
    square->SetDrawMode(GL_LINE_LOOP);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    

    square->InitFromData(vertices, indices);
    return square;
}

