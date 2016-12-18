//
// Created by 宇 on 2016/12/16.
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <SOIL/SOIL.h>
#include "Model.h"

Model::Model(GLchar *path) {
    this->loadModel(path);
}

void Model::Draw(Shader shader) {
    for (GLuint i = 0; i<meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(string path) {
    Assimp::Importer import;

    LOGI(1, "Start Reading Model");
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//    scene = import.ApplyPostProcessing(aiProcess_GenNormals);
    LOGI(1, "Finish Reading Model %s", import.GetErrorString());


    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOGI(1, "%s", import.GetErrorString());
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    LOGI(1, "Directory: %s", directory.c_str());
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {

//    LOGI(1, "mNumMeshes : %d, mNumChildren: %d ", node->mNumMeshes, node->mNumChildren);

    for (GLuint i = 0; i<node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

//    LOGI(1, "%d %d %d", mesh->mNumVertices, mesh->mNumFaces, mesh->mMaterialIndex);

    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 v;
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;

        vertex.Position = v;

        glm::vec3 vv;
        vv.x = mesh->mNormals[i].x;
        vv.y = mesh->mNormals[i].y;
        vv.z = mesh->mNormals[i].z;

        vertex.Normal = vv;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 v2;
            v2.x = mesh->mTextureCoords[0][i].x;
            v2.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = v2;
        }else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

//    LOGI(1, "Finish Vertices");

    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
//    LOGI(1, "Finish Faces");

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

//    LOGI(1, "Finish Material");

    return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            string typeName) {
    vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean skip = false;

        for(GLuint j = 0; j < textures_loaded.size(); j++)
        {
            if (textures_loaded[i].path == str)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);

            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

GLuint TextureFromFile(const char*path, string directory)
{
    string filename = string(path);
    filename = directory + "/" + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    return textureID;
}


