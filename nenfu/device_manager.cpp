#pragma once
#include "device_tracker.hpp"

namespace nf
{
	DeviceTrackerManager::DeviceTrackerManager(NFManager *manager)
		: keyboard_tracker(manager), mouse_tracker(manager) {}

	DeviceTrackerManager::~DeviceTrackerManager()
	{}

	KeyboardTracker &DeviceTrackerManager::get_keyboard_tracker()
	{
		return keyboard_tracker;
	}

	MouseTracker &DeviceTrackerManager::get_mouse_tracker()
	{
		return mouse_tracker;
	}

}