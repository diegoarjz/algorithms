#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE NearestPoints

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>

#include <Timer.h>

#include "../Line3.h"
#include "../NearestPoints.h"

/*
 * Line to line nearest points
 */
BOOST_AUTO_TEST_CASE(test_line_distance_intersect){
    Line3 l1{ {0,0,0}, {1,0,0} };
    Line3 l2{ {0,0,0}, {0,1,0} };
    
    Vector3 l1Point, l2Point;
    
    auto distance = nearest_points(l1, l2, l1Point, l2Point);
    
    BOOST_CHECK(distance == 0);
    BOOST_CHECK( l1Point == Vector3({0,0,0}) );
    BOOST_CHECK( l2Point == Vector3({0,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_line_distance_intersect_at_different_points){
    Line3 l1{ {0,0,0}, {1,0,0} };
    Line3 l2{ {1,0,0}, {0,1,0} };
    
    Vector3 l1Point, l2Point;
    
    auto distance = nearest_points(l1, l2, l1Point, l2Point);
    
    BOOST_CHECK(distance == 0);
    BOOST_CHECK( l1Point == Vector3({1,0,0}) );
    BOOST_CHECK( l2Point == Vector3({1,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_line_distance_dont_intersect){
    Line3 l1{ {0,0,0}, {1,0,0} };
    Line3 l2{ {0,0,1}, {0,1,0} };
    
    Vector3 l1Point, l2Point;
    
    auto distance = nearest_points(l1, l2, l1Point, l2Point);
    
    BOOST_CHECK(distance == 1);
    BOOST_CHECK( l1Point == Vector3({0,0,0}) );
    BOOST_CHECK( l2Point == Vector3({0,0,1}) );
}

BOOST_AUTO_TEST_CASE(test_line_distance_parallel){
    Line3 l1{ {0,0,0}, {1,0,0} };
    Line3 l2{ {0,1,0}, {1,0,0} };
    
    Vector3 l1Point, l2Point;
    
    auto distance = nearest_points(l1, l2, l1Point, l2Point);
    
    BOOST_CHECK(distance == 1);
    BOOST_CHECK( l1Point == Vector3({0,0,0}) );
    BOOST_CHECK( l2Point == Vector3({0,1,0}) );
}

BOOST_AUTO_TEST_CASE(test_line_distance_efficiency){
    Line3 l1{ {0,0,0}, {1,0,0} };
    Line3 l2{ {0,1,0}, {1,0,0} };
    
    Vector3 l1Point, l2Point;
    
    std::cout << "test_line_distance_efficiency: " << std::endl;
    {
        Timer t;
        
        for(int i=0; i<10000000; ++i){
            nearest_points(l1, l2, l1Point, l2Point);
        }
    }
}

/*
 * Segment to Segment
 */
BOOST_AUTO_TEST_CASE(test_segment_distance_no_intersection_closest_in_endpoints){
    Segment3 s1{{0,0,0}, {1,0,0}};
    Segment3 s2{{2,0,0}, {3,0,0}};
    
    Vector3 s1Point, s2Point;
    
    auto distance = nearest_points(s1, s2, s1Point, s2Point);
    
    BOOST_CHECK( distance == 1 );
    BOOST_CHECK( s1Point == Vector3({1,0,0}) );
    BOOST_CHECK( s2Point == Vector3({2,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_distance_efficiency){
    Segment3 s1{{0,0,0}, {1,0,0}};
    Segment3 s2{{2,0,0}, {3,0,0}};
    
    Vector3 l1Point, l2Point;
    
    std::cout << "test_segment_distance_efficiency: " << std::endl;
    {
        Timer t;
        
        for(int i=0; i<10000000; ++i){
            nearest_points(s1, s2, l1Point, l2Point);
        }
    }
}

/*
 * Segment to Ray
 */
BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_intersection_1){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{5,1,0}, {0,-1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance == 0 );
    BOOST_CHECK( pointOnSegment == Vector3({5,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({5,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_intersection_2){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{0,2,0}, {1,-1,0}};
    r.mDirection = normalized(r.mDirection);
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance < 0.000001 );
    BOOST_CHECK( length(pointOnSegment - Vector3({2,0,0})) < 0.000001 );
    BOOST_CHECK( length(pointOnRay - Vector3({2,0,0})) < 0.000001 );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_intersection_3){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{5,5,0}, {0,-1,0}};
    r.mDirection = normalized(r.mDirection);
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance == 0 );
    BOOST_CHECK( length(pointOnSegment - Vector3({5,0,0})) < 0.000001 );
    BOOST_CHECK( length(pointOnRay - Vector3({5,0,0})) < 0.000001 );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_no_intersection_1){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{11,1,0}, {0,-1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance == 1 );
    BOOST_CHECK( pointOnSegment == Vector3({10,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({11,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_no_intersection_2){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{5,-1,0}, {0,-1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance == 1 );
    BOOST_CHECK( pointOnSegment == Vector3({5,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({5,-1,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_no_intersection_3){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{-1,0,0}, {0,-1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    
    BOOST_CHECK( distance == 1 );
    BOOST_CHECK( pointOnSegment == Vector3({0,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({-1,0,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_no_intersection_4){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{-2,-1,0}, {0,-1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    BOOST_CHECK( distance == std::sqrt(5.0f) );
    BOOST_CHECK( pointOnSegment == Vector3({0,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({-2,-1,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_no_intersection_5){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{0,2,0}, {0,1,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    BOOST_CHECK( distance == 2 );
    BOOST_CHECK( pointOnSegment == Vector3({0,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({0,2,0}) );
}

BOOST_AUTO_TEST_CASE(test_segment_to_ray_distance_parallel){
    Segment3 s{{0,0,0}, {10,0,0}};
    Ray3 r{{0,2,0}, {1,0,0}};
    
    Vector3 pointOnSegment, pointOnRay;
    
    auto distance = nearest_points(s, r, pointOnSegment, pointOnRay);
    BOOST_CHECK( distance == 2 );
    BOOST_CHECK( pointOnSegment == Vector3({0,0,0}) );
    BOOST_CHECK( pointOnRay == Vector3({0,2,0}) );
}
