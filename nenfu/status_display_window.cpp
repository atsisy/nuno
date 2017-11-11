#include "sub_window.hpp"
#include <imgui.h>

namespace nf
{

	StatusDisplay::StatusDisplay(std::string title, unsigned int width, unsigned int height, int x, int y)
		: Window(title, width, height, x, y)
	{}

	StatusDisplay::~StatusDisplay()
	{}

	void StatusDisplay::close()
	{}

	void StatusDisplay::render()
	{
		ImGui::Begin(get_title());
		static float f = 0.0f;
		ImGui::Text("This is status window");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

	}

}