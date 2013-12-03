/*
 *  Vector3.cpp
 *  Project 1
 *
 *  Created by Grady Kestler on 9/28/13.
 *
 */

#include "Vector3.h"
#include <math.h>
#include <cstdio>

Vector3::Vector3()
{
	for (int i=0; i<3; ++i)
	{
		v[i] = 0;
	}
} 
Vector3::Vector3(double v0, double v1, double v2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
}

double* Vector3::getPointer()
{
	return &v[0];
}

void Vector3::set(double newX, double newY, double newZ)
{
	v[0] = newX;
	v[1] = newY;
	v[2] = newZ;
}

void Vector3::set(VectorCoord index, double newValue)
{
    switch (index) {
        case v_x_coord:
            v[0]=newValue;
            break;
        case v_y_coord:
            v[1]=newValue;
            break;
        case v_z_coord:
            v[2]=newValue;
            break;
        default:
            break;
    }
    
}

double Vector3::get(VectorCoord index)
{
	switch (index) {
		case v_x_coord:
			return v[0];
			break;
		case v_y_coord:
			return v[1];
			break;
		case v_z_coord:
			return v[2];
			break;
		default:
			break;
	}
	return -1;
}

double Vector3::operator[](int index)
{
	return get((VectorCoord) index);
}

void Vector3::add(Vector3& vect)
{
	v[0]+=vect[0];
	v[1]+=vect[1];
	v[2]+=vect[2];
}

Vector3* Vector3::operator+(Vector3& vect)
{
	return new Vector3(v[0]+vect[0],
					   v[1]+vect[1],
					   v[2]+vect[2]);	
}

void Vector3::subtract(Vector3& vect)
{
	vect.negate();
	add(vect);
	vect.negate();
}

Vector3* Vector3::operator-(Vector3& vect)
{
	return new Vector3(v[0]-vect[0],
					   v[1]-vect[1],
					   v[2]-vect[2]);
}

void Vector3::negate()
{
	v[0]=-v[0];
	v[1]=-v[1];
	v[2]=-v[2];
}

void Vector3::scale(double x_scale, double y_scale, double z_scale)
{
	v[0]*=x_scale;
	v[1]*=y_scale;
	v[2]*=z_scale;
}

void Vector3::scalarDivide(double scalar)
{
    if(scalar == 0){
        printf("Cannot divide by zero");
    }
    else{
        v[0] = v[0]/scalar,
        v[1] = v[1]/scalar,
        v[2] = v[2]/scalar;
    }
}

double Vector3::dotProduct(Vector3& vect)
{
	return v[0]*vect[0]+
	v[1]*vect[1]+
	v[2]*vect[2];
}

Vector3* Vector3::crossProduct(Vector3& vect)
{
	return new Vector3(v[1]*vect[2]-v[2]*vect[1],
					   v[2]*vect[0]-v[0]*vect[2],
					   v[0]*vect[1]-v[1]*vect[0]);
}

double Vector3::magnitude()
{
	return sqrt(v[0]*v[0]+
				v[1]*v[1]+
				v[2]*v[2]);
}

void Vector3::normalize()
{
	double mag=magnitude();
	v[0]=v[0]/mag;
	v[1]=v[1]/mag;
	v[2]=v[2]/mag;
}

double Vector3::angle(Vector3& vect)
{
    double dotProd = v[0]*vect[0]+
                    v[1]*vect[1]+
                    v[2]*vect[2];
    
    double magA = sqrt(v[0]*v[0]+
                        v[1]*v[1]+
                        v[2]*v[2]);
    
    double magB = sqrt(vect[0]*vect[0]+
                       vect[1]*vect[1]+
                       vect[2]*vect[2]);
    
    double cosTheta = (dotProd/(magA*magB));
    
    double theta = acos(cosTheta);
    
    return theta;
}

void Vector3::print()
{
	printf("Vector3 Coords: x: %f | y: %f | z: %f\n", v[v_x_coord], v[v_y_coord], v[v_z_coord]);
}


