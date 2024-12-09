#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "BackEnd/BackEnd.hpp"

//// Function to load texture
//GLuint loadTexture() 
//{
//    int width, height, channels;
//    unsigned char* data = stbi_load("E:/Hell2024/Hell2024/Hell2024/res/rounds/round1.png", &width, &height, &channels, 0);
//
//    if (!data) 
//    {
//        std::cerr << "Failed to load texture: " << std::endl;
//        return 0;
//    }
//
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//
//    // Set texture parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    // Load texture into OpenGL
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
//    glGenerateMipmap(GL_TEXTURE_2D);
//
//    stbi_image_free(data);
//
//    if (!texture) return -1;
//
//    return texture;
//}
//
//void drawImage (GLuint* texture) 
//{
//    // Bind texture
//    glBindTexture(GL_TEXTURE_2D, *texture);
//}
//
//GLuint roundTexture;
