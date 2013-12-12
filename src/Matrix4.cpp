#define _USE_MATH_DEFINES
#include <math.h>

#include "Matrix4.h"
#include <cstdio>

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 
Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

Matrix4::~Matrix4()
{

}

void Matrix4::setAll(
                     double m00, double m10, double m20, double m30,
                     double m01, double m11, double m21, double m31,
                     double m02, double m12, double m22, double m32,
                     double m03, double m13, double m23, double m33 )
{
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30; 
    m[3][1] = m31; 
    m[3][2] = m32; 
    m[3][3] = m33; 
}

double Matrix4::get(int x, int y)
{
	return m[x][y];
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

Matrix4 Matrix4::multiply(Matrix4& other)
{
	double newM[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
	for(int ii = 0; ii < 4; ii++)
	{
		for(int jj = 0; jj < 4; jj++)
		{
			for(int kk = 0; kk < 4; kk++)
			{
				newM[ii][jj] += m[kk][jj] * other.m[ii][kk];
			}
		}
	}
    
    Matrix4 retMat = Matrix4(newM[0][0], newM[0][1], newM[0][2], newM[0][3],
                                 newM[1][0], newM[1][1], newM[1][2], newM[1][3],
                                 newM[2][0], newM[2][1], newM[2][2], newM[2][3],
                                 newM[3][0], newM[3][1], newM[3][2], newM[3][3]);
    return retMat;
//	for (int i=0; i<4; ++i)
//	{
//		for (int j=0; j<4; ++j)
//		{
//		  m[i][j] = newM[i][j];
//		}
//	}
}

void Matrix4::homogenize()
{
	for(int ii = 0; ii < 4; ii++)
	{
		for(int jj = 0; jj < 4; jj++)
		{
			m[ii][jj] /= m[3][3];
		}
	}
}

Vector4 Matrix4::multiply(Vector4& other)
{
	double v[4];
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
	for(int ii = 0; ii < 4; ii++)
	{
		for(int jj = 0; jj < 4 ; jj++)
		{
			v[ii] += m[ii][jj] * other[jj];
		}
	}
	return Vector4(v[0],v[1],v[2],v[3]);
}

// angle in radians
void Matrix4::rotateX(double angle)
{
	angle = (angle/180.0) * M_PI;

	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = -sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}
// angle in radians
void Matrix4::rotateY(double angle)
{
    angle = (angle/180.0) * M_PI;

	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}
// angle in radians
void Matrix4::rotateZ(double angle)
{
    angle = (angle/180.0) * M_PI;
	m[0][0] = cos(angle);
	m[0][1] = sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = -sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

Matrix4 Matrix4::rotate(Vector3& axis, double angle)
{
	double cTheta = cos(angle);
	double sTheta = sin(angle);
	double ax = axis[v_x_coord];
	double ay = axis[v_y_coord];
	double az = axis[v_z_coord];
    double t[4][4];

	t[0][0] = pow(ax,2) + cTheta*(1-pow(ax,2));
	t[0][1] = ax*ay*(1-cTheta) + az*sTheta;
	t[0][2] = ax*az*(1-cTheta) - ay*sTheta;
	t[0][3] = 0;
	t[1][0] = ax*ay*(1-cTheta) - az * sTheta;
	t[1][1] = pow(ay,2) + cTheta*(1-pow(ay,2));
	t[1][2] = ay*az*(1-cTheta) + ax*sTheta;
	t[1][3] = 0;
	t[2][0] = ax*az*(1-cTheta) + ay*sTheta;
	t[2][1] = ay*az*(1-cTheta)-ax*sTheta;
	t[2][2] = pow(az,2) + cTheta*(1-pow(az,2));
	t[2][3] = 0;
	t[3][0] = 0;
	t[3][1] = 0;
    t[3][2] = 0;
	t[3][3] = 1;
    
    return Matrix4(t[0][0], t[0][1], t[0][2], t[0][3],
                   t[1][0], t[1][1], t[1][2], t[1][3],
                   t[2][0], t[2][1], t[2][2], t[2][3],
                   t[3][0], t[3][1], t[3][2], t[3][3]);
}

void Matrix4::scalingMat(double x, double y, double z)
{
	m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void Matrix4::translationMat(double x, double y, double z)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	m[3][3] = 1;
}

void Matrix4::transpose()
{
	double temp;
	for(int ii = 3; ii >= 0; ii--)
	{
		for(int jj = ii-1; jj >=0; jj--)
		{
			temp = m[ii][jj];
			m[ii][jj] = m[jj][ii];
			m[jj][ii] = temp;
		}
	}
}

void Matrix4::invert()
{
    double det = m[0][0]*m[1][1]*m[2][2]*m[3][3]+m[0][0]*m[1][2]*m[2][3]*m[3][1]+m[0][0]*m[1][3]*m[2][1]*m[3][2]
    +m[0][1]*m[1][0]*m[2][3]*m[3][2]+m[0][1]*m[1][2]*m[2][0]*m[3][3]+m[0][1]*m[1][3]*m[2][2]*m[3][0]
    +m[0][2]*m[1][0]*m[2][1]*m[3][3]+m[0][2]*m[1][1]*m[2][3]*m[3][0]+m[0][2]*m[1][3]*m[2][0]*m[3][1]
    +m[0][3]*m[1][0]*m[2][2]*m[3][1]+m[0][3]*m[1][1]*m[2][0]*m[3][2]+m[0][3]*m[1][2]*m[2][1]*m[3][0]
    -m[0][0]*m[1][1]*m[2][3]*m[3][2]-m[0][0]*m[1][2]*m[2][1]*m[3][3]-m[0][0]*m[1][3]*m[2][2]*m[3][1]
    -m[0][1]*m[1][0]*m[2][2]*m[3][3]-m[0][1]*m[1][2]*m[2][3]*m[3][0]-m[0][1]*m[1][3]*m[2][0]*m[3][2]
    -m[0][2]*m[1][0]*m[2][3]*m[3][1]-m[0][2]*m[1][1]*m[2][0]*m[3][3]-m[0][2]*m[1][3]*m[2][1]*m[3][0]
    -m[0][3]*m[1][0]*m[2][1]*m[3][2]-m[0][3]*m[1][1]*m[2][2]*m[3][0]-m[0][3]*m[1][2]*m[2][0]*m[3][1];
    double b[4][4];
    b[0][0] = m[1][1]*m[2][2]*m[3][3]+m[1][2]*m[2][3]*m[3][1]+m[1][3]*m[2][1]*m[3][2]-m[1][1]*m[2][3]*m[3][2]-m[1][2]*m[2][1]*m[3][3]-m[1][3]*m[2][2]*m[3][1];
    b[0][1] = m[0][1]*m[2][3]*m[3][2]+m[0][2]*m[2][1]*m[3][3]+m[0][3]*m[2][2]*m[3][1]-m[0][1]*m[2][2]*m[3][3]-m[0][2]*m[2][3]*m[3][1]-m[0][3]*m[2][1]*m[3][2];
    b[0][2] = m[0][1]*m[1][2]*m[3][3]+m[0][2]*m[1][3]*m[3][1]+m[0][3]*m[1][1]*m[3][2]-m[0][1]*m[1][3]*m[3][2]-m[0][2]*m[1][1]*m[3][3]-m[0][3]*m[1][2]*m[3][1];
    b[0][3] = m[0][1]*m[1][3]*m[2][2]+m[0][2]*m[1][1]*m[2][3]+m[0][3]*m[1][2]*m[2][1]-m[0][1]*m[1][2]*m[2][3]-m[0][2]*m[1][3]*m[2][1]-m[0][3]*m[1][1]*m[2][2];
    b[1][0] = m[1][0]*m[2][3]*m[3][2]+m[1][2]*m[2][0]*m[3][3]+m[1][3]*m[2][2]*m[3][0]-m[1][0]*m[2][2]*m[3][3]-m[1][2]*m[2][3]*m[3][0]-m[1][3]*m[2][0]*m[3][2];
    b[1][1] = m[0][0]*m[2][2]*m[3][3]+m[0][2]*m[2][3]*m[3][0]+m[0][3]*m[2][0]*m[3][2]-m[0][0]*m[2][3]*m[3][2]-m[0][2]*m[2][0]*m[3][3]-m[0][3]*m[2][2]*m[3][0];
    b[1][2] = m[0][0]*m[1][3]*m[3][2]+m[0][2]*m[1][0]*m[3][3]+m[0][3]*m[1][2]*m[3][0]-m[0][0]*m[1][2]*m[3][3]-m[0][2]*m[1][3]*m[3][0]-m[0][3]*m[1][0]*m[3][2];
    b[1][3] = m[0][0]*m[1][2]*m[2][3]+m[0][2]*m[1][3]*m[2][0]+m[0][3]*m[1][0]*m[2][2]-m[0][0]*m[1][3]*m[2][2]-m[0][2]*m[1][0]*m[2][3]-m[0][3]*m[1][2]*m[2][0];
    b[2][0] = m[1][0]*m[2][1]*m[3][3]+m[1][1]*m[2][3]*m[3][0]+m[1][3]*m[2][0]*m[3][1]-m[1][0]*m[2][3]*m[3][1]-m[1][1]*m[2][0]*m[3][3]-m[1][3]*m[2][1]*m[3][0];
    b[2][1] = m[0][0]*m[2][3]*m[3][1]+m[0][1]*m[2][0]*m[3][3]+m[0][3]*m[2][1]*m[3][0]-m[0][0]*m[2][1]*m[3][3]-m[0][1]*m[2][3]*m[3][0]-m[0][3]*m[2][0]*m[3][1];
    b[2][2] = m[0][0]*m[1][1]*m[3][3]+m[0][1]*m[1][3]*m[3][0]+m[0][3]*m[1][0]*m[3][1]-m[0][0]*m[1][3]*m[3][1]-m[0][1]*m[1][0]*m[3][3]-m[0][3]*m[1][1]*m[3][0];
    b[2][3] = m[0][0]*m[1][3]*m[2][1]+m[0][1]*m[1][0]*m[2][3]+m[0][3]*m[1][1]*m[2][0]-m[0][0]*m[1][1]*m[2][3]-m[0][1]*m[1][3]*m[2][0]-m[0][3]*m[1][0]*m[2][1];
    b[3][0] = m[1][0]*m[2][2]*m[3][1]+m[1][1]*m[2][0]*m[3][2]+m[1][2]*m[2][1]*m[3][0]-m[1][0]*m[2][1]*m[3][2]-m[1][1]*m[2][2]*m[3][0]-m[1][2]*m[2][0]*m[3][1];
    b[3][1] = m[0][0]*m[2][1]*m[3][2]+m[0][1]*m[2][2]*m[3][0]+m[0][2]*m[2][0]*m[3][1]-m[0][0]*m[2][2]*m[3][1]-m[0][1]*m[2][0]*m[3][2]-m[0][2]*m[2][1]*m[3][0];
    b[3][2] = m[0][0]*m[1][2]*m[3][1]+m[0][1]*m[1][0]*m[3][2]+m[0][2]*m[1][1]*m[3][0]-m[0][0]*m[1][1]*m[3][2]-m[0][1]*m[1][2]*m[3][0]-m[0][2]*m[1][0]*m[3][1];
    b[3][3] = m[0][0]*m[1][1]*m[2][2]+m[0][1]*m[1][2]*m[2][0]+m[0][2]*m[1][0]*m[2][1]-m[0][0]*m[1][2]*m[2][1]-m[0][1]*m[1][0]*m[2][2]-m[0][2]*m[1][1]*m[2][0];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            m[i][j] = b[i][j]/det;
}

void Matrix4::print()
{
	printf("Matrix4:\n \
			%f %f %f %f\n \
			%f %f %f %f\n \
			%f %f %f %f\n \
			%f %f %f %f\n ",
			m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3]);
}

/** Rotates the matrix according to a fictitious trackball, placed in
 the middle of the given window.
 The trackball is approximated by a Gaussian curve.
 The trackball coordinate system is: x=right, y=up, z=to viewer<BR>
 The origin of the mouse coordinates zero (0,0) is considered to be top left.
 @param width, height  window size in pixels
 @param fromX, fromY   mouse starting position in pixels
 @param toX, toY       mouse end position in pixels
 */
Matrix4 Matrix4::trackballRotation(int width, int height, int fromX, int fromY, int toX, int toY)
{
    const float TRACKBALL_SIZE = 1.3f;              // virtual trackball size (empirical value)
    Matrix4 mInv;                                   // inverse of ObjectView matrix
    Vector3 v1, v2;                                 // mouse drag positions in normalized 3D space
    float smallSize;                                // smaller window size between width and height
    float halfWidth, halfHeight;                    // half window sizes
    float angle;                                    // rotational angle
    float d;                                        // distance
    
    // Compute mouse coordinates in window and normalized to -1..1
    // ((0,0)=window center, (-1,-1) = bottom left, (1,1) = top right)
    halfWidth   = (float)width  / 2.0f;
    halfHeight  = (float)height / 2.0f;
    smallSize   = (halfWidth < halfHeight) ? halfWidth : halfHeight;
    v1.set(v_x_coord,((float)fromX - halfWidth)  / smallSize);
    v1.set(v_y_coord,((float)(height-fromY) - halfHeight) / smallSize);
    v2.set(v_x_coord,((float)toX   - halfWidth)  / smallSize);
    v2.set(v_y_coord,((float)(height-toY)   - halfHeight) / smallSize);
    
    // Compute z-coordinates on Gaussian trackball:
    d       = sqrtf(v1[0] * v1[0] + v1[1] * v1[1]);
    v1.set(v_z_coord, expf(-TRACKBALL_SIZE * d * d));
    d       = sqrtf(v2[0] * v2[0] + v2[1] * v2[1]);
    v2.set(v_z_coord,expf(-TRACKBALL_SIZE * d * d));
    
    // Compute rotational angle:
    angle = v1.angle(v2);                          // angle = angle between v1 and v2
    //printf("%f\n", angle);
    
    // Compute rotational axis:
    Vector3* crossProdAxis;
    crossProdAxis = v2.crossProduct(v1);                                  // v2 = v2 x v1 (cross product)
    
    Vector4 tmp = Vector4(crossProdAxis->get(v_x_coord), crossProdAxis->get(v_y_coord), crossProdAxis->get(v_z_coord), 0);
    
    // Convert axis coordinates (v2) from WCS to OCS:
    mInv.identity();
    
    mInv.copyRot(this);                             // copy rotational part of mv to mInv
    
//    mInv.invert();
    //mInv.invertOrtho();                             // invert orthogonal matrix mInv
    Vector4 tmp2 = mInv.multiply(tmp);               // v2 = v2 x mInv (matrix multiplication)
    Vector3 tmp3 = Vector3(tmp2.get(v_x_coord), tmp2.get(v_y_coord), tmp2.get(v_z_coord));
    tmp3.normalize();                                 // normalize v2 before rotation
    
    // Perform acutal model view matrix modification:
    Matrix4 rotMat;
    rotMat = rotate(tmp3, -angle);
    //rotMat.invert();
    return rotate(tmp3, -angle);      // rotate model view matrix
}

void Matrix4::copyRot(Matrix4* mat)
{
    m[0][0] = mat->get(0, 0);
    m[0][1] = mat->get(0, 1);
    m[0][2] = mat->get(0, 2);
    m[1][0] = mat->get(1, 0);
    m[1][1] = mat->get(1, 1);
    m[1][2] = mat->get(1, 2);
    m[2][0] = mat->get(2, 0);
    m[2][1] = mat->get(2, 1);
    m[2][2] = mat->get(2, 2);
}

