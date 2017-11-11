#include <GL/glut.h>
#include <GL/freeglut.h>
#include "callback.hpp"
#include "device_tracker.hpp"
#include "core.hpp"
#include "sub_window.hpp"
#include <imgui_impl_glut.h>
#include <imgui.h>

extern nf::NFManager *nf_manager;


bool show_test_window = true;
bool show_another_window = false;


void display()
{
	/*
	* �`�揈���Ăяo��
	*/
	nf_manager->get_display_callback()->run();

	ImGui_ImplGLUT_NewFrame(WINDOW_WIDTH, WINDOW_HEIGHT, 1.0 / 60);

	
	static nf::StatusDisplay window("Status", 300, 300, 10, 10);

	window.render();

	ImGui::Render();


	// �J���[�o�b�t�@�̓���ւ�
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

	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);

	if (state == GLUT_DOWN && (button == GLUT_LEFT_BUTTON))
		io.MouseDown[0] = true;
	else
		io.MouseDown[0] = false;

	if (state == GLUT_DOWN && (button == GLUT_RIGHT_BUTTON))
		io.MouseDown[1] = true;
	else
		io.MouseDown[1] = false;

	glutPostRedisplay();
}

void mouse_dragging_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_dragging(x, y);
	
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
}

void mouse_moving_event(int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_moving(x, y);
}

void mouse_wheeling_event(int wheel_flag, int direction, int x, int y)
{
	nf_manager->get_device_tracker_manager()->get_mouse_tracker().mouse_wheeling(wheel_flag, direction, x, y);
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)x, (float)y);
	if (direction > 0)
	{
		// Zoom in
		io.MouseWheel = 1.0;
	}
	else if (direction < 0)
	{
		// Zoom out
		io.MouseWheel = -1.0;
	}

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

void register_glut_call_back()
{
	/*
	* �`��p�R�[���o�b�N�o�^
	*/
	glutDisplayFunc(display);

	/*
	* �ҋ@���R�[���o�b�N�o�^
	*/
	glutIdleFunc(idle);

	/*
	* �}�E�X�{�^���C�x���g�R�[���o�b�N�o�^
	*/
	glutMouseFunc(mouse_button_event);
	
	/*
	* �}�E�X�h���b�O���R�[���o�b�N�o�^
	*/
	glutMotionFunc(mouse_dragging_event);

	/*
	* �}�E�X�ړ����R�[���o�b�N�o�^
	*/
	glutPassiveMotionFunc(mouse_moving_event);

	/*
	* �}�E�X�X�N���[�����̃R�[���o�b�N�o�^
	*/
	glutMouseWheelFunc(mouse_wheeling_event);

	/*
	* �L�[�{�[�h�������ꂽ�Ƃ��̃R�[���o�b�N�o�^
	*/
	glutKeyboardFunc(keyboard_key_down);

	/*
	* �L�[�{�[�h�������ꂽ�Ƃ��̃R�[���o�b�N�o�^
	*/
	glutKeyboardUpFunc(keyboard_key_up);

}