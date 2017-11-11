#pragma once

#include "utility.hpp"
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


	class WindowManager {

	private:
		
		std::vector<std::unique_ptr<Window>> window_buffer;


	public:

		WindowManager();
		~WindowManager();

		void add(std::unique_ptr<Window> ptr);
		size_t size();

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