#include "callback.hpp"
#include <GL/glut.h>

#include <iostream>

namespace nf
{

	/*
	* DisplayCallBackクラス
	* 非公開メソッド
	*/
	void DisplayCallBack::draw_grid()
	{
		double ground_max_x = 300.0;
		double ground_max_y = 300.0;
		glColor3d(0.8, 0.8, 0.8);
		glBegin(GL_LINES);
		for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0)
		{
			glVertex3d(-ground_max_x, ly, 0);
			glVertex3d(ground_max_x, ly, 0);
		}
		for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0) 
		{
			glVertex3d(lx, ground_max_y, 0);
			glVertex3d(lx, -ground_max_y, 0);
		}
		glEnd();
	}

	void DisplayCallBack::look_from()
	{
		camera.look_from();
	}
	

	void DisplayCallBack::move_camera(Camera3DPointType type, int x, int y, int z)
	{
		camera.move(type, x, y, z);
		look_from();
	}

	void DisplayCallBack::move_camera(Camera3DPointType type, Point3D<double> point)
	{
		camera.move(type, point);
		look_from();
	}

	/*
	* DisplayCallBackクラス
	* 公開メソッド
	*/

	/*
	* DisplayCallBackクラス コンストラクタ
	* 
	*/
	DisplayCallBack::DisplayCallBack(nf::NFManager *nf_manager)
		: GlutCallBack(nf_manager)
	{
		target_function = [this]()
		{

			// バッファの消去
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// グリッドの描画
			draw_grid();

			// カラーバッファの入れ替え
			glutSwapBuffers();
		};
	}

	DisplayCallBack::~DisplayCallBack()
	{}

	void DisplayCallBack::run()
	{
		target_function();
	}

	Camera::Camera()
		: view_point(0.0, -700.0, 150.0), view_center_point(0.0, 100.0, 0.0), view_upper_vector(0.0, 0.0, 1.0) {}

	Camera::~Camera()
	{}

	void Camera::move(Camera3DPointType type, int x, int y, int z)
	{
		Point3D<double> point(x, y, z);
		switch (type)
		{
		case nf::VIEW_POINT: view_point += point; break;
		case nf::VIEW_CENTER_POINT: view_center_point += point; break;
		case nf::VIEW_UPPER_POINT: view_upper_vector += point; break;
		default:
			break;
		}
	}

	void Camera::move(Camera3DPointType type, Point3D<double> point)
	{
		switch (type)
		{
		case nf::VIEW_POINT: view_point += point; break;
		case nf::VIEW_CENTER_POINT: view_center_point += point; break;
		case nf::VIEW_UPPER_POINT: view_upper_vector += point; break;
		default:
			break;
		}
	}

	void Camera::look_from()
	{
		gluPerspective(30.0, (double)600 / (double)600, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);
		
		gluLookAt(
			view_point.get_x(), view_point.get_y(), view_point.get_z(),
			view_center_point.get_x(), view_center_point.get_y(), view_center_point.get_z(),
			view_upper_vector.get_x(), view_upper_vector.get_y(), view_upper_vector.get_z()
		);

		std::cout << view_point.get_x() << ":" << view_point.get_y() << ":" << view_point.get_z() << std::endl;
		std::cout << view_center_point.get_x() << ":" << view_center_point.get_y() << ":" << view_center_point.get_z() << std::endl;

	}
}