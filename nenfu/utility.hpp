#pragma once

namespace nf
{

	template <typename T>
	class Point3D {

	protected:
		T x;
		T y;
		T z;

	public:

		Point3D(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Point3D()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		~Point3D()
		{}

		T get_x() const
		{
			return x;
		}

		T get_y() const
		{
			return y;
		}

		T get_z() const
		{
			return z;
		}

		void operator +=(const Point3D<T> &value)
		{
			this->x += value.x;
			this->y += value.y;
			this->z += value.z;
		}

		void operator -=(const Point3D<T> &value)
		{
			this->x -= value.x;
			this->y -= value.y;
			this->z -= value.z;
		}

		explicit operator Point3D<double>() const
		{
			return Point3D<double>((double)this->x, (double)this->y, (double)this->z);
		}

		Point3D<T> operator +(const Point3D<T> &value)
		{
			return Point3D<T>(this->x + value.x, this->y + value.y, this->z + value.z);
		}

		Point3D<T> operator -(const Point3D<T> &value)
		{
			return Point3D<T>(this->x - value.x, this->y - value.y, this->z - value.z);
		}
	};

	template <typename T>
	class Point2D : public Point3D<T> {
		
	private:

	public:

		Point2D(T x, T y)
			: Point3D(x, y, 0){}

		Point2D()
			: Point3D(x, y, 0){}

		~Point2D()
		{}

	};

}