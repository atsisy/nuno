#include <GL/glut.h>
#include "core.hpp"
#include "callback.hpp"
#include "device_tracker.hpp"
#include "nf_manager.hpp"

nf::NFManager *nf_manager;

void register_glut_call_back();
void Initialize(void);

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);//環境の初期化

	glutInitWindowPosition(250, 250);//ウィンドウの位置の指定
	glutInitWindowSize(600, 600); //ウィンドウサイズの指定

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(MAIN_WINDOW_NAME);  //ウィンドウの作成

	nf::GlutCallBackManager manager;
	manager.glut_register();

	Initialize();

	register_glut_call_back();

	glutMainLoop();

	return 0;
}

void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

	nf_manager = new nf::NFManager;

	gluPerspective(30.0, (double)600 / (double)600, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);
	gluLookAt(
		0.0, -700.0, 150.0, // 視点の位置x,y,z;
		0.0, 100.0, 0.0,   // 視界の中心位置の参照点座標x,y,z
		0.0, 0.0, 1.0);  //視界の上方向のベクトルx,y,z
}