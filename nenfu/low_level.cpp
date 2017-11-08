#include <GL/glut.h>
#include "callback.hpp"
#include "device_tracker.hpp"

extern nf::NFManager *nf_manager;

void display()
{
	/*
	* �`�揈���Ăяo��
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

}