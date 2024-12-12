#include "GUI_UI.hpp"

#include "BackEnd/BackEnd.hpp"
#include "Renderer/RendererUtil.hpp"
#include "Renderer/TextBlitter.hpp"
#include "Game/Round.hpp"

void IMGUI::ImGui_Init(GLFWwindow* window)
{
	ImGui_ShowDrawConsole = false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	std::cout << "[INIT] ImGui" << "\n";
}

void IMGUI::ImGui_StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void IMGUI::ImGui_ToggleDebugConsole()
{
	if (Input::KeyPressed(HELL_KEY_F8))
	{
		ImGui_ShowDrawConsole = !ImGui_ShowDrawConsole;

		if (ImGui_ShowDrawConsole)
		{
			std::cout << "Show cursor" << std::endl;
			Input::ShowCursor();
		}
		else
		{
			std::cout << "Hide cursor" << std::endl;
			Input::HideCursor();
			Input::DisableCursor();

			Game::GiveControlToPlayer1();

		}
	}
}

void IMGUI::ImGui_RenderFrame()
{
	// Gotta do updates inside the ImGui frame
	ImGui_ToggleDebugConsole();

	if (ImGui_ShowDrawConsole)
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	//std::cout << "Rendering" << ImGui_ShowDrawConsole << std::endl;
}

void IMGUI::ImGui_DrawDemoWindow()
{
	ImGui_StartFrame();

	// Draw ImGui UI
	if (!ImGui_DEMO)
	{
		return;
	}

	ImGui::ShowDemoWindow(&ImGui_DEMO);

	// Render 
	ImGui_RenderFrame();

	if (ImGui_DEBUG)
	{
		std::cout << "[DRAWING] ImGui" << "\n";
	}
}

void IMGUI::ImGui_DrawFPS(std::vector<RenderItem2D>* renderItems, hell::ivec2 debugTextLocation, hell::ivec2 presentSize)
{
	int fps = Util::GetFPS();

	if (OVERLAYS_SHOW_FPS)
	{
		// Format the FPS text
		std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));

		// Set the ImGui overlay position (e.g., top-left corner)
		ImGui::SetNextWindowPos(ImVec2(debugTextLocation.x, debugTextLocation.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_Always);

		// Render the FPS overlay
		ImGui::Begin("FPS Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
		ImGui::TextUnformatted(fpsText.c_str());
		ImGui::End();
	}
}


