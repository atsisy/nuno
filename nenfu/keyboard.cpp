#include "device_tracker.hpp"
#include <GL/glut.h>
#include <imgui.h>

namespace nf
{
	/*
	* こんこんコンストラクタ
	*/
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

	/*
	* imguiにキー入力があったことを伝えるメソッド
	*/
	void KeyboardTracker::send_keycode_to_imgui(unsigned char key_code)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.AddInputCharacter(key_code);
	}

	/*
	* キーボードが押されたときに、そのasciiコードを受け取り、処理を行うメソッド
	*/
	void KeyboardTracker::recieve_key_down_signal(unsigned char ascii_key_code)
	{
		/*
		* 押されたキーコードをキーテーブルに記録
		*/
		key_table[ascii_key_code] = true;

		/*
		* imguiにキーが押されたことを報告
		*/
		send_keycode_to_imgui(ascii_key_code);
	}

	/*
	* キーボードが離されたときにそのasciiコードを受け取り、処理を行うメソッド
	*/
	void KeyboardTracker::recieve_key_up_signal(unsigned char ascii_key_code)
	{
		key_table[ascii_key_code] = false;
	}
	
	/*
	* asciiコードで指定されたキーが押されているか判定するメソッド
	*/
	bool KeyboardTracker::is_down(unsigned char ascii_key_code)
	{
		return key_table[ascii_key_code];
	}

	/*
	*
	* 以下、修飾キーの判定メソッド
	*
	*/

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