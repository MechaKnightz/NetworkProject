#pragma once
#include <cstdint>
#include <glad\glad.h>
#include <iostream>
#include <stb_image.h>
#include "Component.h"
#include <assimp/scene.h>
#include "Mesh.h"

class ModelComponent : public Component
{
public:
    std::vector<Texture> LoadedTextures;
    std::vector<Mesh> Meshes;
    std::string Directory;

	ModelComponent(const std::string& path)
	{
        LoadModel(path);
	}

private:
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    uint32_t TextureFromFile(const std::string& uri, const std::string& directory);
};