#include "GUI_UI.h"


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

			//for (int i = 0; i < Game::GetPlayerCount(); i++)
			//{
			//	Player* player = Game::GetPlayerByIndex(i);

			//	if (Game::IsLoaded() && player->IsAlive());
			//	{
			//		//Game::GiveControlToPlayer1();
			//		std::cout << "ALIVE BABY" << std::endl;
			//		break;
			//	}
			//}
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

void IMGUI::ImGui_DrawMainBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{
				commandHistory.push_back("File > Open Selected");
			}
			if (ImGui::MenuItem("Save"))
			{
				commandHistory.push_back("File > Save Selected");
			}
			if (ImGui::MenuItem("Exit"))
			{
				commandHistory.push_back("File > Exit Selected");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo"))
			{
				commandHistory.push_back("File > Undo Selected");
			}
			if (ImGui::MenuItem("Redo"))
			{
				commandHistory.push_back("File > Redo Selected");
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				commandHistory.push_back("Help > About Selected");
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

	ImGui::SetNextWindowPos(ImVec2(10, 0), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y / 3));

	//ImVec2 windowSize = ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - ImGui::GetMenuBarHeight());
	//ImGui::SetNextWindowSize(windowSize);
	//ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - windowSize.y));

	ImGui::Begin("Command Prompt", nullptr, ImGuiWindowFlags_NoTitleBar);

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
	if (ImGui::InputText("##CommandInput", inputBuffer, IM_ARRAYSIZE(inputBuffer)))
	{
		if (strlen(inputBuffer) > 0)
		{
			//commandHistory.push_back(inputBuffer);
			//memset(inputBuffer, 0, sizeof(inputBuffer));  // Clear the input buffer
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
