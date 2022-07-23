#include "Model.h"

Model::Model(Graphics* graphics, char* modelPath)
{
	loadModel(graphics, modelPath, new DefaultVertexShader(graphics, L"VertexShader.hlsl"), new PixelShader(graphics, L"PixelShader.hlsl"));
}

Model::Model(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader)
{
	loadModel(graphics, modelPath, vertexShader, pixelShader);
}

void Model::draw(Graphics* graphics, Camera* camera)
{
	int pointk = 0;
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].position = position;
		meshes[i].rotationAngle = rotationAngle;
		meshes[i].scale = scale;
		meshes[i].draw(graphics, camera);
	}

}

void Model::loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw;
	//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
	directory = path.substr(0, path.find_last_of('/'));
	processNode(graphics, scene->mRootNode, scene, vertexShader, pixelShader);
}

void Model::processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(graphics, mesh, vertexShader, pixelShader));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(graphics, node->mChildren[i], scene, vertexShader, pixelShader);
	}
}

Mesh Model::processMesh(Graphics* graphics, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex{};
		vertex.pos.x = mesh->mVertices[i].x;
		vertex.pos.y = mesh->mVertices[i].y;
		vertex.pos.z = mesh->mVertices[i].z;

		if (mesh->mNormals)
		{
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTangents)
		{
			vertex.tangent.x = mesh->mTangents[i].x;
			vertex.tangent.y = mesh->mTangents[i].y;
			vertex.tangent.z = mesh->mTangents[i].z;
		}
		if (mesh->mBitangents)
		{
			vertex.bitangent.x = mesh->mBitangents[i].x;
			vertex.bitangent.y = mesh->mBitangents[i].y;
			vertex.bitangent.z = mesh->mBitangents[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		vertices.push_back(vertex);
	}
	
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	return Mesh(graphics, vertices, indices, vertexShader, pixelShader);
}
