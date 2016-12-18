//
// Created by 宇 on 2016/12/16.
//

#ifndef ESVIRTUALTOUR_MODEL_H
#define ESVIRTUALTOUR_MODEL_H

#include <string>

#include <GLES3/gl3.h>
#include <assimp/scene.h>
#include "Shader.h"
#include "Mesh.h"

using namespace std;

GLuint TextureFromFile(const char* path, string directory);

class Model
{
public:
    Model(GLchar* path);
    void Draw(Shader shader);

private:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);

    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

};

#endif //ESVIRTUALTOUR_MODEL_H
