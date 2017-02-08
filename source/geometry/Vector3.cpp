#include "Vector3.h"

#include <cmath>

float dot(const Vector3 &v1, const Vector3 &v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

float length(const Vector3 &v){
    return std::sqrt( v.x*v.x + v.y*v.y + v.z*v.z );
}

Vector3 normalized(const Vector3 &v){
    auto l = 1/length(v);
    return Vector3{v.x*l, v.y*l, v.z*l};
}

Vector3 operator+(const Vector3 &v1, const Vector3 &v2){
    return {
        v2.x+v1.x,
        v2.y+v1.y,
        v2.z+v1.z
    };
}

Vector3 operator-(const Vector3 &v1, const Vector3 &v2){
    return {
        v1.x-v2.x,
        v1.y-v2.y,
        v1.z-v2.z
    };
}

Vector3 operator*(const float &scalar, const Vector3 &v){
    return {
        scalar*v.x,
        scalar*v.y,
        scalar*v.z,
    };
}

bool operator==(const Vector3 &v1, const Vector3 &v2){
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}
