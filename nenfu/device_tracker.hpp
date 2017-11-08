#pragma once

#include "utility.hpp"
#include "int_types.hpp"
#include "nf_manager.hpp"
#include <array>
#include <iostream>
#include <unordered_map>

namespace nf
{

	enum MouseEventPointEnum
	{
		MOUSE_RIGHT_DOWN_POINT,
		MOUSE_RIGHT_UP_POINT,
		MOUSE_MIDDLE_DOWN_POINT,
		MOUSE_MIDDLE_UP_POINT,
		MOUSE_LEFT_DOWN_POINT,
		MOUSE_LEFT_UP_POINT,
		MOUSE_PRESENT_POINT,
		MOUSE_DRAGGING_PRESENT_POINT,
		MOUSE_EVENT_POINT_ENUM_SIZE
	};

	class MouseTracker : public NFMChildren {

	private:

		std::array<Point2D<int>, MOUSE_EVENT_POINT_ENUM_SIZE> mouse_point_flag;


		void translation_glut_message_left_state(int state, int x, int y);
		void translation_glut_message_middle_state(int state, int x, int y);
		void translation_glut_message_right_state(int state, int x, int y);

		template <typename T>
		Point3D<T> minimum_scroll_distance(const Point3D<T> &value)
		{
			return Point3D<T>(
				binary<T>(value.get_x(), 1.0),
				binary<T>(value.get_y(), 1.0),
				binary<T>(value.get_z(), 1.0)
				);
		}

		template <typename T>
		T binary(T value, T return_value)
		{
			return value != 0 ? (return_value * (value < 0 ? -1 : 1)) : 0;
		}


	public:

		MouseTracker(NFManager *manager);
		~MouseTracker();

		void mouse_dragging(int x, int y);
		void mouse_moving(int x, int y);

		void translation_glut_message_button(int button, int state, int x, int y);
		Point2D<int> access(MouseEventPointEnum flag) const;

	};

	class KeyboardTracker : public NFMChildren {

	private:

		std::array<bool, 256> key_table;


	public:

		KeyboardTracker(NFManager *manager);
		~KeyboardTracker();

		void recieve_key_down_signal(unsigned char ascii_key_code);
		void recieve_key_up_signal(unsigned char ascii_key_code);
		bool is_down(unsigned char ascii_key_code);

		bool is_shift_down();
		bool is_ctrl_down();
		bool is_alt_down();


	};

	class DeviceTrackerManager {

	private:

		KeyboardTracker keyboard_tracker;
		MouseTracker mouse_tracker;


	public:

		DeviceTrackerManager(NFManager *manager);
		~DeviceTrackerManager();

		MouseTracker &get_mouse_tracker();
		KeyboardTracker &get_keyboard_tracker();

	};

}