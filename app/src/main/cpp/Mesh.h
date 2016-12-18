//
// Created by 宇 on 2016/12/15.
//

#ifndef ESVIRTUALTOUR_MESH_H
#define ESVIRTUALTOUR_MESH_H

#include <string>
#include <vector>
#include <sstream>

#include <assimp/types.h>

#include <glm/glm.hpp>
#include <GLES3/gl3.h>
#include "Shader.h"

using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture{
    GLuint id;
    string type;
    aiString path;
};

class Mesh{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
    void Draw(Shader shader);

private:
    GLuint VAO, VBO, EBO;
    void setupMesh();
};


#endif //ESVIRTUALTOUR_MESH_H
