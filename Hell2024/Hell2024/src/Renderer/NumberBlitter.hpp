#pragma once

#include "Enums.hpp"

namespace NumberBlitter 
{
	enum class Justification {LEFT, RIGHT};
	void Draw(const char* text, int xScreenCoord, int yScreenCoord, int renderWidth, int renderHeight, float scale, Justification alignment);
};
