#pragma once

#include <string>
#include <GL/glut.h>
#include <vector>
#include "utility.hpp"

namespace nf
{

	class NObject {

	protected:

		std::string object_name;
		unsigned int object_id;


	public:

		NObject();
		~NObject();

		virtual void motion() = 0;

	};

	class N2DObject : public NObject {

	private:

		std::vector<Point2D<GLdouble>> point_data;


	public:

		void motion();
	};

}