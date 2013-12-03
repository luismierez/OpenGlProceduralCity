#ifndef _MATRIX4_H_
#define _MATRIX4_H_
#include "Vector3.h"
#include "Vector4.h"
#include "VectCoordEnum.h"

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    ~Matrix4();
    double* getPointer();  // return pointer to matrix elements
	double get(int x, int y);
    void setAll(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);

	void identity();  // create identity matrix
	
	Matrix4 multiply(Matrix4& other);
	Vector4 multiply(Vector4& other);

	void rotateX(double angle);					// rotation about x axis
    void rotateY(double angle);					// rotation about y axis
	void rotateZ(double angle);					// rotation about z axis
    Matrix4 rotate(Vector3& axis, double angle);	// rotation about arbitrary axis

	void scalingMat(double x, double y, double z);		//creates a scaling matrix
	void translationMat(double x, double y, double z);	//creates a translation matrix
	void transpose();	//Transposes the matrix
	void homogenize();
    
    void invert();

	void print();
    
    Matrix4 trackballRotation(int width, int height, int fromX, int fromY, int toX, int toY);
    void copyRot(Matrix4*);
};

#endif