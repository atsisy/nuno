#include "callback.hpp"
#include <GL/glut.h>

namespace nf {

	IdleCallBack::IdleCallBack(nf::NFManager *nf_manager)
		: GlutCallBack(nf_manager)
	{
		target_function = []()
		{};
	}

	IdleCallBack::~IdleCallBack()
	{}

	void IdleCallBack::run()
	{
		target_function();
	}

}