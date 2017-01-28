//
//  CORE_MATH_SHAPE_SPHERE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "CORE_MATH_SHAPE_SPHERE.h"

/**
 * http://www.lighthouse3d.com/tutorials/maths/line-and-rays/
 * http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/
 **/
bool CORE_MATH_SHAPE_SPHERE_GetIntersection(
    const CORE_MATH_RAY & ray,
    const CORE_MATH_VECTOR & position,
    const CORE_MATH_VECTOR & half_extent,
    CORE_MATH_VECTOR & intersection ) {
    
    // t = -b +- sqrt( (b*b - c) );
    // b = ^D dot ( O - c )
    // c = ( O - C ) dot ( O - C ) - (r * r)
        
    // if ( ( b * b ) -c < O )
    // else if ( ( b * b ) -c < O )
    // else if ( ( b * b ) -c = O )
    
    float r_square = half_extent.ComputeSquareLength();
    
    CORE_MATH_VECTOR vpc( position - ray.GetOrigin()  );
    
    if ( vpc.ComputeDotProduct( ray.GetDirection() ) < 0) {
        
        float a = ray.GetDirection().ComputeDotProduct(ray.GetDirection() );
        float b = (ray.GetDirection() * 2.0f ).ComputeDotProduct( vpc );
        float c = vpc.ComputeDotProduct( vpc ) - r_square;
        
        float delta = ((b * b) - 4 * a * c );
        
        if ( delta < 0 ) { //miss
            return false ;
        }
        else if ( delta > 0 ) { //2 solutions
            return true;
        }
        else if ( delta == 0 ) { //1 solution
            return true;
        }
    }
    else {
        CORE_MATH_VECTOR pc = ray.GetOrigin() + ray.GetDirection() * ( ( vpc.ComputeDotProduct(ray.GetDirection() ) ) / ray.GetDirection().ComputeLength() );

        CORE_MATH_VECTOR pc_pr = pc -position;
        
        float sq_len = pc_pr.ComputeSquareLength();
        
        if ( sq_len <= r_square ) {
            
            float temp = ( pc - position ).ComputeLength();
            
            float dist = sqrtf( r_square - temp*temp);
            
            float di1;
            
            if ( vpc.ComputeLength() > sqrtf( r_square ) ) {
                
                di1 = ( pc - ray.GetOrigin() ).ComputeLength() - dist;
            }
            else {
                
                di1 = ( pc - ray.GetOrigin() ).ComputeLength() + dist;
            }
            
            intersection = ray.GetOrigin() + ray.GetDirection() * di1;
            
            return true;
        }
        else {
            return false;
        }
    }
    
    return false;
}