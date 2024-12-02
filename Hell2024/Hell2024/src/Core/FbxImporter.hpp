#pragma once

#include "HellCommon.hpp"
#include "../Renderer/Types/SkinnedModel.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

namespace FbxImporter 
{
    void LoadAnimation(Animation* animation);
};