void IMGUI::ImGui_DrawMainBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Overlays"))
		{
			ImGui::Checkbox("Show FPS", &OVERLAYS_SHOW_FPS);
			ImGui::Checkbox("Show Frame Time", &OVERLAYS_SHOW_FRAME_TIME);
			ImGui::Checkbox("Show Memory Usage", &OVERLAYS_SHOW_MEMORY_USAGE);
			ImGui::Checkbox("Show Bounding Boxes", &OVERLAYS_SHOW_BOUNDING_BOXES);
			ImGui::Checkbox("Show Collision Debug", &OVERLAYS_SHOW_COLLISION_DEBUG);
			ImGui::Checkbox("Wireframe Mode", &OVERLAYS_WIREFRAME_MODE);
			ImGui::Checkbox("Show Minimap", &OVERLAYS_SHOW_MINIMAP);
			ImGui::EndMenu();
		}

		/*int leftX = RendererUtil::GetViewportLeftX(1, Game::GetSplitscreenMode(), gBufferSize.x, gBufferSize.y);
		int rightX = RendererUtil::GetViewportRightX(1, Game::GetSplitscreenMode(), gBufferSize.x, gBufferSize.y);
		int bottomY = RendererUtil::GetViewportBottomY(1, Game::GetSplitscreenMode(), gBufferSize.x, gBufferSize.y);*/

	/*	hell::ivec2 ammoSlashTextLocation = { 0,0 };
		if (Game::GetSplitscreenMode() == SplitscreenMode::NONE)
		{
			ammoSlashTextLocation.x = rightX - (gBufferSize.x * 0.125f);
			ammoSlashTextLocation.y = bottomY + (gBufferSize.x * 0.1f);
		}
		if (Game::GetSplitscreenMode() == SplitscreenMode::TWO_PLAYER)
		{
			ammoSlashTextLocation.x = rightX - (gBufferSize.x * 0.125f);
			ammoSlashTextLocation.y = bottomY + (gBufferSize.x * 0.065f);
		}
		if (Game::GetSplitscreenMode() == SplitscreenMode::FOUR_PLAYER)
		{
			ammoSlashTextLocation.x = rightX - (gBufferSize.x * 0.08f);
			ammoSlashTextLocation.y = bottomY + (gBufferSize.x * 0.065f);
		}*/


		std::vector<RenderItem2D> renderItems;

		const static hell::ivec2 roundCounterSize = { 1920, 1080 };
		const static hell::ivec2 testter = {480, 270};

		//hell::ivec2 ammoTotalTextLocation = { ammoSlashTextLocation.x + int(TextBlitter::GetCharacterSize("/", BitmapFontType::AMMO_NUMBERS).x * 1.6f * ammoTextScale), ammoSlashTextLocation.y };

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{
				ImGui_AddToConsoleLog("File > Open Selected");
			}
			if (ImGui::MenuItem("Save"))
			{
				ImGui_AddToConsoleLog("File > Save Selected");
			}
			if (ImGui::MenuItem("Exit"))
			{
				ImGui_AddToConsoleLog("Exiting...");
				// Make a are you sure prompt pop up.
				BackEnd::ForceCloseWindow();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				ImGui_AddToConsoleLog("File > Undo Selected");
			}
			if (ImGui::MenuItem("Redo"))
			{
				ImGui_AddToConsoleLog("File > Redo Selected");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				ImGui_AddToConsoleLog("Help > About Selected");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void IMGUI::ImGui_DrawMainCommandBox()
{
	ImGui_StartFrame();

	ImGui_DrawMainBar();

	ImGui::SetNextWindowPos(ImVec2(0, MainBarHeight), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y / 3));

	ImGui::Begin("Command Prompt", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	if (ImGui::BeginChild("CommandHistory", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true))
	{
		for (const auto& line : commandHistory)
		{
			ImGui::TextUnformatted(line.c_str());
		}
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
		{
			ImGui::SetScrollHereY(1.0f);
		}
	}
	ImGui::EndChild();

	// Input box at the bottom of the window
	static char inputBuffer[256] = "";
	ImGui::PushItemWidth(-1);
	if (ImGui::InputText("##CommandInput", inputBuffer, IM_ARRAYSIZE(inputBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (strlen(inputBuffer) > 0)
		{
			ImGui_ExecuteCommand(inputBuffer);
			//memset(inputBuffer, 0, sizeof(inputBuffer)); // Clear the input buffer
		}
	}
	ImGui::PopItemWidth();

	ImGui::End();

	ImGui_RenderFrame();
}

void IMGUI::ImGui_MainLoop()
{
	if (ImGui_DEMO)
	{
		ImGui_DrawDemoWindow();
	}
	else
	{
		ImGui_DrawMainCommandBox();
	}
}

void IMGUI::ImGui_Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	std::cout << "[CLEANUP] ImGui" << "\n";
}

bool IMGUI::ImGui_IsAnyWindowOpen()
{
	return ImGui_ShowDrawConsole;
}

void IMGUI::ImGui_AddToConsoleLog(std::string param)
{
	commandHistory.push_back(param);
}

void IMGUI::ImGui_ClearAllConsoleLogs()
{
	commandHistory.clear();
}

void IMGUI::ImGui_ExecuteCommand(const char* command)
{
	// Handle specific commands or general processing
	if (strcmp(command, "clear") == 0)
	{
		ImGui_ClearAllConsoleLogs();
	}
	else if (strcmp(command, "help") == 0)
	{
		ImGui_AddToConsoleLog("Available commands:\n- clear: Clears command history\n- help: Displays available commands");
	}
	else if (strcmp(command, "increaseround") == 0)
	{
		RoundManager::IncreaseRound();
		ImGui_AddToConsoleLog("Zombies: Increased round");
	}
	else if (strcmp(command, "decreaseround") == 0)
	{
		RoundManager::DecreaseRound();
		ImGui_AddToConsoleLog("Zombies: Decreased round");
	}
	else if (strcmp(command, "round") == 0)
	{
		RoundManager::SetCurrentRound(5);
		ImGui_AddToConsoleLog("Zombies: Set Current Round: 5");
	}
	else
	{
		ImGui_AddToConsoleLog(command);
	}
}