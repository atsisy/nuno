#include <GL/glut.h>
#include <GL/freeglut.h>
#include "callback.hpp"
#include "device_tracker.hpp"
#include "core.hpp"
#include "sub_window.hpp"
#include <imgui_impl_glut.h>
#include <imgui.h>
#include <iostream>

extern nf::NFManager *nf_manager;


bool show_test_window = true;
bool show_another_window = false;


void display()
{
	/*
	* 描画処理呼び出し
	*/
	nf_manager->get_display_callback()->run();

	ImGui_ImplGLUT_NewFrame(nf_manager->get_window_manager()->get_root_width(), nf_manager->get_window_manager()->get_root_height(), 1.0 / 60);

	nf_manager->get_window_manager()->render_all_window();


	ImGui::Render();


	// カラーバッファの入れ替え
	glutSwapBuffers();

}

void idle()
{
	static nf::IdleCallBack idle_call_back(nf_manager);

	idle_call_back.run();
}

void mouse_button_event(int button, int state, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().translation_glut_message_button(button, state, x, y);
	glutPostRedisplay();
}

void mouse_dragging_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_dragging(x, y);
}

void mouse_moving_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_moving(x, y);
	glutPostRedisplay();
}

void mouse_wheeling_event(int wheel_flag, int direction, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_wheeling(wheel_flag, direction, x, y);
	glutPostRedisplay();
}

void keyboard_key_down(unsigned char ascii_key_code, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_keyboard_tracker().recieve_key_down_signal(ascii_key_code);
}

void keyboard_key_up(unsigned char ascii_key_code, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_keyboard_tracker().recieve_key_up_signal(ascii_key_code);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);

	nf_manager->get_window_manager()->resize_root(w, h);
}

void register_glut_call_back()
{
	/*
	* 描画用コールバック登録
	*/
	glutDisplayFunc(display);

	/*
	* 待機時コールバック登録
	* 今のところ特にやることがないのでコメントアウト
	* これを走らせると、idle関数が呼ばれまくってCPU使用率がMAXになるってのもある
	*/
	//glutIdleFunc(idle);

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
	* マウススクロール時のコールバック登録
	*/
	glutMouseWheelFunc(mouse_wheeling_event);

	/*
	* ウィンドウのりサイズ時に呼び出されるコールバック登録
	*/
	glutReshapeFunc(resize);

	/*
	* キーボードが押されたときのコールバック登録
	*/
	glutKeyboardFunc(keyboard_key_down);

	/*
	* キーボードが離されたときのコールバック登録
	*/
	glutKeyboardUpFunc(keyboard_key_up);

	nf_manager->get_window_manager()->add(std::make_unique<nf::StatusDisplay>("Status", 300, 300, 10, 10));

}