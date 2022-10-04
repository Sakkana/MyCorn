#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader_m.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    int m_BoneIDs[MAX_BONE_INFLUENCE];      //bone indexes which will influence this vertex
    float m_Weights[MAX_BONE_INFLUENCE];    //weights from each bone
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // 网格数据
    std::vector<Vertex>       vertices;  // 顶点数据
    std::vector<unsigned int> indices;   // 用EBO做索引
    std::vector<Texture>      textures;  // 用哪几张素材贴图

    Mesh() = default;

    Mesh(std::vector<Vertex> vertices,  std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader& shader);  // 渲染所有网格

    std::vector<Vertex> get_vertices();
    std::vector<unsigned int> get_indices();
    std::vector<Texture> get_textures();

protected:
    void setupMesh();   // 设置所有缓冲对象/数组, 在构造函数里调用

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

#endif
