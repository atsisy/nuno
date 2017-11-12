#include "nf_manager.hpp"
#include "device_tracker.hpp"
#include "callback.hpp"
#include "sub_window.hpp"

namespace nf
{

	NFManager::NFManager(std::string title, unsigned int width, unsigned int height, int x, int y)
	{
		device_tracker_manager = new nf::DeviceTrackerManager(this);
		display_callback = new nf::DisplayCallBack(this);
		window_manager = new nf::WindowManager(this, title, width, height, x, y);
	}

	NFManager::~NFManager()
	{
		delete device_tracker_manager;
		delete display_callback;
	}

	NFMChildren::NFMChildren(NFManager *manager)
	{
		this->manager = manager;
	}

	NFMChildren::~NFMChildren()
	{}

	DeviceTrackerManager *NFManager::get_device_tracker_manager()
	{
		return device_tracker_manager;
	}

	DisplayCallBack *NFManager::get_display_callback()
	{
		return display_callback;
	}

	WindowManager *NFManager::get_window_manager()
	{
		return window_manager;
	}

}