#ifndef Algorithms_NearestPoints_H_
#define Algorithms_NearestPoints_H_

#include "Ray3.h"
#include "Segment3.h"
#include "Vector3.h"
#include "Line3.h"

float nearest_points(const Line3 &P, const Line3 &Q, Vector3 &outPointOnL1, Vector3 &outPointOnL2);
float nearest_points(const Segment3 &s1, const Segment3 &s2, Vector3 &outPointOnS1, Vector3 &outPointOnS2);
float nearest_points(const Segment3 &segment, const Ray3 &ray, Vector3 &outPointOnSegment, Vector3 &outPointOnRay);

#endif
