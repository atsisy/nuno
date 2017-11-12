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


	WindowManager::WindowManager(NFManager *maanger, std::string title, unsigned int width, unsigned int height, int x, int y)
		: NFMChildren(manager), root_window(std::make_unique<RootWindow>(title, width, height, x, y))
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

	void WindowManager::render_all_window()
	{
		for (std::unique_ptr<Window> &ptr : window_buffer)
		{
			ptr->render();
		}
	}

	unsigned int WindowManager::get_root_width()
	{
		return root_window->get_width();
	}

	unsigned int WindowManager::get_root_height()
	{
		return root_window->get_height();
	}

	void WindowManager::resize_root(int width, int height)
	{
		root_window->resize(width, height);
	}

	const char *Window::get_title() const
	{
		return window_title.data();
	}


	RootWindow::RootWindow(std::string title, unsigned int width, unsigned int height, int x, int y)
		: Window(title, width, height, x, y)
	{}

	RootWindow::~RootWindow()
	{}


	void RootWindow::resize(int width, int height)
	{
		this->width = width;
		this->height = height;
	}

	unsigned int RootWindow::get_width()
	{
		return this->width;
	}

	unsigned int RootWindow::get_height()
	{
		return this->height;
	}

	void RootWindow::close()
	{}

	void RootWindow::render()
	{}

}