#include "device_tracker.hpp"
#include "callback.hpp"
#include "core.hpp"
#include <GL/glut.h>
#include <imgui.h>

namespace nf
{

	MouseTracker::MouseTracker(NFManager *manager)
		: NFMChildren(manager)
	{}

	MouseTracker::~MouseTracker()
	{}


	/*
	* imgui���̃}�E�X�J�[�\���̍��W���X�V���郁�\�b�h
	*/
	void MouseTracker::update_imgui_mouse_position(int x, int y)
	{
		ImGuiIO &io = ImGui::GetIO();
		io.MousePos = ImVec2((float)x, (float)y);
	}

	/*
	* imgui���̃}�E�X�J�[�\���̍��W���X�V���郁�\�b�h
	* ��������ImGuiIO &imgui_io�����A���ʂ�ImGuiIO�擾�������Ȃ�
	*/
	void MouseTracker::update_imgui_mouse_position(ImGuiIO &imgui_io, int x, int y)
	{
		imgui_io.MousePos = ImVec2((float)x, (float)y);
	}

	void MouseTracker::update_imgui_mouse_wheeling_status(int direction, int x, int y)
	{
		ImGuiIO &io = ImGui::GetIO();
		update_imgui_mouse_position(io, x, y);

		if (direction > 0)
		{
			io.MouseWheel = 1.0;
		}
		else if (direction < 0)
		{
			io.MouseWheel = -1.0;
		}
	}

	/*
	* translation_glut_message_button���\�b�h
	* glut�����΂���Ă������ϊ�����MouseTracker�N���X�̃����o��mouse_point_flag�ɑ�����Ȃ������\�b�h
	*/
	void MouseTracker::translation_glut_message_button(int button, int state, int x, int y)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON: translation_glut_message_left_state(state, x, y); break;
		case GLUT_MIDDLE_BUTTON: translation_glut_message_middle_state(state, x, y); break;
		case GLUT_RIGHT_BUTTON: translation_glut_message_right_state(state, x, y); break;
		default:
			break;
		}
	}


	/*
	* �ȉ��A�{�^���̎�ނɂ���ĕ��򂵂ĕϊ��𑱍s
	* �����3�Â̊֐��ŁA�ϊ��͊�������.
	*/

	void MouseTracker::translation_glut_message_left_state(int state, int x, int y)
	{
		Point2D<int> point(x, y);
		switch (state)
		{
		case GLUT_DOWN: 
			mouse_point_flag[MOUSE_LEFT_DOWN_POINT] = point; 
			glutSetCursor(GLUT_CURSOR_CROSSHAIR); 
			break;
		case GLUT_UP:
			mouse_point_flag[MOUSE_LEFT_UP_POINT] = point;
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
			break;
		default:
			break;
		}
	}

	void MouseTracker::translation_glut_message_middle_state(int state, int x, int y)
	{
		Point2D<int> point(x, y);
		switch (state)
		{
		case GLUT_DOWN: mouse_point_flag[MOUSE_MIDDLE_DOWN_POINT] = point; break;
		case GLUT_UP: mouse_point_flag[MOUSE_MIDDLE_UP_POINT] = point; break;
		default:
			break;
		}
	}

	void MouseTracker::translation_glut_message_right_state(int state, int x, int y)
	{
		Point2D<int> point(x, y);
		switch (state)
		{
		case GLUT_DOWN: mouse_point_flag[MOUSE_RIGHT_DOWN_POINT] = point; break;
		case GLUT_UP: mouse_point_flag[MOUSE_RIGHT_UP_POINT] = point; break;
		default:
			break;
		}
	}

	/*
	* �}�E�X���h���b�O���ꂽ�Ƃ��̏���
	* �����̓}�E�X�h���b�O���̃}�E�X���W
	*/
	void MouseTracker::mouse_dragging(int x, int y)
	{
		/*
		* imgui���̃}�E�X���W���X�V
		*/
		update_imgui_mouse_position(x, y);

		/*
		* ���݂̈ʒu��ێ�
		*/
		Point2D<int> point(x, y);

		/*
		* �Ō�ɋL�^�����}�E�X�̍��W�Ƃ̍�����1,0�ɕϊ����A�����distance�Ɋi�[
		*/
		Point3D<double> distance = minimum_scroll_distance<double>((Point3D<double>(mouse_point_flag[MOUSE_DRAGGING_PRESENT_POINT] - point)));

		if (manager->get_device_tracker_manager()->get_keyboard_tracker().is_shift_down())
		{
			/*
			* Shift�L�[��������Ă����ꍇ��Rotated
			*/
			glRotated(ROTATE_MINIMUM_ANGLE, -distance.get_y(), distance.get_z(), -distance.get_x());
		}
		else if(manager->get_device_tracker_manager()->get_keyboard_tracker().is_ctrl_down())
		{
			/*
			* Ctrl�L�[��������Ă����ꍇ��Translated
			*/
			glTranslated(-distance.get_x(), distance.get_y(), distance.get_z());
		}

		/*
		* ���W���X�V
		*/
		mouse_point_flag[MOUSE_DRAGGING_PRESENT_POINT] = point;

		/*
		* �ĕ`����s��
		*/
		glutPostRedisplay();

	}

	void MouseTracker::mouse_wheeling(int wheel_flag, int direction, int x, int y)
	{
		update_imgui_mouse_wheeling_status(direction, x, y);

		if (manager->get_device_tracker_manager()->get_keyboard_tracker().is_shift_down())
		{
			if (direction == 1)
			{
				glRotated(ROTATE_MINIMUM_ANGLE, 0, 1, 0);
			}
			else
			{
				glRotated(ROTATE_MINIMUM_ANGLE, 0, -1, 0);
			}
		}
		else if(manager->get_device_tracker_manager()->get_keyboard_tracker().is_ctrl_down())
		{
			if (direction == 1)
			{
				glTranslated(0, 0, 1);
			}
			else
			{
				glTranslated(0, 0, -1);
			}
		}

		glutPostRedisplay();
	}

	void MouseTracker::mouse_moving(int x, int y)
	{
		mouse_point_flag[MOUSE_PRESENT_POINT] = Point2D<int>(x, y);
	}

	Point2D<int> MouseTracker::access(MouseEventPointEnum flag) const
	{
		return mouse_point_flag[flag];
	}

}