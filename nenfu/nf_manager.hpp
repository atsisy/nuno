#pragma once

#include <memory>
#include <string>

namespace nf
{
	class DeviceTrackerManager;
	class DisplayCallBack;
	class WindowManager;

	class NFManager {

	private:

		DeviceTrackerManager *device_tracker_manager;
		DisplayCallBack *display_callback;
		WindowManager *window_manager;


	public:

		NFManager(std::string title, unsigned int width, unsigned int height, int x, int y);
		~NFManager();

		DeviceTrackerManager *get_device_tracker_manager();
		DisplayCallBack *get_display_callback();
		WindowManager *get_window_manager();
		

	};

	class NFMChildren {

	protected:

		NFManager *manager;


	public:

		NFMChildren(NFManager *manager);
		~NFMChildren();

	};

}