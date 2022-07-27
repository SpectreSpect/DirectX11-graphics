#include "Model.h"

Model::Model(Graphics* graphics, char* modelPath)
{
	loadModel(graphics, modelPath, new DefaultVertexShader(graphics, L"VertexShader.hlsl"), new PixelShader(graphics, L"PixelShader.hlsl"));
}

Model::Model(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader)
{
	loadModel(graphics, modelPath, vertexShader, pixelShader);
}

void Model::setTexture(Texture* texture, unsigned int slot)
{
	//textures[slot] = texture;
	textures.push_back(new TextureStruct{ texture, slot });
}

void Model::deleteTexture(unsigned int slot)
{
	//textures[slot] = nullptr;
}

std::vector<Texture*> Model::loadMaterialTextures(Graphics* graphics, aiMaterial* mat, aiTextureType type)
{
	std::vector<Texture*> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		//Convert char to wchar_t

		//rsize_t length = strlen(str.C_Str()) + 1;

		//char* t = (char*)directory.c_str();
		//char* inputStr = new char[10000];
		//memcpy((void*)inputStr, directory.c_str(), str.length);
		//strcat_s(inputStr, length, (const char*)str.C_Str());

		std::string path = directory + str.C_Str();

		size_t cSize = strlen(path.c_str()) + 1;
		if (cSize > 1)
			int point = 0;
		wchar_t* texFileNameWChar = new wchar_t[cSize];
		MultiByteToWideChar(0, 0, path.c_str(), cSize, texFileNameWChar, cSize);
		//Convert char to wchar_t

		Texture* texture = new Texture(graphics, texFileNameWChar);
		textures.push_back(texture);

		delete[cSize] texFileNameWChar;
	}
	return textures;
}

void Model::draw(Graphics* graphics, Camera* camera)
{
	//for (int i = 0; i < maxTexturesCount; i++)
	//	if (textures[i])
	//		textures[i]->bind(i);

	for (int i = 0; i < textures.size(); i++)
		textures[i]->texture->bind(textures[i]->slot);

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].position = position;
		meshes[i].rotationAngle = rotationAngle;
		meshes[i].scale = scale;
		meshes[i].drawDepthStencil = drawDepthStencil;
		meshes[i].draw(graphics, camera);
	}
}

void Model::loadModel(Graphics* graphics, std::string path, VertexShader* vertexShader, PixelShader* pixelShader)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw;
	//cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
	directory = path.substr(0, path.find_last_of('\\')) + "\\";
	processNode(graphics, scene->mRootNode, scene, vertexShader, pixelShader);
}

void Model::processNode(Graphics* graphics, aiNode* node, const aiScene* scene, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];









		meshes.push_back(processMesh(graphics, scene, mesh, vertexShader, pixelShader));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		if (i == 101)
			int k = 0;
		processNode(graphics, node->mChildren[i], scene, vertexShader, pixelShader);
	}
}

