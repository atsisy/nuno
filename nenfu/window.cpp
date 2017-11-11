#include "sub_window.hpp"

namespace nf
{

	Window::Window(std::string title, unsigned int width, unsigned int height, int x, int y)
		: window_title(title)
	{
		this->width = width;
		this->height = height;
		this->screen_x = x;
		this->screen_y = y;
	}

	Window::~Window()
	{}


	WindowManager::WindowManager()
	{}

	WindowManager::~WindowManager()
	{}

	void WindowManager::add(std::unique_ptr<Window> ptr)
	{
		window_buffer.push_back(std::move(ptr));
	}

	size_t WindowManager::size()
	{
		return window_buffer.size();
	}

	const char *Window::get_title() const
	{
		return window_title.data();
	}

}