#pragma once

#include <memory>

namespace nf
{
	class DeviceTrackerManager;
	class DisplayCallBack;

	class NFManager {

	private:

		DeviceTrackerManager *device_tracker_manager;
		DisplayCallBack *display_callback;


	public:

		NFManager();
		~NFManager();

		DeviceTrackerManager *get_device_tracker_manager();
		DisplayCallBack *get_display_callback();
		

	};

	class NFMChildren {

	protected:

		NFManager *manager;


	public:

		NFMChildren(NFManager *manager);
		~NFMChildren();

	};

}