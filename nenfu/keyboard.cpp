#include "device_tracker.hpp"
#include <GL/glut.h>

namespace nf
{

	KeyboardTracker::KeyboardTracker(NFManager *manager)
		: NFMChildren(manager)
	{
		/*
		* キーボードテーブルの初期状態はすべて押されてない状態
		*/
		std::fill(std::begin(key_table), std::end(key_table), false);
	}

	KeyboardTracker::~KeyboardTracker()
	{}

	void KeyboardTracker::recieve_key_down_signal(unsigned char ascii_key_code)
	{
		key_table[ascii_key_code] = true;
	}

	void KeyboardTracker::recieve_key_up_signal(unsigned char ascii_key_code)
	{
		key_table[ascii_key_code] = false;
	}

	bool KeyboardTracker::is_down(unsigned char ascii_key_code)
	{
		return key_table[ascii_key_code];
	}

	bool KeyboardTracker::is_shift_down()
	{
		return glutGetModifiers() & GLUT_ACTIVE_SHIFT;
	}

	bool KeyboardTracker::is_ctrl_down()
	{
		return glutGetModifiers() & GLUT_ACTIVE_CTRL;
	}

	bool KeyboardTracker::is_alt_down()
	{
		return glutGetModifiers() & GLUT_ACTIVE_ALT;
	}

}