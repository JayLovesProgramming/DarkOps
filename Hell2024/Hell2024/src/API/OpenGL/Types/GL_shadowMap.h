#pragma once

#include "HellCommon.hpp"
#include <vector>

struct ShadowMap
{
	void Init(); 
	void CleanUp();
	void Clear();

    unsigned int m_ID = 0;
    unsigned int m_depthTexture = 0;
};
