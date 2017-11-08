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

	glutInit(&argc, argv);//���̏�����

	glutInitWindowPosition(250, 250);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(600, 600); //�E�B���h�E�T�C�Y�̎w��

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(MAIN_WINDOW_NAME);  //�E�B���h�E�̍쐬

	nf::GlutCallBackManager manager;
	manager.glut_register();

	Initialize();

	register_glut_call_back();

	glutMainLoop();

	return 0;
}

void Initialize(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);//�f�v�X�o�b�t�@���g�p�FglutInitDisplayMode() �� GLUT_DEPTH ���w�肷��

	nf_manager = new nf::NFManager;

	gluPerspective(30.0, (double)600 / (double)600, 0.1, 1000.0); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
	gluLookAt(
		0.0, -700.0, 150.0, // ���_�̈ʒux,y,z;
		0.0, 100.0, 0.0,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		0.0, 0.0, 1.0);  //���E�̏�����̃x�N�g��x,y,z
}