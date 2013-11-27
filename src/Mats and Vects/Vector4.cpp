#include "Vector4.h"
#include <math.h>
#include <cstdio>

Vector4::Vector4()
{
	for (int i=0; i<4; ++i)
	{
		v[i] = 0;
	}
} 
Vector4::Vector4(double x, double y, double z, double w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

double* Vector4::getPointer()
{
	return v;
}

void Vector4::set(double x, double y, double z, double w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

double Vector4::get(VectorCoord index)
{
	switch (index) {
		case v_x_coord:
			return v[0];
		case v_y_coord:
			return v[1];
		case v_z_coord:
			return v[2];
		case v_w_coord:
			return v[3];
		default:
			break;
	}
	return -1;
}

double Vector4::operator[](int index)
{
	return get((VectorCoord) index);
}

void Vector4::add(Vector4& vect)
{
	v[0]+=vect[0];
	v[1]+=vect[1];
	v[2]+=vect[2];
	v[3]+=vect[3];
}

Vector4* Vector4::operator+(Vector4& vect)
{
	return new Vector4(v[0]+vect[0],
					   v[1]+vect[1],
					   v[2]+vect[2],
					   v[3]+vect[3]);	
}

void Vector4::subtract(Vector4& vect)
{
	vect.negate();
	add(vect);
	vect.negate();
}

Vector4* Vector4::operator-(Vector4& vect)
{
	return new Vector4(v[0]-vect[0],
					   v[1]-vect[1],
					   v[2]-vect[2],
					   v[3]-vect[3]);
}

void Vector4::negate()
{
	v[0]=-v[0];
	v[1]=-v[1];
	v[2]=-v[2];
	v[3]=-v[3];
}

void Vector4::dehomogenize()
{
	v[0] /= v[3];
	v[1] /= v[3];
	v[2] /= v[3];
	v[3] /= v[3];
}

double Vector4::magnitude()
{
	return sqrt(v[0]*v[0]+
				v[1]*v[1]+
				v[2]*v[2]+
                v[3]*v[3]);
}


void Vector4::normalize()
{
	double mag=magnitude();
	v[0]=v[0]/mag;
	v[1]=v[1]/mag;
	v[2]=v[2]/mag;
    v[3]=v[3]/mag;
}

void Vector4::print()
{
	printf("Vector4 Coords: x: %f | y: %f | z: %f | w: %f\n", v[v_x_coord], v[v_y_coord], v[v_z_coord], v[v_w_coord]);
}