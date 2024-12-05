//#pragma once
//
//#include "BackEnd.hpp"
//
//void InitWindowHints()
//{
//    if (BackEnd::GetAPI() == API::OPENGL)
//    {
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
//    }
//    else if (BackEnd::GetAPI() == API::VULKAN)
//    {
//        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
//    }
//}