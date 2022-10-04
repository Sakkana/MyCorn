#ifndef TRANSFORMTOIMAGE
#define TRANSFORMTOIMAGE
#define STB_IMAGE_IMPLEMENTATION

#define PI 3.141593
#define VERTEX_NUM 3
#define TEXTURE_VERTEX_NUM 3
#define INDEX_NUM 2

#define LOG_VARIABLE(info, x) std::cout<<"[ "<<info" ]  "<<x<<std::endl
#define LOG_TEXT(text) std::cout<<text<<std::endl

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader_m.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

const float INF = 999.0;

class TransformToImage
{
public:
	TransformToImage() = default;

	// TransformToImage(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	TransformToImage(std::vector<Mesh> meshed);

	void transform();
	
protected:
	void get_bounding_box();	// 获取包围盒参数
	void mapping();				// 实施二维映射

private:
	std::vector<Mesh>    m_meshes;
	// std::vector<Vertex>       vertices;  // 顶点数据
	// std::vector<unsigned int> indices;   // 用EBO做索引
	// std::vector<Texture>      textures;  // 用哪几张素材贴图
	std::vector<std::vector<float>> m_max_coord;
	std::vector<std::vector<float>> m_min_coord;
};

#endif