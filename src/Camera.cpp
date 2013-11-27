
#include "Camera.h"

Camera::Camera()
{
	e				= new Vector4(0,0,-1);
	d				= new Vector4(0,0,0);
	up				= new Vector4(0,1,0);
	camMat			= new Matrix4();
	inverseCamMat	= new Matrix4();

	generateCameraMatrix();
}

Camera::Camera(Vector4* eR, Vector4* dR, Vector4* upR)
{
	e		= eR;
	d		= dR;
	up		= upR;
	camMat			= new Matrix4();
	inverseCamMat	= new Matrix4();
	generateCameraMatrix();
}

void Camera::setE(Vector4* eP)
{
	e = eP;
	generateCameraMatrix();
}

void Camera::setD(Vector4* dP)
{
	d = dP;
	generateCameraMatrix();
}

void Camera::setUp(Vector4* upP)
{
	up = upP;
	generateCameraMatrix();
}

void Camera::generateCameraMatrix()
{
	Vector4 zAx;
	zAx = (*e)-(*d);
	zAx.normalize();

	Vector4 xAx = up->crossProduct(zAx);
	xAx.normalize();

	Vector4 yAx = zAx.crossProduct(xAx);

	camMat->setAll
	(
		xAx.get(v_x_coord),	yAx.get(v_x_coord),	zAx.get(v_x_coord),	e->get(v_x_coord),
		xAx.get(v_y_coord),	yAx.get(v_y_coord),	zAx.get(v_y_coord),	e->get(v_y_coord),
		xAx.get(v_z_coord),	yAx.get(v_z_coord),	zAx.get(v_z_coord),	e->get(v_z_coord),
		0,						0,						0,						1
	);
	inverseCamMat->setAll //C inverse = T inverse times R transpose
	(
		camMat->get(0,0),	camMat->get(0,1),	camMat->get(0,2),	0,
		camMat->get(1,0),	camMat->get(1,1),	camMat->get(1,2),	0,
		camMat->get(2,0),	camMat->get(2,1),	camMat->get(2,2),	0,
		0,					0,					0,					1
	);
	double transX = (camMat->get(3,0));
	double transY = (camMat->get(3,1));
	double transZ = (camMat->get(3,2));
	Matrix4 rotMatInvs = Matrix4
	(
		1,	0,	0,	-transX,
		0,	1,	0,	-transY,
		0,	0,	1,	-transZ,
		0,	0,	0,	1
	);
	inverseCamMat->multiply(rotMatInvs);
}

void Camera::generateInverseCameraMatrix()
{
	inverseCamMat->setAll //C inverse = T inverse times R transpose
	(
		camMat->get(0,0),	camMat->get(0,1),	camMat->get(0,2),	0,
		camMat->get(1,0),	camMat->get(1,1),	camMat->get(1,2),	0,
		camMat->get(2,0),	camMat->get(2,1),	camMat->get(2,2),	0,
		0,					0,					0,					1
	);
	Matrix4 rotMatInvs = Matrix4
	(
		1,	0,	0,	-camMat->get(3,0),
		0,	1,	0,	-camMat->get(3,1),
		0,	0,	1,	-camMat->get(3,2),
		0,	0,	0,	1
	);
	inverseCamMat->multiply(rotMatInvs);
}

Matrix4* Camera::getCameraMatrix()
{
	generateCameraMatrix();
	return camMat;
}

Matrix4* Camera::getCameraMatrixInverse()
{
	generateInverseCameraMatrix();
	return inverseCamMat;
}