Mesh Model::processMesh(Graphics* graphics, const aiScene* scene, aiMesh* mesh, VertexShader* vertexShader, PixelShader* pixelShader)
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
	

	Mesh outputMesh = Mesh(graphics, vertices, indices, vertexShader, pixelShader);



	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		//aiString texFileName;
		//material->GetTexture(aiTextureType_NORMALS, 0, &texFileName);

		// Convert char into wchar_t
		//const char* t = texFileName.C_Str();
		//size_t cSize = strlen(texFileName.C_Str()) + 1;
		//if (cSize > 1)
		//	int point = 0;
		//wchar_t* texFileNameWChar = new wchar_t[cSize];
		//MultiByteToWideChar(0, 0, texFileName.C_Str(), cSize, texFileNameWChar, cSize);
		// Convert char into wchar_t
		//outputMesh.textures[0] = new Texture(graphics, texFileNameWChar);

		std::vector<Texture*> texturesDiffuse = loadMaterialTextures(graphics, material, aiTextureType_DIFFUSE);
		//std::vector<Texture*> texturesNormal = loadMaterialTextures(graphics, material, aiTextureType_NORMALS);
		//std::vector<Texture*> texturesRoughness = loadMaterialTextures(graphics, material, aiTextureType_DIFFUSE_ROUGHNESS);
		std::vector<Texture*> texturesBaseColor = loadMaterialTextures(graphics, material, aiTextureType_BASE_COLOR);
		//std::vector<Texture*> texturesNormals2 = loadMaterialTextures(graphics, material, aiTextureType_AMBIENT);

		if (texturesDiffuse.size() > 0)
			outputMesh.textures[0] = texturesDiffuse[0];

		//if (texturesRoughness.size() > 0)
		//	int k = 0;

		if (texturesBaseColor.size() > 0)
			outputMesh.textures[0] = texturesBaseColor[0];



		//std::vector<Texture*> texturesDiffuse2 = loadMaterialTextures(graphics, material, aiTextureType_DIFFUSE);

		//if (texturesNormal.size() > 0)
		//	outputMesh.textures[1] = texturesNormal[0];

		//if (texturesNormals2.size() > 0)
		//	outputMesh.textures[1] = texturesNormals2[0];



		//int countAMBIENT = material->GetTextureCount(aiTextureType_AMBIENT);
		//int countAMBIENT_OCCLUSION = material->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);
		//int countBASE_COLOR = material->GetTextureCount(aiTextureType_BASE_COLOR);
		//int countCLEARCOAT = material->GetTextureCount(aiTextureType_CLEARCOAT);
		//int countDIFFUSE = material->GetTextureCount(aiTextureType_DIFFUSE);
		//int countDIFFUSE_ROUGHNESS = material->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS);
		//int countDISPLACEMENT = material->GetTextureCount(aiTextureType_DISPLACEMENT);
		//int countEMISSION_COLOR = material->GetTextureCount(aiTextureType_EMISSION_COLOR);
		//int countEMISSIVE = material->GetTextureCount(aiTextureType_EMISSIVE);
		//int countHEIGHT = material->GetTextureCount(aiTextureType_HEIGHT);
		//int countLIGHTMAP = material->GetTextureCount(aiTextureType_LIGHTMAP);
		//int countMETALNESS = material->GetTextureCount(aiTextureType_METALNESS);
		//int countNONE = material->GetTextureCount(aiTextureType_NONE);
		//int countNORMALS = material->GetTextureCount(aiTextureType_NORMALS);
		//int countNORMAL_CAMERA = material->GetTextureCount(aiTextureType_NORMAL_CAMERA);
		//int countOPACITY = material->GetTextureCount(aiTextureType_OPACITY);
		//int countREFLECTION = material->GetTextureCount(aiTextureType_REFLECTION);
		//int countSHEEN = material->GetTextureCount(aiTextureType_SHEEN);
		//int countSHININESS = material->GetTextureCount(aiTextureType_SHININESS);
		//int countSPECULAR = material->GetTextureCount(aiTextureType_SPECULAR);
		//int countTRANSMISSION = material->GetTextureCount(aiTextureType_TRANSMISSION);
		//int countUNKNOWN = material->GetTextureCount(aiTextureType_UNKNOWN);
		//int countForce32Bit = material->GetTextureCount(_aiTextureType_Force32Bit);

		//if (countAMBIENT > 0 || countAMBIENT_OCCLUSION > 0 || countBASE_COLOR > 0 || countCLEARCOAT > 0 || countDIFFUSE > 0 || countDIFFUSE_ROUGHNESS > 0 || countDISPLACEMENT > 0 || countEMISSION_COLOR > 0 || countEMISSIVE > 0 || countHEIGHT > 0 || countLIGHTMAP > 0 || countMETALNESS > 0 || countNONE > 0 || countNORMALS > 0 || countNORMAL_CAMERA > 0 || countOPACITY > 0 || countREFLECTION > 0 || countSHEEN > 0 || countSHININESS > 0 || countSPECULAR > 0 || countTRANSMISSION > 0 || countUNKNOWN > 0 || countForce32Bit > 0)
		//{
		//	int k = 0;
		//}


	}

	return outputMesh;
}
