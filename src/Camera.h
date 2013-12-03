#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Vector3.h"
#include "Vector4.h"
#include "VectCoordEnum.h"
#include "Matrix4.h"

class Camera
{
public:
    Camera();        // constructor
    Camera(Vector4* e, Vector4* d, Vector4* up);
    
    Matrix4* getCameraMatrix();
    Matrix4* getCameraMatrixInverse();
    
    void setE(Vector4* eP);
    void setD(Vector4* dP);
    void setUp(Vector4* upP);
    
    void print();
private:
    void generateCameraMatrix();
    void generateInverseCameraMatrix();
    
    Vector4* e;                                        //Origin of camera
    Vector4* d;                                        //Look at point
    Vector4* up;                                //Vector which determines camera tilt
    Matrix4* camMat;                        //Camera matrix generated as a result of the vector values
    Matrix4* inverseCamMat;                //Inverted CM
};

#endif