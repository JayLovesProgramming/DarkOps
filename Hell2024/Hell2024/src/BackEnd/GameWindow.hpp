#pragma once

#include "BackEnd.hpp"

GLFWwindow* _window = NULL;

GLFWwindow* GetWindowPointer()
{
    return _window;
}