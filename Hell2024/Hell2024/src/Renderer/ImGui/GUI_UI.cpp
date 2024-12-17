#include "GUI_UI.hpp"

#include "BackEnd/BackEnd.hpp"

#include "Renderer/RendererUtil.hpp"
#include "Renderer/TextBlitter.hpp"
#include "Renderer/Minimap.hpp"

#include "Game/Round.hpp"
#include "Game/MiscObjects.hpp"

#include "AssetBrowser/AssetBrowser.hpp"

void IMGUI::Init(GLFWwindow* window)
{
	F8_TOGGLED = false;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	std::cout << "[INIT] ImGui" << "\n";
}

void IMGUI::StartFrame()
{
	glDisable(GL_DEPTH_TEST);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void IMGUI::ToggleDebugConsole()
{
	if (Input::KeyPressed(HELL_KEY_F8))
	{
		F8_TOGGLED = !F8_TOGGLED;

		if (F8_TOGGLED)
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

void IMGUI::RenderFrame()
{
	// Gotta do updates inside the ImGui frame
	ToggleDebugConsole();

	ImGui::Render();

	// Render cursor?
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//std::cout << "Rendering" << F8_TOGGLED << std::endl;
}

void IMGUI::DrawDemoWindow()
{
	// Draw ImGui UI
	if (ImGui_DEMO)
	{
		ImGui::ShowDemoWindow(&ImGui_DEMO);
	}
}

void IMGUI::DrawAllOverlays()
{
	DrawFPS();
	DrawDeltaTime();
}

int IMGUI::GetUIOverlayPosition(std::string type)
{
	UIElements uiElements = {};
	if (type == "DeltaTime")
	{
		if (!OVERLAYS_SHOW_FPS)
		{
			//return 10;
			return uiElements.positions[1];
		}
		else
		{
			//return 80;
			return uiElements.positions[2];
		}
	}

	return 0;
}

void IMGUI::DrawFPS()
{
	if (OVERLAYS_SHOW_FPS)
	{
		int fps = Util::GetFPS();
		std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
		ImGui::Begin("FPS Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(10, ImGui::GetIO().DisplaySize.y - 30), ImGuiCond_Always);
		ImGui::TextUnformatted(fpsText.c_str());
		ImGui::End();
		//std::cout << "Drawing FPS" << std::endl;wd
	}
}

void IMGUI::DrawDeltaTime()
{
	if (OVERLAYS_SHOW_DELTA_TIME)
	{
		double deltaTime = Game::GetDeltaTime();
		std::string deltaTimeText = "Delta Time: " + std::to_string(static_cast<double>(deltaTime));
		ImGui::Begin("Delta Time Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos(ImVec2(GetUIOverlayPosition("DeltaTime"), ImGui::GetIO().DisplaySize.y - 30), ImGuiCond_Always);
		ImGui::TextUnformatted(deltaTimeText.c_str());
		ImGui::End();
		//std::cout << "Drawing Delta Time" << std::endl;wd
	}
}

void IMGUI::DrawMainBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Overlays"))
		{
			ImGui::Checkbox("Show FPS", &OVERLAYS_SHOW_FPS);
			ImGui::Checkbox("Show Frame Time", &OVERLAYS_SHOW_DELTA_TIME);
			ImGui::Checkbox("Show Minimap", &Minimap::MINIMAP_ENABLED);
			ImGui::Checkbox("Show Memory Usage", &OVERLAYS_SHOW_MEMORY_USAGE);
			ImGui::Checkbox("Show Bounding Boxes", &OVERLAYS_SHOW_BOUNDING_BOXES);
			ImGui::Checkbox("Show Collision Debug", &OVERLAYS_SHOW_COLLISION_DEBUG);
			ImGui::Checkbox("Wireframe Mode", &OVERLAYS_WIREFRAME_MODE);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{
				AddToConsoleLog("File > Open Selected");
			}
			if (ImGui::MenuItem("Save"))
			{
				AddToConsoleLog("File > Save Selected");
			}
			if (ImGui::MenuItem("Exit"))
			{
				AddToConsoleLog("Exiting...");
				// Make a are you sure prompt pop up.
				BackEnd::ForceCloseWindow();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				AddToConsoleLog("File > Undo Selected");
			}
			if (ImGui::MenuItem("Redo"))
			{
				AddToConsoleLog("File > Redo Selected");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				AddToConsoleLog("Help > About Selected");
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void IMGUI::DrawF8Command()
{

	if (F8_TOGGLED)
	{

		DrawMainBar();
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
				ExecuteCommand(inputBuffer);
				//memset(inputBuffer, 0, sizeof(inputBuffer)); // Clear the input buffer
			}
		}
		ImGui::PopItemWidth();

		ImGui::End();
	}
}

void IMGUI::MainLoop()
{
	StartFrame();
	if (ImGui_DEMO)
	{
		DrawDemoWindow();
	}
	else
	{
		//AssetBrowser assetBrowser;
		AssetBrowser::Render();
		DrawF8Command();
		DrawAllOverlays();
	}
	RenderFrame();
}

void IMGUI::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	std::cout << "[CLEANUP] ImGui" << "\n";
}

bool IMGUI::IsAnyWindowOpen()
{
	return F8_TOGGLED;
}

void IMGUI::AddToConsoleLog(std::string param)
{
	commandHistory.push_back(param);
}

void IMGUI::ClearAllConsoleLogs()
{
	commandHistory.clear();
}

void IMGUI::ExecuteCommand(const char* command)
{
	// Handle specific commands or general processing
	if (strcmp(command, "clear") == 0)
	{
		ClearAllConsoleLogs();
	}
	else if (strcmp(command, "help") == 0)
	{
		AddToConsoleLog("Available commands:\n- clear: Clears command history\n- help: Displays available commands");
	}
	else if (strcmp(command, "increaseround") == 0)
	{
		int previousRound = RoundManager::GetCurrentRound();
		RoundManager::IncreaseRound();
		AddToConsoleLog("Zombies: Increased Round From " + std::to_string(previousRound) +" To " + std::to_string(RoundManager::GetCurrentRound()));
	}
	else if (strcmp(command, "decreaseround") == 0)
	{
		int previousRound = RoundManager::GetCurrentRound();
		RoundManager::DecreaseRound();
		AddToConsoleLog("Zombies: Decreased Round From " + std::to_string(previousRound) + " To " + std::to_string(RoundManager::GetCurrentRound()));
	}
	else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
	{
		BackEnd::ForceCloseWindow();
	}
	else if (strcmp(command, "round") == 0)
	{
		RoundManager::SetCurrentRound(5);
		AddToConsoleLog("Zombies: Set Current Round: 5");
	}
	else if (strcmp(command, "spawn juggernog") == 0)
	{
		MiscObjectsManager::SpawnJuggernog();
		AddToConsoleLog("Zombies: Spawned juggernog");
	}
	else if (strcmp(command, "spawn speedcola") == 0)
	{
		MiscObjectsManager::SpawnSpeedCola();
		AddToConsoleLog("Zombies: Spawned speedcola");
	}
	else
	{
		AddToConsoleLog(command);
	}
}

// Assets Browser
