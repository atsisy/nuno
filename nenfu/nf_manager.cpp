#include "nf_manager.hpp"
#include "device_tracker.hpp"
#include "callback.hpp"

namespace nf
{

	NFManager::NFManager()
	{
		device_tracker_manager = new nf::DeviceTrackerManager(this);
		display_callback = new nf::DisplayCallBack(this);
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

}