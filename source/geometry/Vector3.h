#ifndef Algorithms_Vector3_H_
#define Algorithms_Vector3_H_

struct Vector3{
    float x;
    float y;
    float z;
}; // struct Vector3

float dot(const Vector3 &v1, const Vector3 &v2);
float length(const Vector3 &v);
Vector3 normalized(const Vector3 &v);

Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
Vector3 operator*(const float &scalar, const Vector3 &v);
bool operator==(const Vector3 &v1, const Vector3 &v2);

#endif
