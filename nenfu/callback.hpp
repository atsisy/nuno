#pragma once

#include <functional>
#include "utility.hpp"
#include "nf_manager.hpp"

namespace nf
{
	/*
	* GlutCallBackクラス
	* GLUTのコールバック関数に登録するためのインターフェースの抽象クラス
	*/
	class GlutCallBack : public NFMChildren {

	public:
		
		GlutCallBack(nf::NFManager *nf_manager);
		virtual void run() = 0;

	};

	enum Camera3DPointType
	{
		VIEW_POINT,
		VIEW_CENTER_POINT,
		VIEW_UPPER_POINT,
		CAMERA_3DPOINT_TYPE_SIZE
	};

	class Camera {

	private:

		Point3D<double> view_point;
		Point3D<double> view_center_point;
		Point3D<double> view_upper_vector;


	public:

		Camera();
		~Camera();

		void look_from();

		void move(Camera3DPointType type, int x, int y, int z);
		void move(Camera3DPointType type, Point3D<double> point);

	};

	/*
	* DisplayCallBackクラス
	* 描画処理のコールバック処理の際、呼び出されるクラス
	*/
	class DisplayCallBack : public GlutCallBack {

	private:
		/*
		* 登録する予定の関数
		*/
		std::function<void(void)> target_function;
		Camera camera;

		void draw_grid();
		void look_from();

	public:

		DisplayCallBack(nf::NFManager *nf_manager);
		~DisplayCallBack();

		void move_camera(Camera3DPointType type, int x, int y, int z);
		void move_camera(Camera3DPointType type, Point3D<double> point);

		void run();

	};

	class IdleCallBack : public GlutCallBack {

	private:
		
		std::function<void(void)> target_function;


	public:

		IdleCallBack(nf::NFManager *nf_manager);
		~IdleCallBack();

		void run();

	};

	class GlutCallBackManager {

	private:

	public:
		void glut_register();

	};
}