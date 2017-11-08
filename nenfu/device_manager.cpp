#pragma once
#include "device_tracker.hpp"

namespace nf
{
	DeviceTrackerManager::DeviceTrackerManager(NFManager *manager)
		: mouse_tracker(manager) {}

	DeviceTrackerManager::~DeviceTrackerManager()
	{}

	MouseTracker &DeviceTrackerManager::get_mouse_tracker()
	{
		return mouse_tracker;
	}

}