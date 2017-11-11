#include "device_tracker.hpp"
#include <GL/glut.h>
#include <imgui.h>

namespace nf
{
	/*
	* ���񂱂�R���X�g���N�^
	*/
	KeyboardTracker::KeyboardTracker(NFManager *manager)
		: NFMChildren(manager)
	{
		/*
		* �L�[�{�[�h�e�[�u���̏�����Ԃ͂��ׂĉ�����ĂȂ����
		*/
		std::fill(std::begin(key_table), std::end(key_table), false);
	}

	KeyboardTracker::~KeyboardTracker()
	{}

	/*
	* imgui�ɃL�[���͂����������Ƃ�`���郁�\�b�h
	*/
	void KeyboardTracker::send_keycode_to_imgui(unsigned char key_code)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.AddInputCharacter(key_code);
	}

	/*
	* �L�[�{�[�h�������ꂽ�Ƃ��ɁA����ascii�R�[�h���󂯎��A�������s�����\�b�h
	*/
	void KeyboardTracker::recieve_key_down_signal(unsigned char ascii_key_code)
	{
		/*
		* �����ꂽ�L�[�R�[�h���L�[�e�[�u���ɋL�^
		*/
		key_table[ascii_key_code] = true;

		/*
		* imgui�ɃL�[�������ꂽ���Ƃ��
		*/
		send_keycode_to_imgui(ascii_key_code);
	}

	/*
	* �L�[�{�[�h�������ꂽ�Ƃ��ɂ���ascii�R�[�h���󂯎��A�������s�����\�b�h
	*/
	void KeyboardTracker::recieve_key_up_signal(unsigned char ascii_key_code)
	{
		key_table[ascii_key_code] = false;
	}
	
	/*
	* ascii�R�[�h�Ŏw�肳�ꂽ�L�[��������Ă��邩���肷�郁�\�b�h
	*/
	bool KeyboardTracker::is_down(unsigned char ascii_key_code)
	{
		return key_table[ascii_key_code];
	}

	/*
	*
	* �ȉ��A�C���L�[�̔��胁�\�b�h
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