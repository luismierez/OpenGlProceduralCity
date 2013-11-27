#ifndef _VECTOR4_H_
#define _VECTOR4_H_
#include "VectCoordEnum.h"

class Vector4
{
protected:
    double v[4];   // vector elements
    
public:
    Vector4();        // constructor
    Vector4(double x, double y, double z);
	Vector4(double x, double y, double z, double w);
    double* getPointer();  // return pointer to vector elements
	void set(double, double, double, double); // set the vector elements
	double get(VectorCoord); // get specific vector element

	double operator[](int);

	void add(Vector4&);
	Vector4* operator+(Vector4&);
	void subtract(Vector4&);
	Vector4* operator-(Vector4&);

	void dehomogenize();
    void normalize();
    double magnitude();

	void negate();
	void print();
};

#endif