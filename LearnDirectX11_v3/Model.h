#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "Camera.h"
class Model
{
public:
	float3 position;
	float3 rotationAngle;
	float3 scale = {1, 1, 1};
	Model(Graphics* graphics, char* modelPath);
	Model(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader);
	void draw(Graphics* graphics, Camera* camera);
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader);
	void processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader);
	Mesh processMesh(Graphics* graphics, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader);
};

