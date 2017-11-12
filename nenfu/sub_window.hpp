#pragma once

#include "utility.hpp"
#include "nf_manager.hpp"
#include <string>
#include <vector>
#include <memory>

namespace nf
{
	/*
	* Windowクラス
	* ウィンドウを表現するための抽象クラス
	*/
	class Window {

	private:

		std::string window_title;


	protected:

		unsigned int width;
		unsigned int height;
		int screen_x;
		int screen_y;

		const char *get_title() const;


	public:

		Window(std::string title, unsigned int width, unsigned int height, int x, int y);
		~Window();

		virtual void close()  = 0;
		virtual void render() = 0;

	};


	class RootWindow : public Window {

	private:

	public:

		RootWindow(std::string title, unsigned int width, unsigned int height, int x, int y);
		~RootWindow();

		void resize(int width, int height);
		unsigned int get_width();
		unsigned int get_height();

		void close();
		void render();

	};
	

	class WindowManager : public NFMChildren {

	private:

		std::vector<std::unique_ptr<Window>> window_buffer;
		std::unique_ptr<RootWindow> root_window;


	public:

		WindowManager(NFManager *manager, std::string title, unsigned int width, unsigned int height, int x, int y);
		~WindowManager();

		void add(std::unique_ptr<Window> ptr);
		size_t size();
		void render_all_window();

		unsigned int get_root_width();
		unsigned int get_root_height();
		void resize_root(int width, int height);

	};


	class StatusDisplay : public Window {

	private:


	public:

		StatusDisplay(std::string title, unsigned int width, unsigned int height, int x, int y);
		~StatusDisplay();

		void close();
		void render();

	};
}