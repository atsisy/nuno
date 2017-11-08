#include <GL/glut.h>
#include "callback.hpp"
#include "device_tracker.hpp"

extern nf::NFManager *nf_manager;

void display()
{
	/*
	* 描画処理呼び出し
	*/
	nf_manager->get_display_callback()->run();
}

void idle()
{
	static nf::IdleCallBack idle_call_back(nf_manager);

	idle_call_back.run();
}

void mouse_button_event(int button, int state, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().translation_glut_message_button(button, state, x, y);
}

void mouse_dragging_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_dragging(x, y);
}

void mouse_moving_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_moving(x, y);
}

void keyboard_key_down(unsigned char ascii_key_code, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_keyboard_tracker().recieve_key_down_signal(ascii_key_code);
}

void keyboard_key_up(unsigned char ascii_key_code, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_keyboard_tracker().recieve_key_up_signal(ascii_key_code);
}

void register_glut_call_back()
{
	/*
	* 描画用コールバック登録
	*/
	glutDisplayFunc(display);

	/*
	* 待機時コールバック登録
	*/
	glutIdleFunc(idle);

	/*
	* マウスボタンイベントコールバック登録
	*/
	glutMouseFunc(mouse_button_event);
	
	/*
	* マウスドラッグ時コールバック登録
	*/
	glutMotionFunc(mouse_dragging_event);

	/*
	* マウス移動時コールバック登録
	*/
	glutPassiveMotionFunc(mouse_moving_event);

	/*
	* キーボードが押されたときのコールバック登録
	*/
	glutKeyboardFunc(keyboard_key_down);

	/*
	* キーボードが離されたときのコールバック登録
	*/
	glutKeyboardUpFunc(keyboard_key_up);

}