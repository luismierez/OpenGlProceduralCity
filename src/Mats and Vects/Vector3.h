/*
 *  Vector3.h
 *  Project 1
 *
 *  Created by Grady Kestler on 9/28/13.
 *
 */

#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <math.h>
#include "VectCoordEnum.h"

class Vector3
{
public:
    double v[3];   // vector elements
    
public:
    Vector3();        // constructor
    Vector3(double, double, double);
    double* getPointer();  // return pointer to vector elements
	void set(double, double, double); // set the vector elements
    void set(VectorCoord, double);
	double get(VectorCoord); // get specific vector element

	double operator[](int);

	void add(Vector3&);
	Vector3* operator+(Vector3&);
	void subtract(Vector3&);
	Vector3* operator-(Vector3&);

	void negate();
	void scale(double, double, double);
    void scalarDivide(double);
	double dotProduct(Vector3&);
	Vector3* crossProduct(Vector3&);
	double magnitude();
	void normalize();
    double angle(Vector3&);
    
	void print();
};

#endif