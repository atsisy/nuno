#include "device_tracker.hpp"
#include "callback.hpp"
#include <GL/glut.h>

namespace nf
{

	MouseTracker::MouseTracker(NFManager *manager)
		: NFMChildren(manager)
	{}

	MouseTracker::~MouseTracker()
	{}

	/*
	* translation_glut_message_buttonメソッド
	* glutから飛ばされてくる情報を変換してMouseTrackerクラスのメンバのmouse_point_flagに代入しなおすメソッド
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
	* 以下、ボタンの種類によって分岐して変換を続行
	* これら3つ津の関数で、変換は完了する.
	*/

	void MouseTracker::translation_glut_message_left_state(int state, int x, int y)
	{
		Point2D<int> point(x, y);
		switch (state)
		{
		case GLUT_DOWN: mouse_point_flag[MOUSE_LEFT_DOWN_POINT] = point; break;
		case GLUT_UP: mouse_point_flag[MOUSE_LEFT_UP_POINT] = point; break;
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

	void MouseTracker::mouse_dragging(int x, int y)
	{
		Point2D<int> point(x, y);

		Point3D<double> distance = minimum_scroll_distance<double>((Point3D<double>(mouse_point_flag[MOUSE_DRAGGING_PRESENT_POINT] - point)));

		glTranslated(-distance.get_x(), distance.get_y(), distance.get_z());
		glutPostRedisplay();
		mouse_point_flag[MOUSE_DRAGGING_PRESENT_POINT] = point;

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