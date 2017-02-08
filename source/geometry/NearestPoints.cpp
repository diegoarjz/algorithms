#include "NearestPoints.h"

#include <cmath>

#define NEAR_ZERO 0.000001

float nearest_points(const Line3 &P, const Line3 &Q, Vector3 &outPointOnL1, Vector3 &outPointOnL2){
    // Based on the algorithm on http://geomalgorithms.com/a07-_distance.html
    auto w0 = P.mPoint - Q.mPoint;
    auto a = dot(P.mDirection,P.mDirection);
    auto b = dot(P.mDirection,Q.mDirection);
    auto c = dot(Q.mDirection,Q.mDirection);
    auto d = dot(P.mDirection,w0);
    auto e = dot(Q.mDirection,w0);
    
    auto denominator = (a*c-b*b);
    
    // The lines are parallel
    if(denominator < NEAR_ZERO){
        auto Tc = e/b;
        
        outPointOnL1 = P.mPoint;
        outPointOnL2 = Q.mPoint + Tc*Q.mDirection;
    }
    else{
        auto invDenominator = 1/denominator;
        auto Sc = (b*e-c*d)*invDenominator;
        auto Tc = (a*e-b*d)*invDenominator;
        
        outPointOnL1 = P.mPoint + Sc*P.mDirection;
        outPointOnL2 = Q.mPoint + Tc*Q.mDirection;
    }
    
    return length( outPointOnL2-outPointOnL1 );
}

float nearest_points(const Segment3 &s1, const Segment3 &s2, Vector3 &outPointOnS1, Vector3 &outPointOnS2){
    // Based on the algorithm on http://geomalgorithms.com/a07-_distance.html
    Vector3 u = s1.mTarget - s1.mSource;
    Vector3 v = s2.mTarget - s2.mSource;
    Vector3 w = s1.mSource - s2.mSource;
    float a = dot(u,u);         // always >= 0
    float b = dot(u,v);
    float c = dot(v,v);         // always >= 0
    float d = dot(u,w);
    float e = dot(v,w);
    float D = a*c - b*b;        // always >= 0
    float sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
    float tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0
    
    // compute the line parameters of the two closest points
    if (D < NEAR_ZERO) { // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                 // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }
    
    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }
    else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-d + b) < 0.0)
            sN = 0;
        else if ((-d + b) > a)
            sN = sD;
        else {
            sN = (-d +  b);
            sD = a;
        }
    }
    // finally do the division to get sc and tc
    sc = (std::abs(sN) < NEAR_ZERO ? 0.0 : sN / sD);
    tc = (std::abs(tN) < NEAR_ZERO ? 0.0 : tN / tD);
    
    outPointOnS1 = s1.mSource + sc*u;
    outPointOnS2 = s2.mSource + tc*v;
    
    // get the difference of the two closest points
    Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)
    
    return length(dP);   // return the closest distance
}
float nearest_points(const Segment3 &s, const Ray3 &r, Vector3 &outPointOnSegment, Vector3 &outPointOnRay){
    // Based on the algorithm on http://geomalgorithms.com/a07-_distance.html
    Vector3 u = s.mTarget - s.mSource;
    Vector3 v = r.mDirection;
    Vector3 w = s.mSource - r.mOrigin;
    float a = dot(u,u);         // always >= 0
    float b = dot(u,v);
    float c = dot(v,v);         // always >= 0
    float d = dot(u,w);
    float e = dot(v,w);
    float D = a*c - b*b;        // always >= 0
    float sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
    float tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0
    
    // compute the line parameters of the two closest points
    if (D < NEAR_ZERO) { // the lines are almost parallel
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = e;
        tD = c;
    }
    else {                 // get the closest points on the infinite lines
        sN = (b*e - c*d);
        tN = (a*e - b*d);
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e;
            tD = c;
        }
        else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = e + b;
            tD = c;
        }
    }
    
    if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-d < 0.0)
            sN = 0.0;
        else if (-d > a)
            sN = sD;
        else {
            sN = -d;
            sD = a;
        }
    }

    // finally do the division to get sc and tc
    sc = (std::abs(sN) < NEAR_ZERO ? 0.0 : sN / sD);
    tc = (std::abs(tN) < NEAR_ZERO ? 0.0 : tN / tD);
    
    outPointOnSegment = s.mSource + sc*u;
    outPointOnRay = r.mOrigin + tc*v;
    
    // get the difference of the two closest points
    Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)
    
    return length(dP);   // return the closest distance
}
