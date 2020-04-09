#ifndef VECTOR_H_
#define VECTOR_H_
#include<iostream>

namespace VECTOR
{
	class Vector
	{
	public:
		enum Mode{RECT, POL};
	private:
		double x;
		double y;
		double mag;
		double ang;
		Mode mode;

		void set_mag();
		void set_ang();
		void set_x();
		void set_y();
	public:
		Vector
	};
}
#endif // !VECTOR_H_
