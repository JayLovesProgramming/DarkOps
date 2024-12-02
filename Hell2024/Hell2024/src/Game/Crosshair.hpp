#pragma once

#include "Utils/Util.hpp"
#include "HellCommon.hpp"
#include "../Renderer/RendererUtil.hpp"
#include "Player.hpp"
#include "../Renderer/Renderer.hpp"

class CrosshairManager
{
public:

	static float CrosshairShrink(float currentSize, float deltaTime)
	{
        const float shrinkTargets[] = { 0, 0, 0, 0 };
        const float shrinkSpeeds[] = { 0.7, 1.3, 2.5, 3.5 };
        const float thresholds[] = { 14, 9, 6, 0 };

        for (int i = 0; i < 4; ++i) {
            if (currentSize > thresholds[i]) {
                return Util::FInterpTo(currentSize, shrinkTargets[i], deltaTime, shrinkSpeeds[i]);
            }
        }

        return currentSize;
	}

    static void DrawCrosshair(hell::ivec2 viewportCenter, WeaponInfo* weaponInfo, std::vector<RenderItem2D>* renderItems, int m_crosshairCrossSize, hell::ivec2 presentSize)
    {
        hell::ivec2 crosshairPos = viewportCenter;

        // if (GetCrosshairType() == CrosshairType::REGULAR) {
        //     renderItems.push_back(RendererUtil::CreateRenderItem2D("CrosshairDot", crosshairPos, presentSize, Alignment::CENTERED));
        // }
        // else if (GetCrosshairType() == CrosshairType::INTERACT) {
        //     renderItems.push_back(RendererUtil::CreateRenderItem2D("CrosshairSquare", crosshairPos, presentSize, Alignment::CENTERED));
        // }


        renderItems->push_back(RendererUtil::CreateRenderItem2D("CrosshairCrossLeft", crosshairPos + hell::ivec2{ -int(m_crosshairCrossSize + Config::CROSSHAIR_GAP), 0 }, presentSize, Alignment::CENTERED));
        renderItems->push_back(RendererUtil::CreateRenderItem2D("CrosshairCrossRight", crosshairPos + hell::ivec2{ int(m_crosshairCrossSize + Config::CROSSHAIR_GAP), 0 }, presentSize, Alignment::CENTERED));
        renderItems->push_back(RendererUtil::CreateRenderItem2D("CrosshairCrossBottom", crosshairPos + hell::ivec2{ 0, -int(m_crosshairCrossSize + Config::CROSSHAIR_GAP) }, presentSize, Alignment::CENTERED));
        if (weaponInfo->type != WeaponType::PISTOL) // COD BO6 inspired - If we have a pistol, remove the top crosshair line
        {
            renderItems->push_back(RendererUtil::CreateRenderItem2D("CrosshairCrossTop", crosshairPos + hell::ivec2{ 0, int(m_crosshairCrossSize + Config::CROSSHAIR_GAP + 1) /* +1 is a magic number to make it look properly centered */ }, presentSize, Alignment::CENTERED));
        }
        renderItems->push_back(RendererUtil::CreateRenderItem2D("CrosshairDot", crosshairPos, presentSize, Alignment::CENTERED));

        static int texHeight = AssetManager::GetTextureByName("inventory_mockup")->GetHeight();
        static int height = (presentSize.y - texHeight) / 2;

        renderItems->push_back(RendererUtil::CreateRenderItem2D("inventory_mockup", { 40, height }, presentSize, Alignment::BOTTOM_LEFT));

    }
};