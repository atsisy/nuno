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
		};
	}

	DisplayCallBack::~DisplayCallBack()
	{}

	void DisplayCallBack::camera_rotate(double angle, double x, double y, double z)
	{
		camera.rotate(angle, x, y, z);
	}

	void DisplayCallBack::camera_translate(double x, double y, double z)
	{
		camera.translate(x, y, z);
	}

	void DisplayCallBack::run()
	{
		target_function();
	}

	Camera::Camera()
	{}

	Camera::~Camera()
	{}


	void Camera::rotate(double angle, double x, double y, double z)
	{
		glRotated(angle, x, y, z);
	}

	void Camera::translate(double x, double y, double z)
	{
		glTranslated(x, y, z);
	}

}