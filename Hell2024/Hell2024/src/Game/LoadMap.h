//#pragma once
//
////#include <GL/glew.h>
//#include "HellCommon.hpp"
//#include <GLFW/glfw3.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//struct Vertex {
//    glm::vec3 Position;
//    glm::vec3 Normal;
//    glm::vec2 TexCoords;
//};
//
//class MapModel {
//public:
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    unsigned int VAO, VBO, EBO;
//
//    MapModel(const char* path) {
//        loadModel(path);
//        setupMesh();
//    }
//
//    void Draw(GLuint shaderProgram) {
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//    }
//
//private:
//    void loadModel(const char* path) {
//        Assimp::Importer importer;
//        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
//            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
//            return;
//        }
//        processNode(scene->mRootNode, scene);
//    }
//
//    void processNode(aiNode* node, const aiScene* scene) {
//        // Process all the node's meshes (if any)
//        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
//            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//            processMesh(mesh, scene);
//        }
//        // Then do the same for each of its children
//        for (unsigned int i = 0; i < node->mNumChildren; i++) {
//            processNode(node->mChildren[i], scene);
//        }
//    }
//
//    void processMesh(aiMesh* mesh, const aiScene* scene) {
//        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//            Vertex vertex;
//            // Process vertex positions, normals and texture coordinates
//            vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//            vertex.Normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//            if (mesh->mTextureCoords[0])
//                vertex.TexCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
//            else
//                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//            vertices.push_back(vertex);
//        }
//        // Process indices
//        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
//            aiFace face = mesh->mFaces[i];
//            for (unsigned int j = 0; j < face.mNumIndices; j++)
//                indices.push_back(face.mIndices[j]);
//        }
//    }
//
//    void setupMesh() {
//        glGenVertexArrays(1, &VAO);
//        glGenBuffers(1, &VBO);
//        glGenBuffers(1, &EBO);
//
//        glBindVertexArray(VAO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//
//        // Vertex Positions
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//        // Vertex Normals
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//        // Vertex Texture Coords
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//
//        glBindVertexArray(0);
//    }
//};
//
//// In your main function or game loop:
//MapModel map("path/to/your/map.obj");
//
//// In your render function:
//map.Draw(shaderProgram);
