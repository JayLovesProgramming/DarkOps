#pragma once

class InventoryManager
{
public:

	static void DrawInventory(std::vector<RenderItem2D>* renderItems, hell::ivec2 presentSize)
	{
		static int texHeight = AssetManager::GetTextureByName("inventory_mockup")->GetHeight();
		static int height = (presentSize.y - texHeight) / 2;

		renderItems->push_back(RendererUtil::CreateRenderItem2D("inventory_mockup", { 40, height }, presentSize, Alignment::BOTTOM_LEFT));
	}
};